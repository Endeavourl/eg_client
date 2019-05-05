#include "EG_configurator.h"

///
////////////////////////////////////////////////////////////////////////////////////////
///

HWND hIDlg;

CIgnoreList g_Ignores;

static const IGNORE_GUI_ITEM g_IgnoresGUI[] = {
	{ IDC_EDIT1,  IDC_CHECK1,  IDC_CHECK2  },
	{ IDC_EDIT2,  IDC_CHECK3,  IDC_CHECK4  },
	{ IDC_EDIT3,  IDC_CHECK5,  IDC_CHECK10 },
	{ IDC_EDIT4,  IDC_CHECK6,  IDC_CHECK7  },
	{ IDC_EDIT5,  IDC_CHECK8,  IDC_CHECK9  },
	{ IDC_EDIT6,  IDC_CHECK11, IDC_CHECK12 },
	{ IDC_EDIT7,  IDC_CHECK13, IDC_CHECK14 },
	{ IDC_EDIT8,  IDC_CHECK15, IDC_CHECK16 },
	{ IDC_EDIT9,  IDC_CHECK17, IDC_CHECK18 },
	{ IDC_EDIT10, IDC_CHECK19, IDC_CHECK20 },
	{ IDC_EDIT11, IDC_CHECK21, IDC_CHECK22 },
	{ IDC_EDIT12, IDC_CHECK23, IDC_CHECK24 },
	{ IDC_EDIT13, IDC_CHECK25, IDC_CHECK26 },
	{ IDC_EDIT14, IDC_CHECK27, IDC_CHECK28 },
	{ IDC_EDIT15, IDC_CHECK29, IDC_CHECK30 },
	{ IDC_EDIT16, IDC_CHECK31, IDC_CHECK32 },
	{ IDC_EDIT17, IDC_CHECK33, IDC_CHECK34 },
	{ IDC_EDIT18, IDC_CHECK35, IDC_CHECK36 },
	{ IDC_EDIT19, IDC_CHECK37, IDC_CHECK38 },
	{ IDC_EDIT20, IDC_CHECK39, IDC_CHECK40 },
	{ IDC_EDIT21, IDC_CHECK41, IDC_CHECK42 },
	{ IDC_EDIT22, IDC_CHECK43, IDC_CHECK44 },
	{ IDC_EDIT23, IDC_CHECK45, IDC_CHECK46 },
	{ IDC_EDIT24, IDC_CHECK47, IDC_CHECK48 },
	{ IDC_EDIT25, IDC_CHECK49, IDC_CHECK50 },
	{ IDC_EDIT26, IDC_CHECK51, IDC_CHECK52 },
	{ IDC_EDIT27, IDC_CHECK53, IDC_CHECK54 },
	{ IDC_EDIT28, IDC_CHECK55, IDC_CHECK56 },
	{ IDC_EDIT29, IDC_CHECK57, IDC_CHECK58 },
	{ IDC_EDIT30, IDC_CHECK59, IDC_CHECK60 },
	{ IDC_EDIT31, IDC_CHECK61, IDC_CHECK62 },
	{ IDC_EDIT32, IDC_CHECK63, IDC_CHECK64 },
};

///
////////////////////////////////////////////////////////////////////////////////////////
///

void LoadIgnoresGUI(void)
{
	UINT i = 0;
	for(CIgnoreList::iterator it = g_Ignores.begin(); it!=g_Ignores.end(); ++it, i++)
	{
		SetDlgItemText(hIDlg, g_IgnoresGUI[i].iEditID,  it->first.c_str());
		CheckDlgButton(hIDlg, g_IgnoresGUI[i].iPFlagID, it->second & 0x1);
		CheckDlgButton(hIDlg, g_IgnoresGUI[i].iIFlagID, it->second & 0x2);
	}
}

////////////////////////////////////////////////////////////////////////////////////////

void SaveIgnoresGUI(void)
{
#define IS_CHECKED(x) (IsDlgButtonChecked(hIDlg, x)==BST_CHECKED)
	g_Ignores.clear();
	g_Ignores.reserve(32);
	for(UINT i = 0; i<32; i++)
	{
		wchar_t wszNickname[24];
		GetDlgItemText(hIDlg, g_IgnoresGUI[i].iEditID, wszNickname, 24);
		std::ci_wstring wscNickname = wszNickname;
		if(wscNickname.empty())
			continue;

		DWORD dwIFlags = 0;
		if(IS_CHECKED(g_IgnoresGUI[i].iPFlagID)) dwIFlags |= 0x1;
		if(IS_CHECKED(g_IgnoresGUI[i].iIFlagID)) dwIFlags |= 0x2;
		
		g_Ignores.push_back(CIgnoreList::value_type(wscNickname, dwIFlags));
	}
#undef IS_CHECKED
}

////////////////////////////////////////////////////////////////////////////////////////

BOOL CALLBACK IgnoresDlgProc(HWND hDlg, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uiMsg)
	{
	case WM_INITDIALOG:
		{
			hIDlg = hDlg;

			wchar_t wszCaption[10240];
			LoadString(GetModuleHandle(NULL), IDS_STRING1, wszCaption, 10240);
			SetDlgItemText(hDlg, IDC_SIGNORECAP, wszCaption);

			LoadIgnoresGUI();
			return TRUE;
		}
	case WM_COMMAND:
		{
			if(HIWORD(wParam)==BN_CLICKED)
			{
				switch(LOWORD(wParam))
				{
				case IDCANCEL:
					{
						SendMessage(hDlg, WM_CLOSE, 0, 0);
						return TRUE;
					}
				case IDOK:
					{
						SaveIgnoresGUI();

						SendMessage(hDlg, WM_CLOSE, 0, 0);
						return TRUE;
					}
				}
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

///
////////////////////////////////////////////////////////////////////////////////////////
///
