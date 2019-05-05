#pragma once
#pragma warning(disable: 4786) // long identifiers and debugging information

#include <windows.h>

#include <stdio.h>
#include <process.h>
#include <time.h>
#include <math.h>

#include <vector>
#include <fstream>

#include "detours.h"
#include "ci_string.h"

#include "FLDALib.h"
#include "FLCommon.h"
#include "FreelancerEXE.h"

////////////////////////////////////////////////////////////////////////////////////////

#define DO_NOTHING __asm { nop }
#define CATCH(where, act) \
	catch(const wchar_t* wszWhat)	{HandleException((where), wszWhat); act;} \
	catch(...)						{HandleException((where), NULL);	act;}

#define FLADDR(a) ((PBYTE)hModFL + (a))
#define ADDR_FL_SPEC_SOLAR_RANGE 0x213EC8 //4 bytes, float
#define ADDR_FL_ADD_SERVER_TO_LIST 0x1AC710 //4 bytes, func offset
#define ADDR_FL_ADD_SERVER_TO_LIST_CLASS 0x27E7B8 //4 bytes, class variable offset
#define ADDR_FL_SINGLE_GOOD_PRICE_LIMIT 0x1CAEE8 //4 bytes, float
#define ADDR_FL_CHATLOG_MAX_LINES 0x691D1 //1 byte, signed char
#define ADDR_FL_CHAT_ONSCREEN_TIME 0x691CA //4 bytes, dword
#define ADDR_FL_CHAT_ONSCREEN_MAX_LINES 0x691CF //1 byte, signed char

////////////////////////////////////////////////////////////////////////////////////////

void InitHacks(void);
bool InitHooks(void);
void UnloadHooks(void);
void UnloadHacks(void);

void WriteProcMem(void*, void*, int);
void ReadProcMem(void*, void*, int);

void HandleException(const wchar_t*, const wchar_t*);

UINT ToUINT(const wchar_t* wszStr);
UINT ToUINT(const char* szStr);
int ToInt(const char* szStr);
int ToInt(const wchar_t* wszStr);
float ToFloat(const char* szStr);
float ToFloat(const wchar_t* wszStr);

std::string wstos(wchar_t const*, UINT uiCP_TO);
std::wstring stows(char const*, UINT uiCP_TO);

bool SinglePlayer_Detoured(void);
void __stdcall ReceiveChat_Detoured(UINT, UINT, ULONG, PVOID);

////////////////////////////////////////////////////////////////////////////////////////

//extern FILE* fLog;
extern HMODULE hModSelf;
extern HMODULE hModFL;

extern bool (* SinglePlayer_Trampoline)(void);
extern void (__stdcall* ReceiveChat_Trampoline)(UINT, UINT, ULONG, PVOID);

////////////////////////////////////////////////////////////////////////////////////////
