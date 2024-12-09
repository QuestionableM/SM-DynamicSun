#pragma once

#include <SmSdk/offsets.hpp>

#if _SM_VERSION_NUM == 072775
#	define DYNAMIC_SUN_UPDATE_FUNC_ADDR 0x915440
#	define DYNAMIC_SUN_CREATE_WIDGETS_ADDR 0x3C03B0
#	define DYNAMIC_SUN_GRAPHICS_OPTIONS_MENU_VFTABLE 0xF7AD78
#	define DYNAMIC_SUN_DIRECTION_OFFSET 0x11D5CB0
#	define DYNAMIC_SUN_GAME_INSTANCE_PTR 0x1267738
#elif _SM_VERSION_NUM == 071772
#	define DYNAMIC_SUN_UPDATE_FUNC_ADDR 0x915420
#	define DYNAMIC_SUN_CREATE_WIDGETS_ADDR 0x3C0390
#	define DYNAMIC_SUN_GRAPHICS_OPTIONS_MENU_VFTABLE 0xF7AD78
#	define DYNAMIC_SUN_DIRECTION_OFFSET 0x11D5CB0
#	define DYNAMIC_SUN_GAME_INSTANCE_PTR 0x1267738
#elif _SM_VERSION_NUM == 070771
#	define DYNAMIC_SUN_UPDATE_FUNC_ADDR 0x915630
#	define DYNAMIC_SUN_CREATE_WIDGETS_ADDR 0x3C0390
#	define DYNAMIC_SUN_GRAPHICS_OPTIONS_MENU_VFTABLE 0xF7ACF8
#	define DYNAMIC_SUN_DIRECTION_OFFSET 0x11D5CB0
#	define DYNAMIC_SUN_GAME_INSTANCE_PTR 0x1267720
#else
#	define DYNAMIC_SUN_UPDATE_FUNC_ADDR 0x909880
#	define DYNAMIC_SUN_CREATE_WIDGETS_ADDR 0x3CDFA0
#	define DYNAMIC_SUN_GRAPHICS_OPTIONS_MENU_VFTABLE 0xF65600
#	define DYNAMIC_SUN_DIRECTION_OFFSET 0x11D32C0
#	define DYNAMIC_SUN_GAME_INSTANCE_PTR 0x128D790
#endif