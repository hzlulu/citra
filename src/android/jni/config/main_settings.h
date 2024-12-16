#pragma once

#include <string>

#include "config/config.h"
#include "core/hle/service/cfg/cfg.h"

namespace Settings {
enum class LayoutOption;
enum class MicInputType;
enum class AccurateMul;
enum class SharedFontType;
enum class PresentationMode;
} // namespace Settings

namespace Config {

// core
extern const ConfigInfo<bool> USE_CPU_JIT;
extern const ConfigInfo<bool> IS_NEW_3DS;
extern const ConfigInfo<bool> USE_GAME_CONFIG;
extern const ConfigInfo<bool> USE_VIRTUAL_SD;
extern const ConfigInfo<int> SYSTEM_REGION;
extern const ConfigInfo<Service::CFG::SystemLanguage> SYSTEM_LANGUAGE;
extern const ConfigInfo<Settings::SharedFontType> SHARED_FONT_TYPE;

// renderer
extern const ConfigInfo<bool> USE_GLES;
extern const ConfigInfo<bool> SHOW_FPS;
extern const ConfigInfo<bool> USE_HW_SHADER;
extern const ConfigInfo<bool> USE_SHADER_JIT;
extern const ConfigInfo<Settings::AccurateMul> SHADERS_ACCURATE_MUL;
extern const ConfigInfo<u16> RESOLUTION_FACTOR;
extern const ConfigInfo<bool> USE_FRAME_LIMIT;
extern const ConfigInfo<u16> FRAME_LIMIT;
extern const ConfigInfo<u8> FACTOR_3D;
extern const ConfigInfo<bool> USE_FENCE_SYNC;
extern const ConfigInfo<bool> CUSTOM_TEXTURES;
extern const ConfigInfo<Settings::LayoutOption> LAYOUT_OPTION;
extern const ConfigInfo<Settings::LayoutOption> LANDSCAPE_LAYOUT_OPTION;
extern const ConfigInfo<Settings::PresentationMode> SCREEN_PRESENTATION_MODE;
extern const ConfigInfo<std::string> POST_PROCESSING_SHADER;
extern const ConfigInfo<std::string> REMOTE_SHADER_HOST;

// audio
extern const ConfigInfo<bool> ENABLE_DSP_LLE;
extern const ConfigInfo<bool> DSP_LLE_MULTITHREAD;
extern const ConfigInfo<bool> AUDIO_STRETCHING;
extern const ConfigInfo<float> AUDIO_VOLUME;
extern const ConfigInfo<float> MIC_VOLUME;
extern const ConfigInfo<u8> AUDIO_OUTPUT_TYPE;
extern const ConfigInfo<std::string> AUDIO_OUTPUT_DEVICE;

// mic
extern const ConfigInfo<u8> AUDIO_INPUT_TYPE;
extern const ConfigInfo<std::string> AUDIO_INPUT_DEVICE;

// camera
extern const ConfigInfo<std::string> CAMERA_DEVICE;

// debug
extern const ConfigInfo<u8> HW_GS_MODE;
extern const ConfigInfo<u8> SHADER_TYPE;
extern const ConfigInfo<bool> USE_FMV_HACK;
extern const ConfigInfo<bool> SKIP_SLOW_DRAW;
extern const ConfigInfo<bool> SKIP_CPU_WRITE;
extern const ConfigInfo<bool> SKIP_TEXTURE_COPY;
extern const ConfigInfo<u8> FORCE_TEXTURE_FILTER;
extern const ConfigInfo<bool> ASYNC_SHADER_COMPILE;
extern const ConfigInfo<bool> USE_COMPATIBLE_MODE;
extern const ConfigInfo<bool> USE_PRESENT_THREAD;
extern const ConfigInfo<bool> SHADOW_RENDERING;
extern const ConfigInfo<bool> CPU_USAGE_LIMIT;
extern const ConfigInfo<std::string> LLE_MODULES;
extern const ConfigInfo<std::string> BAIDU_OCR_KEY;
extern const ConfigInfo<std::string> BAIDU_OCR_SECRET;

// controls
extern const ConfigInfo<std::string> BUTTON_A;
extern const ConfigInfo<std::string> BUTTON_B;
extern const ConfigInfo<std::string> BUTTON_X;
extern const ConfigInfo<std::string> BUTTON_Y;
extern const ConfigInfo<std::string> BUTTON_UP;
extern const ConfigInfo<std::string> BUTTON_DOWN;
extern const ConfigInfo<std::string> BUTTON_LEFT;
extern const ConfigInfo<std::string> BUTTON_RIGHT;
extern const ConfigInfo<std::string> BUTTON_L;
extern const ConfigInfo<std::string> BUTTON_R;
extern const ConfigInfo<std::string> BUTTON_START;
extern const ConfigInfo<std::string> BUTTON_SELECT;
extern const ConfigInfo<std::string> BUTTON_DEBUG;
extern const ConfigInfo<std::string> BUTTON_GPIO14;
extern const ConfigInfo<std::string> BUTTON_ZL;
extern const ConfigInfo<std::string> BUTTON_ZR;
extern const ConfigInfo<std::string> BUTTON_HOME;
extern const ConfigInfo<std::string> BUTTON_POWER;
extern const ConfigInfo<std::string> BUTTON_COMBO_1;
extern const ConfigInfo<std::string> BUTTON_COMBO_2;
extern const ConfigInfo<std::string> BUTTON_COMBO_3;
extern const ConfigInfo<std::string> CIRCLE_PAD_UP;
extern const ConfigInfo<std::string> CIRCLE_PAD_DOWN;
extern const ConfigInfo<std::string> CIRCLE_PAD_LEFT;
extern const ConfigInfo<std::string> CIRCLE_PAD_RIGHT;
extern const ConfigInfo<std::string> C_STICK_UP;
extern const ConfigInfo<std::string> C_STICK_DOWN;
extern const ConfigInfo<std::string> C_STICK_LEFT;
extern const ConfigInfo<std::string> C_STICK_RIGHT;
extern const ConfigInfo<std::string> COMBO_KEY_0;
extern const ConfigInfo<std::string> COMBO_KEY_1;
extern const ConfigInfo<std::string> COMBO_KEY_2;
extern const ConfigInfo<u16> INPUT_OVERLAY_ALPHA;
extern const ConfigInfo<u16> INPUT_OVERLAY_SCALE;
extern const ConfigInfo<bool> INPUT_OVERLAY_FEEDBACK;
extern const ConfigInfo<bool> INPUT_OVERLAY_HIDE;
extern const ConfigInfo<bool> INPUT_JOYSTICK_RELATIVE;
extern const ConfigInfo<u32> INPUT_JOYSTICK_RANGE;
extern const ConfigInfo<u32> INPUT_JOYSTICK_DEADZONE;

// custom layout
extern const ConfigInfo<bool> PORTRAIT_CUSTOM_LAYOUT;
extern const ConfigInfo<bool> LANDSCAPE_CUSTOM_LAYOUT;

extern const ConfigInfo<bool> PORTRAIT_SWAP_SCREEN;
extern const ConfigInfo<bool> LANDSCAPE_SWAP_SCREEN;

extern const ConfigInfo<u16> PORTRAIT_TOP_LEFT;
extern const ConfigInfo<u16> PORTRAIT_TOP_TOP;
extern const ConfigInfo<u16> PORTRAIT_TOP_RIGHT;
extern const ConfigInfo<u16> PORTRAIT_TOP_BOTTOM;
extern const ConfigInfo<u16> PORTRAIT_BOTTOM_LEFT;
extern const ConfigInfo<u16> PORTRAIT_BOTTOM_TOP;
extern const ConfigInfo<u16> PORTRAIT_BOTTOM_RIGHT;
extern const ConfigInfo<u16> PORTRAIT_BOTTOM_BOTTOM;

extern const ConfigInfo<u16> LANDSCAPE_TOP_LEFT;
extern const ConfigInfo<u16> LANDSCAPE_TOP_TOP;
extern const ConfigInfo<u16> LANDSCAPE_TOP_RIGHT;
extern const ConfigInfo<u16> LANDSCAPE_TOP_BOTTOM;
extern const ConfigInfo<u16> LANDSCAPE_BOTTOM_LEFT;
extern const ConfigInfo<u16> LANDSCAPE_BOTTOM_TOP;
extern const ConfigInfo<u16> LANDSCAPE_BOTTOM_RIGHT;
extern const ConfigInfo<u16> LANDSCAPE_BOTTOM_BOTTOM;

} // namespace Config