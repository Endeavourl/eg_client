#include "EG_client.h"

///
////////////////////////////////////////////////////////////////////////////////////////
///

void WriteProcMem(void* pAddress, void* pMem, int iSize)
{
	HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, GetCurrentProcessId());
	DWORD dwOld;
	VirtualProtectEx(hProc, pAddress, iSize, PAGE_EXECUTE_READWRITE, &dwOld);
	WriteProcessMemory(hProc, pAddress, pMem, iSize, 0);
	CloseHandle(hProc);
}

////////////////////////////////////////////////////////////////////////////////////////

void ReadProcMem(void* pAddress, void* pMem, int iSize)
{
	HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, GetCurrentProcessId());
	DWORD dwOld;
	VirtualProtectEx(hProc, pAddress, iSize, PAGE_EXECUTE_READWRITE, &dwOld);
	ReadProcessMemory(hProc, pAddress, pMem, iSize, 0);
	CloseHandle(hProc);
}

///
////////////////////////////////////////////////////////////////////////////////////////
///
