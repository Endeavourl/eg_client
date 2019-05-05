#include "EG_configurator.h"

///
////////////////////////////////////////////////////////////////////////////////////////
///

HWND hChDlg = 0;

DWORD g_dwChatFonts[4];

static const CHAT_GUI_ITEM g_ChatFontsGUI[] = {
	{ IDC_CHECK1, IDC_CHECK2, IDC_CHECK3, IDC_CHECK4, IDC_CHECK5, IDC_CHECK10,
		IDC_CHECK65, IDC_CHECK66, IDC_CHECK67 },
	{ IDC_CHECK9, IDC_CHECK11, IDC_CHECK12, IDC_CHECK68, IDC_CHECK69, IDC_CHECK70,
		IDC_CHECK71, IDC_CHECK72, IDC_CHECK73 },
	{ IDC_CHECK74, IDC_CHECK75, IDC_CHECK13, IDC_CHECK76, IDC_CHECK77, IDC_CHECK78,
		IDC_CHECK79, IDC_CHECK80, IDC_CHECK81 },
	{ IDC_CHECK82, IDC_CHECK83, IDC_CHECK19, IDC_CHECK84, IDC_CHECK85, IDC_CHECK86,
		IDC_CHECK87, IDC_CHECK88, IDC_CHECK89 },
};

///
////////////////////////////////////////////////////////////////////////////////////////
///

void LoadChatFontsGUI(void)
{
	for(UINT i = 0; i<4; i++)
	{
		CheckDlgButton(hChDlg, g_ChatFontsGUI[i].iBoldID, g_dwChatFonts[i] & 0x1);
		CheckDlgButton(hChDlg, g_ChatFontsGUI[i].iItalicID, g_dwChatFonts[i] & 0x2);
		CheckDlgButton(hChDlg, g_ChatFontsGUI[i].iUnderlineID, g_dwChatFonts[i] & 0x4);

		CheckDlgButton(hChDlg, g_ChatFontsGUI[i].iBigID, g_dwChatFonts[i] & 0x8);
		CheckDlgButton(hChDlg, g_ChatFontsGUI[i].iBnWID, ((g_dwChatFonts[i] & 0x10) && !(g_dwChatFonts[i] & 0x80)));
		CheckDlgButton(hChDlg, g_ChatFontsGUI[i].iVBigID, g_dwChatFonts[i] & 0x20);

		CheckDlgButton(hChDlg, g_ChatFontsGUI[i].iSmerID, g_dwChatFonts[i] & 0x40);
		CheckDlgButton(hChDlg, g_ChatFontsGUI[i].iSmestID, ((g_dwChatFonts[i] & 0x80) && !(g_dwChatFonts[i] & 0x10)));
		CheckDlgButton(hChDlg, g_ChatFontsGUI[i].iSmallID, ((g_dwChatFonts[i] & 0x10) && (g_dwChatFonts[i] & 0x80)));
	}
}

////////////////////////////////////////////////////////////////////////////////////////

void SaveChatFontsGUI(void)
{
#define IS_CHECKED(x) (IsDlgButtonChecked(hChDlg, x)==BST_CHECKED)
	for(UINT i = 0; i<4; i++)
	{
		g_dwChatFonts[i] = 0;
		if(IS_CHECKED(g_ChatFontsGUI[i].iBoldID)) g_dwChatFonts[i] |= 0x1;
		if(IS_CHECKED(g_ChatFontsGUI[i].iItalicID)) g_dwChatFonts[i] |= 0x2;
		if(IS_CHECKED(g_ChatFontsGUI[i].iUnderlineID)) g_dwChatFonts[i] |= 0x4;

		if(IS_CHECKED(g_ChatFontsGUI[i].iBigID)) g_dwChatFonts[i] |= 0x8;
		if(IS_CHECKED(g_ChatFontsGUI[i].iBnWID)) g_dwChatFonts[i] |= 0x10;
		if(IS_CHECKED(g_ChatFontsGUI[i].iVBigID)) g_dwChatFonts[i] |= 0x20;
		
		if(IS_CHECKED(g_ChatFontsGUI[i].iSmerID)) g_dwChatFonts[i] |= 0x40;
		if(IS_CHECKED(g_ChatFontsGUI[i].iSmestID)) g_dwChatFonts[i] |= 0x80;
		if(IS_CHECKED(g_ChatFontsGUI[i].iSmallID)) g_dwChatFonts[i] |= 0x90;
	}
#undef IS_CHECKED
}

////////////////////////////////////////////////////////////////////////////////////////

BOOL CALLBACK ChatFontsDlgProc(HWND hDlg, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uiMsg)
	{
	case WM_INITDIALOG:
		{
			hChDlg = hDlg;

			LoadChatFontsGUI();
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
						SaveChatFontsGUI();

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
