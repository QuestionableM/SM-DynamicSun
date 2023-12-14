#include "win_include.hpp"

#include "Utils/Console.hpp"

#include "GraphicsOptionsMenu.hpp"
#include "DynamicSun.hpp"

#include <MinHook.h>

static bool ms_mhInitialized = false;
static bool ms_mhHooksAttached = false;

void process_attach()
{
	AttachDebugConsole();

	if (MH_Initialize() != MH_OK)
	{
		DebugErrorL("Couldn't initialize minHook");
		return;
	}

	ms_mhInitialized = true;

	const std::uintptr_t v_mod_base = std::uintptr_t(GetModuleHandle(NULL));
	MH_CreateHook((LPVOID)(v_mod_base + 0x909880),
		(LPVOID)DynamicSun::Update,
		(LPVOID*)&DynamicSun::o_PresentFunction);

	//0x35D8E0 - is the actual address, but i have to call the function before the end
	MH_CreateHook((LPVOID)(v_mod_base + 0x3CDFA0),
		(LPVOID)GraphicsOptionsMenu::h_CreateWidgets,
		(LPVOID*)&GraphicsOptionsMenu::o_CreateWidgets);

	MH_CreateHook((LPVOID)(v_mod_base + 0x35D5F0),
		(LPVOID)GraphicsOptionsMenu::h_Destructor,
		(LPVOID*)&GraphicsOptionsMenu::o_Destructor);


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