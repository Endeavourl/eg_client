#pragma once
#pragma warning(disable: 4786)

////////////////////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include "resource.h"
#include "..\ci_string.h"

///
////////////////////////////////////////////////////////////////////////////////////////
///

#define VERSION L"1.0.4.0"

///
////////////////////////////////////////////////////////////////////////////////////////
///

typedef std::vector<std::pair<std::ci_wstring, DWORD> > CIgnoreList;

typedef struct IGNORE_GUI_ITEM {
	int iEditID;
	int iPFlagID;
	int iIFlagID;
} IGNORE_GUI_ITEM;

typedef struct CHAT_GUI_ITEM {
	int iBoldID;
	int iItalicID;
	int iUnderlineID;
	int iBigID;
	int iBnWID;
	int iVBigID;
	int iSmerID;
	int iSmestID;
	int iSmallID;
} CHAT_GUI_ITEM;

///
////////////////////////////////////////////////////////////////////////////////////////
///

std::string wstos(wchar_t const* wszStr, UINT uiCP_TO);
std::wstring stows(char const* szStr, UINT uiCP_FROM);
UINT ToUINT(const wchar_t* wszStr);
UINT ToUINT(const char* szStr);
int ToInt(const char* szStr);
int ToInt(const wchar_t* wszStr);
float ToFloat(const char* szStr);
float ToFloat(const wchar_t* wszStr);
BOOL CALLBACK IgnoresDlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK ChatFontsDlgProc(HWND, UINT, WPARAM, LPARAM);

///
////////////////////////////////////////////////////////////////////////////////////////
///

extern CIgnoreList g_Ignores;
extern DWORD g_dwChatFonts[4];

///
////////////////////////////////////////////////////////////////////////////////////////
///
