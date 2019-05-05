#include "Preferences.h"

//////////////////////////////////////////////////////////////////////

CPreferences* g_Prefs;

//////////////////////////////////////////////////////////////////////

bool InitPrefs(void)
{
	wchar_t wszSelfPath[MAX_PATH];
	GetModuleFileName(hModSelf, wszSelfPath, MAX_PATH);
	
	try {
		std::ci_wstring wscSelfPath = wszSelfPath;
		wscSelfPath.erase(wscSelfPath.find_last_of(L'\\') + 1);
		
		g_Prefs = new CPreferences;
		if(!g_Prefs)
			throw "new CPreferences.";
		
		g_Prefs->Init(wscSelfPath);
	}
	CATCH(L"InitPrefs", return false)
		
	return true;
}

//////////////////////////////////////////////////////////////////////

void UnloadPrefs(void)
{
	delete g_Prefs;
}

//////////////////////////////////////////////////////////////////////

CPreferences::CPreferences()
{
	bAddServers_ = false;

	bHRLODs_			= 
		bHRAsteroids_	=
		bHRGFX_			= false;

	bLogChat_ = false;
	Ignores_.clear();

	dwUniverseChatFont_		= 
		dwGroupChatFont_	=
		dwSystemChatFont_	=
		dwPrivateChatFont_	= 0;

	bHugeChatWindowLog_			=
		bDecOnScreenChatTime_	=
		bDecOnScreenChatLines_	=
		bDisableOnScreenChat_	= false;
}

//////////////////////////////////////////////////////////////////////

void CPreferences::Init(const std::ci_wstring& wscSelfDir)
{
	wscModulePath_ = wscSelfDir;
	Ini_.Init((wscModulePath_ + L"EG_client.ini").c_str());
	Load();
}

//////////////////////////////////////////////////////////////////////

void CPreferences::Load(void)
{
	Ini_.SetSection(L"General");
	bAddServers_ = Ini_.GetBool(L"AddServers");

	Ini_.SetSection(L"HighRangeView");
	bHRLODs_		= Ini_.GetBool(L"HighRangeLODs");
	bHRAsteroids_	= Ini_.GetBool(L"HighRangeAsteroids");
	bHRGFX_			= Ini_.GetBool(L"HighRangeGFX");

	Ini_.SetSection(L"Chat");
	bLogChat_		= Ini_.GetBool(L"LogChat");
	wscChatLogPath_ = wscModulePath_ + L"EG_chat.log";

	LoadIgnores();

	dwUniverseChatFont_ = Ini_.GetInt(L"UniverseChatFont");
	if(dwUniverseChatFont_	> 0xFF) dwUniverseChatFont_ = 0;
	dwGroupChatFont_	= Ini_.GetInt(L"GroupChatFont");
	if(dwGroupChatFont_		> 0xFF) dwGroupChatFont_ = 0;
	dwSystemChatFont_	= Ini_.GetInt(L"SystemChatFont");
	if(dwSystemChatFont_	> 0xFF) dwSystemChatFont_ = 0;
	dwPrivateChatFont_	= Ini_.GetInt(L"PrivateChatFont");
	if(dwPrivateChatFont_	> 0xFF) dwPrivateChatFont_ = 0;

	bHugeChatWindowLog_		= Ini_.GetBool(L"HugeChatWindowLog");
	bDecOnScreenChatTime_	= Ini_.GetBool(L"DecOnScreenChatTime");
	bDecOnScreenChatLines_	= Ini_.GetBool(L"DecOnScreenChatLines", false);
	bDisableOnScreenChat_	= Ini_.GetBool(L"DisableOnScreenChat", false);

	wscExceptionLogFilename_ = wscModulePath_ + L"EG_client.log";
}

//////////////////////////////////////////////////////////////////////

void CPreferences::LoadIgnores(void)
{
	Ini_.SetSection(L"Chat");
	CIgnoreList::size_type stIgnoresCount = Ini_.GetInt(L"IgnoresCount", 32);

	Ignores_.clear();
	Ignores_.reserve(stIgnoresCount);

	for(CIgnoreList::size_type i = 0; i < stIgnoresCount; i++)
	{
		wchar_t wszOrd[128];
		swprintf(wszOrd, L"Ignore%u", i);
		std::ci_wstring wscIgnore = Ini_.GetString(wszOrd);
		if(wscIgnore.empty())
			continue;
		
		std::ci_wstring::size_type stDivider = wscIgnore.find(L' ');
		if(stDivider == std::ci_wstring::npos)
			continue;
		
		std::ci_wstring wscINick = wscIgnore.substr(0, stDivider);
		DWORD dwIFlags = ToUINT(wscIgnore.substr(stDivider+1).c_str());
		
		if((dwIFlags >= 0x4) || wscINick.empty())
			continue;
		
		Ignores_.push_back(CIgnoreList::value_type(wscINick, dwIFlags));
	}
}

///////////////////////////////////////////////////////////////////////////////////////////
