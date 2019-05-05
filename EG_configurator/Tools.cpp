#include "EG_configurator.h"

///
////////////////////////////////////////////////////////////////////////////////////////
///

UINT ToUINT(const wchar_t* wszStr)
{
	UINT iRet = wcstoul(wszStr, NULL, 10);
	return ((iRet==ULONG_MAX) && (errno==ERANGE))? 0 : iRet;
}

////////////////////////////////////////////////////////////////////////////////////////

UINT ToUINT(const char* szStr)
{
	UINT iRet = strtoul(szStr, NULL, 10);
	return (((iRet==LONG_MAX) || (iRet==LONG_MIN)) && (errno==ERANGE))? 0 : iRet;
}

////////////////////////////////////////////////////////////////////////////////////////

int ToInt(const char* szStr)
{
	int iRet = strtol(szStr, NULL, 10);
	return (((iRet==LONG_MAX) || (iRet==LONG_MIN)) && (errno==ERANGE))? 0 : iRet;
}

////////////////////////////////////////////////////////////////////////////////////////

int ToInt(const wchar_t* wszStr)
{
	int iRet = wcstol(wszStr, NULL, 10);
	return (((iRet==LONG_MAX) || (iRet==LONG_MIN)) && (errno==ERANGE))? 0 : iRet;
}

////////////////////////////////////////////////////////////////////////////////////////

float ToFloat(const char* szStr)
{
	double dRet = strtod(szStr, NULL);
	return (((dRet==HUGE_VAL) || (dRet==-HUGE_VAL)) && (errno==ERANGE))? 0.0 : (float)dRet;
}

////////////////////////////////////////////////////////////////////////////////////////

float ToFloat(const wchar_t* wszStr)
{
	double dRet = wcstod(wszStr, NULL);
	return (((dRet==HUGE_VAL) || (dRet==-HUGE_VAL)) && (errno==ERANGE))? 0.0 : (float)dRet;
}

////////////////////////////////////////////////////////////////////////////////////////

std::string wstos(wchar_t const* wszStr, UINT uiCP_TO)
{
	UINT uiSize = WideCharToMultiByte(uiCP_TO, 0, wszStr, -1, NULL, 0, NULL, NULL);

	char* szStr = new char[uiSize];
	if(!szStr)
		return "";

	WideCharToMultiByte(uiCP_TO, 0, wszStr, -1, szStr, uiSize, NULL, NULL);
	std::string scRet = szStr;

	delete[] szStr;
	return scRet;
}

////////////////////////////////////////////////////////////////////////////////////////

std::wstring stows(char const* szStr, UINT uiCP_FROM)
{
	UINT uiSize = MultiByteToWideChar(uiCP_FROM, 0, szStr, -1, NULL, 0);

	wchar_t* wszStr = new wchar_t[uiSize];
	if(!wszStr)
		return L"";

	MultiByteToWideChar(uiCP_FROM, 0, szStr, -1, wszStr, uiSize);
	std::wstring wscRet = wszStr;

	delete[] wszStr;
	return wscRet;
}

///
////////////////////////////////////////////////////////////////////////////////////////
///
