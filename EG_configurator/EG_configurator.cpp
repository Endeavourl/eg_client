#include "EG_configurator.h"
#include "IniFile.h"

///
////////////////////////////////////////////////////////////////////////////////////////
///

HWND hMainDlg = 0;
std::ci_wstring wscModulePath = L"";

///
////////////////////////////////////////////////////////////////////////////////////////
///
/*
void DisableAll(bool bDisable)
{
	for(UINT i=IDC_CHECK2; i<=IDC_BUTTON4; i++)
	{
		switch(i)
		{
		case IDC_BUTTON2:
			continue;
		}
		EnableWindow(GetDlgItem(hMainDlg, i), bDisable);
	}
	EnableWindow(GetDlgItem(hMainDlg, IDC_CHECK13), bDisable);
}
*/
////////////////////////////////////////////////////////////////////////////////////////

void SaveIgnores(CIniFile& ini)
{
	ini.SetSection(L"Chat");
	UINT i = 0;
	for(CIgnoreList::iterator it = g_Ignores.begin(); it!=g_Ignores.end(); it++, i++)
	{
		wchar_t wszOrd[128];
		swprintf(wszOrd, L"Ignore%u", i);
		wchar_t wszFlag[4];
		swprintf(wszFlag, L" %u", it->second);
		ini.WriteString(wszOrd, (it->first+wszFlag).c_str());
	}

	for(; i<32; i++)
	{
		wchar_t wszOrd[128];
		swprintf(wszOrd, L"Ignore%u", i);
		ini.WriteString(wszOrd, L"");
	}
}

////////////////////////////////////////////////////////////////////////////////////////

void SaveSettings(void)
{
	std::ci_wstring wscIniPath = wscModulePath + L"EG_client.ini";
	if(_waccess(wscIniPath.c_str(), 0))
	{ // if file doesnt exist write the UTF16 LE BOM first
		FILE* fTmp = _wfopen(wscIniPath.c_str(), L"w+t");
		if(fTmp)
		{
			fwrite("\xFF\xFE", 1, 2, fTmp);
			fclose(fTmp);
		}
	}

#define IS_CHECKED(x) (IsDlgButtonChecked(hMainDlg, x)==BST_CHECKED)

	CIniFile ini(wscIniPath.c_str());

	ini.SetSection(L"General");
//	ini.WriteBool(L"SystemEnabled", IS_CHECKED(IDC_CHECK1));
	ini.WriteBool(L"AddServers", IS_CHECKED(IDC_CHECK13));
	
	ini.SetSection(L"HighRangeView");
	ini.WriteBool(L"HighRangeLODs", IS_CHECKED(IDC_CHECK2));
	ini.WriteBool(L"HighRangeGFX", IS_CHECKED(IDC_CHECK3));
	ini.WriteBool(L"HighRangeAsteroids", IS_CHECKED(IDC_CHECK4));

	ini.SetSection(L"Chat");
	ini.WriteBool(L"LogChat", IS_CHECKED(IDC_CHECK5));
	DWORD dwGlobalIgnoreFlags = 0;
	if(IS_CHECKED(IDC_CHECK6)) dwGlobalIgnoreFlags |= 0x8;
	if(IS_CHECKED(IDC_CHECK7)) dwGlobalIgnoreFlags |= 0x4;
	if(IS_CHECKED(IDC_CHECK8)) dwGlobalIgnoreFlags |= 0x2;
	if(IS_CHECKED(IDC_CHECK9)) dwGlobalIgnoreFlags |= 0x1;
	ini.WriteInt(L"GlobalIgnoreFlags", dwGlobalIgnoreFlags);

	SaveIgnores(ini);

	ini.WriteInt(L"UniverseChatFont", g_dwChatFonts[0]);
	ini.WriteInt(L"SystemChatFont", g_dwChatFonts[1]);
	ini.WriteInt(L"GroupChatFont", g_dwChatFonts[2]);
	ini.WriteInt(L"PrivateChatFont", g_dwChatFonts[3]);

	ini.WriteBool(L"HugeChatWindowLog", IS_CHECKED(IDC_CHECK14));
	ini.WriteBool(L"DisableOnScreenChat", IS_CHECKED(IDC_CHECK15));
	ini.WriteBool(L"DecOnScreenChatTime", IS_CHECKED(IDC_CHECK16));
	ini.WriteBool(L"DecOnScreenChatLines", IS_CHECKED(IDC_CHECK17));

#undef IS_CHECKED
}

////////////////////////////////////////////////////////////////////////////////////////

void LoadIgnores(CIniFile& ini)
{
	ini.SetSection(L"Chat");
	g_Ignores.clear();
	g_Ignores.reserve(32);
	for(UINT i = 0; i<32; i++)
	{
		wchar_t wszOrd[128];
		swprintf(wszOrd, L"Ignore%u", i);
		std::ci_wstring wscIgnore = ini.GetString(wszOrd);
		if(wscIgnore.empty())
			continue;

		std::ci_wstring::size_type stDivider = wscIgnore.find(L' ');
		if(stDivider==std::ci_wstring::npos)
			continue;

		std::ci_wstring wscINick = wscIgnore.substr(0, stDivider);
		DWORD dwIFlags = ToUINT(wscIgnore.substr(stDivider+1).c_str());

		if((dwIFlags >= 0x4) || wscINick.empty())
			continue;

		g_Ignores.push_back(CIgnoreList::value_type(wscINick, dwIFlags));
	}
}

////////////////////////////////////////////////////////////////////////////////////////

