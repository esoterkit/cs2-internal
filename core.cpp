#include "core.h"

// [USER] For upstreams
#include <string>

// [USER] For logging
#include "utilities/console/console.h"

// [USER] Initializing our features
#include "hooks/hooks.h"

// [USER] Input Output Stream
#include <iostream>

// [USER] User Interface
#include "utilities/surface/init.h"

DWORD __stdcall InitializeModule()
{
	if (!console::Attach("intern"))
		return false;

	console::info("initialized logging");

	if (!hooks::Setup())
		console::error("failed to initialize hooks");

	console::info("initialized hooks");

	if (!surface::Setup())
		console::error("failed to initialize ISURFACE");

	console::info("initialized surface");

	return true;
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD dReason, LPVOID lpReserved)
{
	switch (dReason)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)InitializeModule, lpReserved, 0, nullptr);
	case DLL_PROCESS_DETACH:
		break;
	}

	return TRUE;
}
