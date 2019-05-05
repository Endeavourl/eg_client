#include "EG_client.h"
#include "Preferences.h"

///////////////////////////////////////////////////////////////////////////////////////////

// old memory values that hacks change are stored here
static 
float	fOldSpecRange		= 10000.0f,

		fOldSingleGoodPrice	= 9999999.0f;

static 
signed char cOldChatLogMaxLines		 = 0x20,
			cOldMaxOnScreenChatLines = 0x20;
static
ULONG		lOldOnScreenChatTime	 = 10000;

///////////////////////////////////////////////////////////////////////////////////////////

void InitHacks(void)
{
	// special solars high range
	ReadProcMem(FLADDR(ADDR_FL_SPEC_SOLAR_RANGE), &fOldSpecRange, 4);
	if(g_Prefs->bHRLODs())
	{
		float fSpecRange = 250000.0f;
		WriteProcMem(FLADDR(ADDR_FL_SPEC_SOLAR_RANGE), &fSpecRange, 4);
	}
	
	// max single good price
	ReadProcMem(FLADDR(ADDR_FL_SINGLE_GOOD_PRICE_LIMIT), &fOldSingleGoodPrice, 4);
	float fSingleGoodPrice = 999999999.0f;
	WriteProcMem(FLADDR(ADDR_FL_SINGLE_GOOD_PRICE_LIMIT), &fSingleGoodPrice, 4);
	
	// max lines in chat log window
	ReadProcMem(FLADDR(ADDR_FL_CHATLOG_MAX_LINES), &cOldChatLogMaxLines, 1);
	if(g_Prefs->bHugeChatWindowLog())
	{
		signed char cMaxLines = 127;
		WriteProcMem(FLADDR(ADDR_FL_CHATLOG_MAX_LINES), &cMaxLines, 1);
	}
	
	// reading on-screen chat params
	ReadProcMem(FLADDR(ADDR_FL_CHAT_ONSCREEN_TIME), &lOldOnScreenChatTime, 4);
	ReadProcMem(FLADDR(ADDR_FL_CHAT_ONSCREEN_MAX_LINES), &cOldMaxOnScreenChatLines, 1);
	
	if(g_Prefs->bDisableOnScreenChat())
	{
		signed char cMaxLines = -1;
		WriteProcMem(FLADDR(ADDR_FL_CHAT_ONSCREEN_MAX_LINES), &cMaxLines, 1);
	}
	else
	{
		// on-screen chat not disabled
		if(g_Prefs->bDecOnScreenChatTime())
		{
			// decrease time chat shown on screen
			ULONG lTime = 2500;
			WriteProcMem(FLADDR(ADDR_FL_CHAT_ONSCREEN_TIME), &lTime, 4);
		}
		if(g_Prefs->bDecOnScreenChatLines())
		{
			// decrease chat lines shown on screen
			signed char cMaxLines = 4;
			WriteProcMem(FLADDR(ADDR_FL_CHAT_ONSCREEN_MAX_LINES), &cMaxLines, 1);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////

void UnloadHacks(void)
{
	WriteProcMem(FLADDR(ADDR_FL_SPEC_SOLAR_RANGE), &fOldSpecRange, 4);
	
	WriteProcMem(FLADDR(ADDR_FL_SINGLE_GOOD_PRICE_LIMIT), &fOldSingleGoodPrice, 4);
	
	WriteProcMem(FLADDR(ADDR_FL_CHATLOG_MAX_LINES), &cOldChatLogMaxLines, 1);
	WriteProcMem(FLADDR(ADDR_FL_CHAT_ONSCREEN_TIME), &lOldOnScreenChatTime, 4);
	WriteProcMem(FLADDR(ADDR_FL_CHAT_ONSCREEN_MAX_LINES), &cOldMaxOnScreenChatLines, 1);
}

////////////////////////////////////////////////////////////////////////////////////////
