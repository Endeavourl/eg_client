#include "EG_client.h"
#include "Preferences.h"

////////////////////////////////////////////////////////////////////////////////////////

void HandleException(const wchar_t* wszWhere, const wchar_t* wszError)
{
	std::wstring wscError;
	wscError.reserve(2048);
	if(!wszError)
	{
		wscError = L"Unknown exception in ";
		wscError += wszWhere;
	}
	else
	{
		wscError = L"Exception in ";
		wscError += wszWhere;
		wscError += L", ";
		wscError += wszError;
	}

	FILE* fELog = 
		_wfopen(g_Prefs->wscExceptionLogFilename().empty()?	L"EG_client.log" : 
				g_Prefs->wscExceptionLogFilename().c_str(), L"a+t");
	if(fELog)
	{
		long ti = time(NULL);
		tm   *t = localtime(&ti);

		fprintf(fELog, "[%04d/%02d/%02d %02d:%02d:%02d]\t%s\n",
			t->tm_year+1900, t->tm_mon+1, t->tm_mday,
			t->tm_hour, t->tm_min, t->tm_sec, 
			wstos(wscError.c_str(), CP_UTF8).c_str());
		fclose(fELog);
	}
	else
		MessageBox(0, L"Error occurred while trying to open a log-file to log the following error: [press OK]",
			L"Critical Error",
			MB_ICONERROR);

	wscError = L"Error ocurred:\n\n" + wscError;
	wscError += L"\n\nPlease, send 'EG_client.log' file in your '<Freelancer>\\EXE' directory to EG MAIN HQ Administration, http://www.elite-games.ru/egmainhq/";
	MessageBox(0, wscError.c_str(), L"Error", MB_ICONERROR);
}

////////////////////////////////////////////////////////////////////////////////////////
