#include "IniFile.h"

CIniFile::CIniFile(const wchar_t *wszFileName, const wchar_t *wszSection)
{
	Init(wszFileName, wszSection);
}

void CIniFile::Init(const wchar_t *wszFileName, const wchar_t *wszSection)
{
	if(wszFileName) wscFileName_ = wszFileName;
	if(wszSection)  wscSection_  = wszSection;
}

void CIniFile::SetSection(const wchar_t *wszSection)
{
	if(wszSection) wscSection_ = wszSection;
}

std::ci_wstring	CIniFile::GetString(const wchar_t *wszName, const wchar_t *wszDefault) const
{
	wchar_t wszBuffer[10240];
	GetPrivateProfileString(wscSection_.c_str(), wszName, wszDefault, wszBuffer, sizeof(wszBuffer)/sizeof(wchar_t), wscFileName_.c_str());
	return wszBuffer;
}

int	CIniFile::GetInt(const wchar_t *wszName, int nDefault) const
{
	return GetPrivateProfileInt(wscSection_.c_str(), wszName, nDefault, wscFileName_.c_str());
}

bool CIniFile::GetBool(const wchar_t *wszName, bool bDefault) const
{
	std::ci_wstring value = GetString(wszName);
	return value.empty()? bDefault : ((value == L"1") || (value == L"y") || (value == L"yes") || (value == L"true"));
}
