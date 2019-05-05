#include "EG_client.h"

class CIniFile  
{
private:
	std::ci_wstring wscFileName_;
	std::ci_wstring wscSection_;

public:
	CIniFile(const wchar_t *wszFileName = NULL, const wchar_t *wszSection = NULL);

	void Init(const wchar_t *wszFileName = NULL, const wchar_t *wszSection = NULL);
	void SetSection(const wchar_t *wszSection);

	const wchar_t* GetFileName()const { return wscFileName_.c_str(); }
	const wchar_t* GetSection()	const { return wscSection_ .c_str(); }

	std::ci_wstring	GetString(const wchar_t *wszName, const wchar_t *wszDefault = NULL) const;
	int				GetInt   (const wchar_t *wszName, int nDefault = 0) const;
	bool			GetBool  (const wchar_t *wszName, bool bDefault = true) const;
};
