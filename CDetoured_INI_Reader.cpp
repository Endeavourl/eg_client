#include "CDetoured_INI_Reader.h"
#include "Preferences.h"

////////////////////////////////////////////////////////////////////////////////////////

static std::ci_string scFXNickname;

float (CDetoured_INI_Reader::* get_value_float_Trampoline)(unsigned int iNum);
const char* (CDetoured_INI_Reader::* get_value_string_Trampoline)(void);

////////////////////////////////////////////////////////////////////////////////////////

float CDetoured_INI_Reader::get_value_float_Detoured(unsigned int iNum)
{
	float fValue = (this->* get_value_float_Trampoline)(iNum);

	// Ships, solars, simples, equips and all that stuff
	// looking for 'LODRanges' in different sections
	if(g_Prefs->bHRLODs() && is_value("LODranges"))
	{
		fValue *= 2.0f;

		if(is_header("Ship") || is_header("CargoPod"))
			fValue *= 2.5f;
		else if(is_header("Solar"))
			fValue *= 4.0f;
	}

	// Asteroids spawn range in fields
	// looking for 'fill_dist' in [Field] sections
	else if(g_Prefs->bHRAsteroids() && is_header("Field") && is_value("fill_dist"))
	{		
		fValue *= 2.5f;
		if(fValue > 3800.0f)
			fValue = 3800.0f;
	}

	// gfx
	// looking for second value of 'pbubble' in [EffectType] sections
	else if(g_Prefs->bHRGFX() && (iNum == 1) && is_header("EffectType") && is_value("pbubble"))
	{
		fValue *= 5.0f;

		if((scFXNickname == "EFT_WEAPON_IMPACT") || (scFXNickname == "EFT_LANE_SHIP_TRAVEL"))
			fValue *= 2.0f;

		else if((scFXNickname == "EFT_ENGINE_FIRE") || (scFXNickname == "EFT_ENGINE_THRUSTER"))
			fValue *= 4.0f;
	}

	return fValue;
}

////////////////////////////////////////////////////////////////////////////////////////

const char* CDetoured_INI_Reader::get_value_string_Detoured(void)
{
	const char* pszStr = (this->* get_value_string_Trampoline)();

	if(pszStr && g_Prefs->bHRGFX() && is_header("EffectType") && is_value("nickname"))
	{
		scFXNickname.reserve(4096);
		scFXNickname = pszStr;
	}

	return pszStr;
}

////////////////////////////////////////////////////////////////////////////////////////