void LoadSettings(void)
{
	CIniFile ini((wscModulePath+L"EG_client.ini").c_str());
	
	ini.SetSection(L"General");
//	bool bEnabled = ini.GetBool(L"SystemEnabled");
	CheckDlgButton(hMainDlg, IDC_CHECK1, true/*bEnabled*/);
//	DisableAll(bEnabled);
	CheckDlgButton(hMainDlg, IDC_CHECK13, ini.GetBool(L"AddServers"));

	ini.SetSection(L"HighRangeView");
	CheckDlgButton(hMainDlg, IDC_CHECK2, ini.GetBool(L"HighRangeLODs"));
	CheckDlgButton(hMainDlg, IDC_CHECK3, ini.GetBool(L"HighRangeGFX"));
	CheckDlgButton(hMainDlg, IDC_CHECK4, ini.GetBool(L"HighRangeAsteroids"));

	ini.SetSection(L"Chat");
	CheckDlgButton(hMainDlg, IDC_CHECK5, ini.GetBool(L"LogChat"));
	DWORD dwGlobalIgnoreFlags = 0;
	dwGlobalIgnoreFlags = ini.GetInt(L"GlobalIgnoreFlags");
	CheckDlgButton(hMainDlg, IDC_CHECK6, dwGlobalIgnoreFlags & 0x8);
	CheckDlgButton(hMainDlg, IDC_CHECK7, dwGlobalIgnoreFlags & 0x4);
	CheckDlgButton(hMainDlg, IDC_CHECK8, dwGlobalIgnoreFlags & 0x2);
	CheckDlgButton(hMainDlg, IDC_CHECK9, dwGlobalIgnoreFlags & 0x1);

	LoadIgnores(ini);

	g_dwChatFonts[0] = ini.GetInt(L"UniverseChatFont");
	if(g_dwChatFonts[0] > 0xFF) g_dwChatFonts[0] = 0;
	g_dwChatFonts[1] = ini.GetInt(L"SystemChatFont");
	if(g_dwChatFonts[1] > 0xFF) g_dwChatFonts[1] = 0;
	g_dwChatFonts[2] = ini.GetInt(L"GroupChatFont");
	if(g_dwChatFonts[2] > 0xFF) g_dwChatFonts[2] = 0;
	g_dwChatFonts[3] = ini.GetInt(L"PrivateChatFont");
	if(g_dwChatFonts[3] > 0xFF) g_dwChatFonts[3] = 0;

	CheckDlgButton(hMainDlg, IDC_CHECK14, ini.GetBool(L"HugeChatWindowLog"));
	CheckDlgButton(hMainDlg, IDC_CHECK15, ini.GetBool(L"DisableOnScreenChat", NULL, false));
	CheckDlgButton(hMainDlg, IDC_CHECK16, ini.GetBool(L"DecOnScreenChatTime"));
	CheckDlgButton(hMainDlg, IDC_CHECK17, ini.GetBool(L"DecOnScreenChatLines", NULL, false));
}

////////////////////////////////////////////////////////////////////////////////////////

bool ButtonClicked(USHORT usID)
{
	switch(usID)
	{
	case IDC_BUTTON1: //About
		{
			MessageBox(hMainDlg,
				L"EG MAIN HQ client add-on configurator.\nAdd-on was made by OutCast especially for Elite Games.\n\nYou are using version " VERSION L"\n\n(c)Elite Games, 2008\n(c)OutCast, 2008\n\nhttp://www.elite-games.ru/egmainhq",
				L"About...",
				MB_ICONASTERISK);
			break;
		}
/*	case IDC_CHECK1: //Enable add-on
		{
			DisableAll((IsDlgButtonChecked(hMainDlg, IDC_CHECK1)==BST_CHECKED));			
			break;
		}
*/	case IDC_BUTTON2: //Apply
		{
			SaveSettings();
			break;
		}
	case IDC_BUTTON3: //ignore nicknames button
		{
			DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG2),
				hMainDlg, IgnoresDlgProc);
			break;
		}
	case IDC_BUTTON4: //chatfonts button
		{
			DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG3),
				hMainDlg, ChatFontsDlgProc);
			break;
		}
	case IDCANCEL:
		{
			SendMessage(hMainDlg, WM_CLOSE, 0, 0);
			break;
		}
	case IDOK:
		{
			SaveSettings();
			SendMessage(hMainDlg, WM_CLOSE, 0, 0);
			break;
		}
	default: return false;
	}
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////

BOOL CALLBACK MainDlgProc(HWND hDlg, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uiMsg)
	{
	case WM_INITDIALOG:
		{
			hMainDlg = hDlg;
			HMODULE hSelf = GetModuleHandle(NULL);

			SendMessage(hDlg, WM_SETICON, ICON_BIG,
				(long)LoadIcon(hSelf, MAKEINTRESOURCE(IDI_ICON1)));

			wchar_t wszSelfPath[MAX_PATH];
			GetModuleFileName(hSelf, wszSelfPath, MAX_PATH);
			wscModulePath = wszSelfPath;
			wscModulePath.erase(wscModulePath.find_last_of(L'\\')+1);

			LoadSettings();
			return TRUE;
		}
	case WM_COMMAND:
		{
			if(HIWORD(wParam)==BN_CLICKED)
			{
				if(ButtonClicked(LOWORD(wParam)))
					return TRUE;
			}
			break;
		}
	case WM_CLOSE:
		{
			EndDialog(hDlg, 0);
			return TRUE;
		}
	}
	return FALSE;
}

////////////////////////////////////////////////////////////////////////////////////////

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpwCmdLine, int nCmdShow)
{
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, MainDlgProc);
}

///
////////////////////////////////////////////////////////////////////////////////////////
///
