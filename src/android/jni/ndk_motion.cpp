#include <chrono>
#include <thread>

#include <android/sensor.h>
#include <dlfcn.h>

#include "common/assert.h"
#include "common/logging/log.h"
#include "common/vector_math.h"
#include "jni_common.h"
#include "ndk_motion.h"

using Common::Vec3;

template <typename T>
static void loadSymbol(T*& pfn, const char *symbol) noexcept {
    pfn = (T*)dlsym(RTLD_DEFAULT, symbol);
}

class NDKMotion final : public Input::MotionDevice {
    using GETINSTANCEFORPACKAGE = ASensorManager* (*)(const char*);
    using REGISTERSENSOR = int (*)(ASensorEventQueue* queue, ASensor const* sensor,
                                   int32_t samplingPeriodUs, int64_t maxBatchReportLatencyUs);

    GETINSTANCEFORPACKAGE GetInstanceForPackage = nullptr;
    REGISTERSENSOR RegisterSensor = nullptr;

    ASensorManager* sensor_manager = nullptr;
    ALooper* looper = nullptr;
    ASensorEventQueue* event_queue;

    mutable std::atomic<Vec3<float>> acceleration{};
    mutable std::atomic<Vec3<float>> rotation{};
    static_assert(decltype(acceleration)::is_always_lock_free, "vectors are not lock free");
    std::thread poll_thread;
    std::atomic<bool> stop_polling = false;

    static Vec3<float> TransformAxes(Vec3<float> in) {
        // 3DS   Y+            Phone     Z+
        // on    |             laying    |
        // table |             in        |
        //       |_______ X-   portrait  |_______ X+
        //      /              mode     /
        //     /                       /
        //    Z-                      Y-
        Vec3<float> out;
        out.y = in.z;
        // rotations are 90 degrees counter-clockwise from portrait
        switch (NativeLibrary::current_display_rotation) {
        case 0:
            out.x = -in.x;
            out.z = in.y;
            break;
        case 1:
            out.x = in.y;
            out.z = in.x;
            break;
        case 2:
            out.x = in.x;
            out.z = -in.y;
            break;
        case 3:
            out.x = -in.y;
            out.z = -in.x;
            break;
        default:
            UNREACHABLE();
        }
        return out;
    }

    void Construct(std::chrono::microseconds update_period) {
        sensor_manager = GetInstanceForPackage("org.citra.emu");
        looper = ALooper_prepare(ALOOPER_PREPARE_ALLOW_NON_CALLBACKS);
        if (!sensor_manager || !looper) {
            LOG_CRITICAL(Input, "Could not retrieve sensor manager");
            return;
        }
        event_queue = ASensorManager_createEventQueue(sensor_manager, looper, 0, nullptr, nullptr);
        if (!event_queue) {
            LOG_ERROR(Input, "Could not create sensor event queue");
            return;
        }
        const auto init_sensor = [this, update_period](int sensor_type) {
            ASensorRef sensor = ASensorManager_getDefaultSensor(sensor_manager, sensor_type);
            if (!sensor) {
                LOG_ERROR(Input, "Could not find sensor of type {}", sensor_type);
                return;
            }
            int error = RegisterSensor(
                event_queue, sensor,
                std::max(ASensor_getMinDelay(sensor), static_cast<int>(update_period.count())), 0);
            if (error < 0)
                LOG_ERROR(Input, "Registering sensor returned error code {}", error);
        };

        init_sensor(ASENSOR_TYPE_ACCELEROMETER);
        init_sensor(ASENSOR_TYPE_GYROSCOPE);
    }

    void Destruct() {
        ASensorManager_destroyEventQueue(sensor_manager, event_queue);
    }

    void Update() const {
        ALooper_pollAll(0, nullptr, nullptr, nullptr);
        ASensorEvent event{};
        std::optional<Vec3<float>> new_accel{}, new_rot{};
        while (ASensorEventQueue_getEvents(event_queue, &event, 1) > 0) {
            if (event.type == ASENSOR_TYPE_ACCELEROMETER) {
                new_accel.emplace(event.vector.x, event.vector.y, event.vector.z);
            } else if (event.type == ASENSOR_TYPE_GYROSCOPE) {
                new_rot.emplace(event.vector.x, event.vector.y, event.vector.z);
            }
            // occasionally the queue has ASENSOR_TYPE_ADDITIONAL_INFO events
            // but so far there is no reason to handle them
        }
        if (new_accel) {
            // convert from m/(s^2) to g and invert
            acceleration = TransformAxes(*new_accel) / -ASENSOR_STANDARD_GRAVITY;
        }
        if (new_rot) {
            // convert from rad/s to deg/s
            rotation = TransformAxes(*new_rot) * 180.0f / static_cast<float>(M_PI);
        }
    }

public:
    NDKMotion(std::chrono::microseconds update_period, bool asynchronous = false) {
        loadSymbol(GetInstanceForPackage, "ASensorManager_getInstanceForPackage");
        loadSymbol(RegisterSensor, "ASensorEventQueue_registerSensor");
        if (asynchronous) {
            poll_thread = std::thread([this, update_period] {
                Construct(update_period);
                auto start = std::chrono::high_resolution_clock::now();
                while (!stop_polling) {
                    Update();
                    std::this_thread::sleep_until(start += update_period);
                }
                Destruct();
            });
        } else {
            Construct(update_period);
        }
    }

    ~NDKMotion() override {
        if (std::thread::id{} == poll_thread.get_id()) {
            Destruct();
        } else {
            stop_polling = true;
            poll_thread.join();
        }
    }

    std::tuple<Vec3<float>, Vec3<float>> GetStatus() const override {
        if (std::thread::id{} == poll_thread.get_id()) {
            Update();
        }
        return {acceleration, rotation};
    }
};

std::unique_ptr<Input::MotionDevice> NDKMotionFactory::Create(const Common::ParamPackage& params) {
    std::chrono::milliseconds update_period{params.Get("update_period", 4)};
    return std::make_unique<NDKMotion>(update_period);
}
