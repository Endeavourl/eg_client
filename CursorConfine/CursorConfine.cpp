#include <windows.h>

#include <cwchar>
#include <process.h>

static volatile bool g_stop = false;

void errorBox(const wchar_t* err)
{
	MessageBox(0, err, L"Error", MB_ICONERROR);
}

RECT setupWnd(HWND wnd) 
{
	HMONITOR hMon = MonitorFromWindow(wnd, MONITOR_DEFAULTTONEAREST);
	MONITORINFO moninfo = MONITORINFO();
	moninfo.cbSize = sizeof(moninfo);
	if (!GetMonitorInfo(hMon, &moninfo))
	{
		throw L"GetMonitorInfo failed!";
	}

	const RECT& rcScreen = moninfo.rcMonitor;

	LONG l = GetWindowLong(wnd, GWL_STYLE);
	if (!l)
	{
		throw L"GetWindowLong failed!";
	}
	l &= ~(WS_CAPTION | WS_BORDER);

	if (!SetWindowLong(wnd, GWL_STYLE, l))
	{
		throw L"SetWindowLong failed!";
	}

	if (!SetWindowPos(wnd, HWND_TOP, 1, 1, rcScreen.right - 2, rcScreen.bottom - 2, SWP_FRAMECHANGED))
	{
		throw L"SetWindowPos failed!";
	}

	return rcScreen;
}

unsigned __stdcall CursorConfineThread(void* p)
{
	HWND wnd = NULL;
	RECT clip, clipOld;
	bool isActive = false;
	while (!g_stop)
	{
		if (!wnd)
		{
			wnd = FindWindow(L"Freelancer", L"Freelancer");
			if (wnd)
			{
				try
				{
					while (GetForegroundWindow() != wnd)
					{
						// wait for window
						Sleep(1);
					}
					// wait for full window init, otherwise it breaks
					Sleep(2000);
					clip = setupWnd(wnd);
					clip.left	+= 30;
					clip.right	-= 30;
					clip.top	+= 30;
					clip.bottom	-= 30;
					// immediately skip to next iteration without Sleeping to confine cursor
					continue;
				}
				catch (const wchar_t* err)
				{
					errorBox(err);
					return 1;
				}
			}
		}
		else if ((GetForegroundWindow() == wnd) != isActive)
		{
			isActive = !isActive;
			if (isActive)
			{
				GetClipCursor(&clipOld);
				ClipCursor(&clip);
			}
			else
			{
				ClipCursor(&clipOld);
			}
		}
		Sleep(1);
	}
	return 0;
}

bool init()
{
	int argc;
	LPWSTR* argv = CommandLineToArgvW(GetCommandLine(), &argc);
	if (!argv)
	{
		throw L"CommandLineToArgvW";
	}
	bool hasWndArg = false;
	for (int i = 0; i < argc; ++i)
	{
		if (!wcscmp(argv[i], L"-w")) {
			hasWndArg = true;
			break;
		}
	}
	LocalFree(argv);
	if (!hasWndArg)
	{
		return false;
	}

	HANDLE hThread = (HANDLE) _beginthreadex(NULL, 0, CursorConfineThread, NULL, 0, NULL);
	if (!hThread) 
	{
		throw L"_beginthreadex";
	}
	CloseHandle(hThread);
	return true;
}

BOOL CALLBACK DllMain(HINSTANCE hModule, DWORD fdwReason, LPVOID lpReserved)
{
	if (!lpReserved)
	{
		if (fdwReason == DLL_PROCESS_ATTACH)
		{
			DisableThreadLibraryCalls(hModule);
			try
			{
				return init();
			}
			catch (const wchar_t* err)
			{
				errorBox(err);
				return FALSE;
			}
		}
		else if (fdwReason == DLL_PROCESS_DETACH)
		{
			g_stop = true;
		}
	}
	return TRUE;
}
