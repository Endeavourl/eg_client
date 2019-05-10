#include <IO.H>
#include "EG_client.h"
#include "Preferences.h"

/// TODO:
/// make display options for widescreen
/// try to make dynamic windowed mode
/// lightning fix, engine fix
/// fix screen shaking
/// chat log conflicts?
/// decentralize headers
////////////////////////////////////////////////////////////////////////////////////////

HMODULE	hModSelf, hModFL;

//FILE* fLog;

////////////////////////////////////////////////////////////////////////////////////////

void DacomSelfInstall()
{
	wchar_t wszModPath[MAX_PATH];
	GetModuleFileName(hModSelf, wszModPath, MAX_PATH);

	std::wstring wscModPath(wszModPath);
	size_t posSep = wscModPath.find_last_of(L'\\');

	std::wstring wscIniPath = wscModPath.substr(0, posSep + 1) + L"dacom.ini";
	std::string scMod = wstos(wscModPath.substr(posSep + 1).c_str(), CP_ACP);

	std::ci_string scIni;
	FILE *fp = _wfopen(wscIniPath.c_str(), L"r+b");
	try
	{
		if (!fp)
			throw L"_wfopen";
		if (fseek(fp, 0, SEEK_END))
			throw L"fseek ";
		long fileSize = ftell(fp);
		if (EOF == fileSize)
			throw L"ftell";
		scIni.resize(fileSize);
		rewind(fp);
		if (fread(&scIni[0], 1, fileSize, fp) != fileSize)
			throw L"fread";

		size_t posSection = scIni.find("[libraries]");
		size_t posNext = scIni.find('[', posSection + 1);
		size_t posDll = scIni.find(scMod.c_str(), posSection + 12);
		if (std::string::npos == posDll || posDll > posNext)
		{
			scIni.insert(posNext, "\r\n");
			scIni.insert(posNext, scMod.c_str());
			rewind(fp);
			if (_chsize(_fileno(fp), 0))
				throw L"_chsize";
			if (fwrite(scIni.c_str(), 1, scIni.length(), fp) != scIni.length())
				throw L"fwrite";
		}
	}
	CATCH(L"DacomSelfInstall", DO_NOTHING)

	if (fp)
		fclose(fp);
}

BOOL CALLBACK DllMain(HINSTANCE hModule, DWORD fdwReason, LPVOID lpReserved)
{
	if(!lpReserved)
	{
		if(fdwReason == DLL_PROCESS_ATTACH)
		{
			/*
			fLog = fopen("_log.log", "a+t");
			if(!fLog)
				return FALSE;
			*/

			DisableThreadLibraryCalls(hModule);

			hModSelf = hModule;
			hModFL = GetModuleHandle(NULL);

			DacomSelfInstall();
			
			if(!InitPrefs())
				return FALSE;

			InitHacks();

			if(!InitHooks())
				return FALSE;
		}

		else if(fdwReason == DLL_PROCESS_DETACH)
		{
			/*
			if(fLog != NULL)
				fclose(fLog);
			*/
			UnloadHooks();
			UnloadHacks();
			UnloadPrefs();
		}
	}
    return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////
