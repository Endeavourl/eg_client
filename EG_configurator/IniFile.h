#include "EG_configurator.h"

class CIniFile  
{
private:
	std::ci_wstring m_wszFileName;
	std::ci_wstring m_wszSection;

public:
	CIniFile(const wchar_t *wszFileName = NULL, const wchar_t *wszSection = NULL);

	void Init(const wchar_t *wszFileName = NULL, const wchar_t *wszSection = NULL);
	void SetSection(const wchar_t *wszSection);

	const wchar_t *GetFileName() { return m_wszFileName.c_str(); }
	const wchar_t *GetSection()  { return m_wszSection.c_str();  }

	std::ci_wstring	GetString(const wchar_t *wszName, const wchar_t *wszSection = NULL, const wchar_t *wszDefault = L"");
	int			GetInt   (const wchar_t *wszName, const wchar_t *wszSection = NULL, int	nDefault = 0);
	bool		GetBool  (const wchar_t *wszName, const wchar_t *wszSection = NULL, bool bDefault = true);
	bool		WriteString(const wchar_t *wszName, const wchar_t *wszValue, const wchar_t *wszSection = NULL);
	
	bool		WriteInt   (const wchar_t *wszName, int nValue,	const wchar_t *wszSection = NULL);
	
	bool		WriteBool  (const wchar_t *wszName, bool bValue, const wchar_t *wszSection = NULL);
};
