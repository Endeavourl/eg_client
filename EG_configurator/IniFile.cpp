// IniFile.cpp: implementation of the CIniFile class.
//
//////////////////////////////////////////////////////////////////////
#include "IniFile.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CIniFile::CIniFile(const wchar_t *wszFileName, const wchar_t *wszSection)
{
	Init(wszFileName, wszSection);
}

void CIniFile::Init(const wchar_t *wszFileName, const wchar_t *wszSection)
{
	if(wszFileName) m_wszFileName = wszFileName;
	if(wszSection)  m_wszSection  = wszSection;
}

void CIniFile::SetSection(const wchar_t *wszSection)
{
	if(wszSection) m_wszSection = wszSection;
}

std::ci_wstring CIniFile::GetString(const wchar_t *wszName, const wchar_t *wszSection, const wchar_t *wszDefault)
{
	if(wszSection && (m_wszSection != wszSection)) m_wszSection = wszSection;
	
	wchar_t wszBuffer[10240];
	GetPrivateProfileString(m_wszSection.c_str(), wszName, wszDefault, wszBuffer, (sizeof(wszBuffer)/sizeof(wchar_t)), m_wszFileName.c_str());
	return wszBuffer;
}

int	CIniFile::GetInt(const wchar_t *wszName, const wchar_t *wszSection, int nDefault)
{
	if(wszSection && m_wszSection != wszSection) m_wszSection = wszSection;
	return GetPrivateProfileInt(m_wszSection.c_str(), wszName, nDefault, m_wszFileName.c_str());
}
/*
double CIniFile::GetDouble( const char *szName, const char *szSection, double  dDefault )
{
	if( szSection && m_szSection != szSection ) m_szSection = szSection;

	ci_string value = GetString( szName, m_szSection.c_str());
	return value.empty() ? dDefault : atof(value.c_str());
}
*/
bool CIniFile::GetBool(const wchar_t *wszName, const wchar_t *wszSection, bool bDefault)
{
	if(wszSection && (m_wszSection != wszSection)) m_wszSection = wszSection;

	std::ci_wstring value = GetString(wszName, m_wszSection.c_str());
	return value.empty() ? bDefault	: 
		(value == L"1") || (value == L"y") || (value == L"yes") || (value == L"true");
}

bool CIniFile::WriteString(const wchar_t *wszName, const wchar_t *wszValue, const wchar_t *wszSection)
{
	if(wszSection && m_wszSection != wszSection) m_wszSection = wszSection;

	return TRUE == WritePrivateProfileString(m_wszSection.c_str(), wszName, wszValue, m_wszFileName.c_str());
}

bool CIniFile::WriteInt(const wchar_t *wszName, int nValue, const wchar_t *wszSection)
{
	if(wszSection && m_wszSection != wszSection) m_wszSection = wszSection;

	wchar_t wszBuffer[40];
	return WriteString(wszName, _itow(nValue, wszBuffer, 10), wszSection);
}
/*
bool CIniFile::WriteDouble( const char *szName, double dValue, const char *szSection )
{
	if( szSection && m_szSection != szSection ) m_szSection = szSection;
	
	char szBuffer[40];
	_snprintf( szBuffer, sizeof(szBuffer), "%.5f", dValue );

	return WriteString( szName, szBuffer, szSection );
}
*/
bool CIniFile::WriteBool(const wchar_t *wszName, bool bValue, const wchar_t *wszSection)
{
	if(wszSection && m_wszSection != wszSection) m_wszSection = wszSection;
	return WriteString(wszName, bValue ? L"true" : L"false", wszSection);
}
/*
void CIniFile::ReadSection( const char *szSection, ci_strings& values )
{
	char buffer[10240];
	GetPrivateProfileSection( szSection, buffer, sizeof(buffer), m_szFileName.c_str() );
	
	values.clear();
	for( char *p = buffer; *p; )
	{
		values.push_back(p);
		p += values.back().length()+1;
	}
}
*/