#include "EG_client.h"
#include "CDetoured_INI_Reader.h"
#include "CDetoured_DPClient.h"

////////////////////////////////////////////////////////////////////////////////////////

#define MAX_HOOKS 256

struct DETOUR_INFO {
	PBYTE pfTarget;
	PBYTE pfDetour;
	PBYTE pfTrampolinePointer;
};

// hooks (detours) stuff
// an array of hook-describing structures
// and pointer to allocated memory for trampolines storage
// trampolines are pieces of binary code overwritten by jmp instruction
static DETOUR_INFO g_DetoursInfo[MAX_HOOKS];
static PVOID g_pTrampolineMemory;

////////////////////////////////////////////////////////////////////////////////////////

void UnloadHooks(void)
{
	if(!g_pTrampolineMemory)
		return;

	for(UINT i = 0; i < MAX_HOOKS; i++)
	{
		if(!g_DetoursInfo[i].pfTarget							||
			!g_DetoursInfo[i].pfDetour							||
			!g_DetoursInfo[i].pfTrampolinePointer				||
			!(*((PBYTE*)g_DetoursInfo[i].pfTrampolinePointer)))
				continue;
		
		try {
			if(!DetourRemove(*((PBYTE*)g_DetoursInfo[i].pfTrampolinePointer), g_DetoursInfo[i].pfDetour))
				throw L"unhooking.";
			else
				*((PBYTE*)g_DetoursInfo[i].pfTrampolinePointer) = NULL;
		}
		CATCH(L"UnloadHooks", DO_NOTHING)
	}

	VirtualFree(g_pTrampolineMemory, NULL, MEM_RELEASE);
}

////////////////////////////////////////////////////////////////////////////////////////

static void InitHooksStruct(void)
{
	// compiler doesn't allow these address types conversions compile-time
	// since pointers-to-member-functions can take more bytes than ordinary PVOID
	// so we are doing these conversions in runtime (and keeping fingers crossed ;])
	// add all necessary hooks (detours) in this function

	memset(&g_DetoursInfo, 0, sizeof(g_DetoursInfo));

	//get_value_float
	float (INI_Reader::* pfget_value_float)(unsigned int)
		= INI_Reader::get_value_float;
	float (CDetoured_INI_Reader::* pfget_value_floatDetour)(unsigned int)
		= CDetoured_INI_Reader::get_value_float_Detoured;
	g_DetoursInfo[0].pfTarget = *(PBYTE*)&pfget_value_float;
	g_DetoursInfo[0].pfDetour = *(PBYTE*)&pfget_value_floatDetour;
	g_DetoursInfo[0].pfTrampolinePointer = (PBYTE)&get_value_float_Trampoline;
		
	//get_value_string
	const char* (INI_Reader::* pfget_value_string)(void)
		= INI_Reader::get_value_string;
	const char* (CDetoured_INI_Reader::* pfget_value_stringDetour)(void)
		= CDetoured_INI_Reader::get_value_string_Detoured;
	g_DetoursInfo[1].pfTarget = *(PBYTE*)&pfget_value_string;
	g_DetoursInfo[1].pfDetour = *(PBYTE*)&pfget_value_stringDetour;
	g_DetoursInfo[1].pfTrampolinePointer = (PBYTE)&get_value_string_Trampoline;

	//AddConnectAttempt
	bool (CDPClient::* pfAddConnectAttempt)(wchar_t const*, wchar_t*)
		= CDPClient::AddConnectAttempt;
	bool (CDetoured_DPClient::* pfAddConnectAttemptDetour)(wchar_t const*, wchar_t*)
		= CDetoured_DPClient::AddConnectAttempt_Detoured;
	g_DetoursInfo[2].pfTarget = *(PBYTE*)&pfAddConnectAttempt;
	g_DetoursInfo[2].pfDetour = *(PBYTE*)&pfAddConnectAttemptDetour;
	g_DetoursInfo[2].pfTrampolinePointer = (PBYTE)&AddConnectAttempt_Trampoline;

	//SinglePlayer
	bool (* pfSinglePlayer)(void) = SinglePlayer;
	bool (* pfSinglePlayerDetour)(void) = SinglePlayer_Detoured;
	g_DetoursInfo[3].pfTarget = *(PBYTE*)&pfSinglePlayer;
	g_DetoursInfo[3].pfDetour = *(PBYTE*)&pfSinglePlayerDetour;
	g_DetoursInfo[3].pfTrampolinePointer = (PBYTE)&SinglePlayer_Trampoline;

	//ReceiveChat
	void (__stdcall* pfReceiveChatDetour)(UINT, UINT, ULONG, PVOID)
		= ReceiveChat_Detoured;
	g_DetoursInfo[4].pfTarget = **GetChatClientInterface();
	g_DetoursInfo[4].pfDetour = *(PBYTE*)&pfReceiveChatDetour;
	g_DetoursInfo[4].pfTrampolinePointer = (PBYTE)&ReceiveChat_Trampoline;
}

////////////////////////////////////////////////////////////////////////////////////////

bool InitHooks(void)
{
	InitHooksStruct();

	// getting the memory page size for proper allocation & alignment
	SYSTEM_INFO si;
	memset(&si, 0, sizeof(si));
	GetSystemInfo(&si);

	// reserving memory to hold MAX_HOOKS trampolines
	// each trampoline should be aligned on page boundary
	g_pTrampolineMemory =
		VirtualAlloc(NULL, si.dwPageSize*MAX_HOOKS, MEM_RESERVE, PAGE_EXECUTE_READWRITE);

	try {
		if(!g_pTrampolineMemory)
			throw L"reserving memory.";

		for(UINT i = 0; i < MAX_HOOKS; i++)
		{
			if(!g_DetoursInfo[i].pfTarget || !g_DetoursInfo[i].pfDetour || !g_DetoursInfo[i].pfTrampolinePointer)
				continue;

			// allocating memory for trampolines, aligned on page boundary
			PBYTE pbTramp = 
				(PBYTE)VirtualAlloc((PVOID)((UINT_PTR)g_pTrampolineMemory + i*si.dwPageSize),
									DETOUR_TRAMPOLINE_SIZE, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
			if(!pbTramp)
				throw L"committing memory.";

			// nop-out the trampoline memory, because it will hold code, just in case
			// 0x90 is binary code for nop (no operation)
			memset(pbTramp, 0x90, DETOUR_TRAMPOLINE_SIZE);

			if(!DetourFunctionWithEmptyTrampoline(pbTramp, g_DetoursInfo[i].pfTarget, g_DetoursInfo[i].pfDetour))
				throw L"hooking.";
			else
				*((PBYTE*)g_DetoursInfo[i].pfTrampolinePointer) = pbTramp;
		}
	}
	CATCH(L"InitHooks", return false)

	return true;
}

////////////////////////////////////////////////////////////////////////////////////////
