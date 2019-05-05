#include "CDetoured_DPClient.h"
#include "Preferences.h"

////////////////////////////////////////////////////////////////////////////////////////

bool (CDetoured_DPClient::* AddConnectAttempt_Trampoline)(const wchar_t* wszAddr, wchar_t *wszPwd);

////////////////////////////////////////////////////////////////////////////////////////

static UINT WINAPI RestrictionBoxThread(PVOID)
{
	MessageBox(0,
		L"Sorry, but you can play only at EG MAIN HQ 24/7 server with this mod installed!\n\nWeb: http://www.elite-games.ru/egmainhq/",
		L"Multiplayer restriction",
		MB_ICONWARNING);

	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////

bool CDetoured_DPClient::AddConnectAttempt_Detoured(const wchar_t *wszAddr, wchar_t *wszPwd)
{
	ULONG ulIP0, ulIP1, ulIP2, ulIP3, ulPort;
	ulIP0 = ulIP1 = ulIP2 = ulIP3 = ulPort = 0;

	swscanf(wszAddr, L"x-directplay:/hostname=%u.%u.%u.%u;port=%u",
		&ulIP0, &ulIP1, &ulIP2, &ulIP3,
		&ulPort);
/*
	if((ulIP0 != 89) || (ulIP1 != 253) || (ulIP2 != 195))
	{
		UINT uiId;
		HANDLE hT = (HANDLE)_beginthreadex(NULL, 0, RestrictionBoxThread, NULL, 0, &uiId);
		if(hT) CloseHandle(hT);

		return false;
	}
*/
	if(g_Prefs->bLogChat())
	{
		try {
			FILE* f =
				_wfopen(g_Prefs->wscChatLogPath().empty()? L"EG_chat.log" :
						g_Prefs->wscChatLogPath().c_str(), L"a+t");
			if(!f)
				throw L"_wfopen failed.";

			long ti = time(NULL);
			tm   *t = localtime(&ti);

			fprintf(f, "\n\n[%04d/%02d/%02d %02d:%02d:%02d]\tUNKN\tConnect attempt to the server, address: %u.%u.%u.%u:%u.\n\n",
				t->tm_year+1900, t->tm_mon+1, t->tm_mday,
				t->tm_hour, t->tm_min, t->tm_sec, 
				ulIP0, ulIP1, ulIP2, ulIP3, ulPort);
			fclose(f);
		}
		CATCH(L"AddConnectAttempt", DO_NOTHING)
	}

	return (this->* AddConnectAttempt_Trampoline)(wszAddr, wszPwd);
}

////////////////////////////////////////////////////////////////////////////////////////
