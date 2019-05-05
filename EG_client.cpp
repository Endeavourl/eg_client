#include "EG_client.h"
#include "Preferences.h"

/// TODO:
/// make display options for widescreen
/// try to make dynamic windowed mode
/// lightning fix, engine fix
/// fix screen shaking
/// chat log conflicts?
/// decentralize headers
////////////////////////////////////////////////////////////////////////////////////////

HMODULE	hModSelf, hModFL;

//FILE* fLog;

////////////////////////////////////////////////////////////////////////////////////////

BOOL CALLBACK DllMain(HINSTANCE hModule, DWORD fdwReason, LPVOID lpReserved)
{
	if(!lpReserved)
	{
		if(fdwReason == DLL_PROCESS_ATTACH)
		{
			/*
			fLog = fopen("_log.log", "a+t");
			if(!fLog)
				return FALSE;
			*/

			DisableThreadLibraryCalls(hModule);

			hModSelf = hModule;
			hModFL = GetModuleHandle(NULL);

			if(!InitPrefs())
				return FALSE;

			InitHacks();

			if(!InitHooks())
				return FALSE;
		}

		else if(fdwReason == DLL_PROCESS_DETACH)
		{
			/*
			if(fLog != NULL)
				fclose(fLog);
			*/
			UnloadHooks();
			UnloadHacks();
			UnloadPrefs();
		}
	}
    return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////
