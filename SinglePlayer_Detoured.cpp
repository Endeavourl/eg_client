#include "EG_client.h"
#include "Preferences.h"

////////////////////////////////////////////////////////////////////////////////////////

static const char szMain[] = "fl.elite-games.ru:2302";

bool (* SinglePlayer_Trampoline)(void);

////////////////////////////////////////////////////////////////////////////////////////

bool SinglePlayer_Detoured(void)
{
	static bool bAdded = false;
	if(!bAdded)
	{
		if(g_Prefs->bAddServers())
		{
			__asm {
				mov		eax, hModFL
				lea		ecx, [eax + ADDR_FL_ADD_SERVER_TO_LIST_CLASS]
				add		eax, ADDR_FL_ADD_SERVER_TO_LIST
				push	offset szMain
				call	eax
			}
		}
		bAdded = true;
	}

	return (SinglePlayer_Trampoline)();
}

////////////////////////////////////////////////////////////////////////////////////////
