#include "IniFile.h"

//////////////////////////////////////////////////////////////////////

typedef std::vector<std::pair<std::ci_wstring, DWORD> > CIgnoreList;

class CPreferences  
{
	CIniFile Ini_;
	std::ci_wstring	wscModulePath_;
	std::ci_wstring	wscExceptionLogFilename_;

	//General options
	bool bAddServers_;

	//Enabled/Disabled HighRangeView options
	bool bHRLODs_;
	bool bHRAsteroids_;
	bool bHRGFX_;

	//Chat options
	bool bLogChat_;

	std::ci_wstring	wscChatLogPath_;
	CIgnoreList		Ignores_;

	DWORD	dwUniverseChatFont_;
	DWORD	dwGroupChatFont_;
	DWORD	dwSystemChatFont_;
	DWORD	dwPrivateChatFont_;
	bool	bHugeChatWindowLog_;
	bool	bDecOnScreenChatTime_;
	bool	bDecOnScreenChatLines_;
	bool	bDisableOnScreenChat_;

	void LoadIgnores(void);

public:
	CPreferences();

	void Init(const std::ci_wstring& wscSelfDir);
	void Load(void);
	
	// getters
	const CIniFile& GetIni() const { return Ini_; }
	const std::ci_wstring& wscModulePath() const 
						{ return wscModulePath_; }
	const std::ci_wstring& wscExceptionLogFilename() const 
						{ return wscExceptionLogFilename_; }

	bool bAddServers() const { return bAddServers_; }

	bool bHRLODs() const { return bHRLODs_; }
	bool bHRAsteroids() const { return bHRAsteroids_; }
	bool bHRGFX() const { return bHRGFX_; }

	bool bLogChat() const { return bLogChat_; }
	const std::ci_wstring& wscChatLogPath() const 
						{ return wscChatLogPath_; }

	const CIgnoreList& Ignores() const { return Ignores_; }
	DWORD dwUniverseChatFont() const { return dwUniverseChatFont_; }
	DWORD dwGroupChatFont() const { return dwGroupChatFont_; }
	DWORD dwSystemChatFont() const { return dwSystemChatFont_; }
	DWORD dwPrivateChatFont() const { return dwPrivateChatFont_; }
	bool bHugeChatWindowLog() const { return bHugeChatWindowLog_; }
	bool bDecOnScreenChatTime() const { return bDecOnScreenChatTime_; }
	bool bDecOnScreenChatLines() const { return bDecOnScreenChatLines_; }
	bool bDisableOnScreenChat() const { return bDisableOnScreenChat_; }

private:
	// disable copy and assign
	CPreferences(const CPreferences&);
	CPreferences& operator=(const CPreferences&);
};

//////////////////////////////////////////////////////////////////////

bool InitPrefs(void);
void UnloadPrefs(void);

extern CPreferences* g_Prefs;

//////////////////////////////////////////////////////////////////////
