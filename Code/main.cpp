#include <SmSdk/TimestampCheck.hpp>
#include <SmSdk/win_include.hpp>

#include "Utils/Console.hpp"
#include "offsets.hpp"

#include "GraphicsOptionsMenu.hpp"
#include "DynamicSun.hpp"

#include <MinHook.h>

#pragma comment(lib, "User32.lib")

static bool ms_mhInitialized = false;
static bool ms_mhHooksAttached = false;

void process_attach()
{
	if (!SmSdk::CheckTimestamp(_SM_TIMESTAMP_072_775))
	{
		MessageBoxA(
			NULL,
			"Your game version is not supported by Dynamic Sun. The current version of the mod has been built for Scrap Mechanic 0.7.2.775\n\nPress OK to continue loading without the mod.",
			"Unsupported Version",
			MB_ICONWARNING);
		return;
	}

	AttachDebugConsole();

	if (MH_Initialize() != MH_OK)
	{
		DebugErrorL("Couldn't initialize minHook");
		return;
	}

	ms_mhInitialized = true;

	const std::uintptr_t v_mod_base = std::uintptr_t(GetModuleHandle(NULL));
	MH_CreateHook((LPVOID)(v_mod_base + DYNAMIC_SUN_UPDATE_FUNC_ADDR),
		(LPVOID)DynamicSun::Update,
		(LPVOID*)&DynamicSun::o_PresentFunction);
	// (0.6.6) 0x35D8E0 - is the actual address, but i have to call the function before the end
	MH_CreateHook((LPVOID)(v_mod_base + DYNAMIC_SUN_CREATE_WIDGETS_ADDR),
		(LPVOID)GraphicsOptionsMenu::h_CreateWidgets,
		(LPVOID*)&GraphicsOptionsMenu::o_CreateWidgets);

	ms_mhHooksAttached = MH_EnableHook(MH_ALL_HOOKS) == MH_OK;
}

void process_detach(HMODULE hmod)
{
	if (ms_mhInitialized)
	{
		if (ms_mhHooksAttached)
			MH_DisableHook(MH_ALL_HOOKS);

		MH_Uninitialize();
	}

	FreeLibrary(hmod);
}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		process_attach();
		break;
	case DLL_PROCESS_DETACH:
		process_detach(hModule);
		break;
	}

	return TRUE;
}