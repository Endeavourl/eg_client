#include "EG_client.h"
#include "Preferences.h"

////////////////////////////////////////////////////////////////////////////////////////

void (__stdcall* ReceiveChat_Trampoline)(UINT, UINT, ULONG, PVOID);

////////////////////////////////////////////////////////////////////////////////////////

static std::wstring XMLSpecialChars(const std::ci_wstring& wscText)
{
	std::wstring wscRet = L"";
	wscRet.reserve(wscText.length() + 2048);
	for(UINT i = 0; i < wscText.length(); i++)
	{
		switch(wscText[i])
		{
		case L'<':
			{
				wscRet.append(L"&#60;");
				break;
			}
		case L'>':
			{
				wscRet.append(L"&#62;");
				break;
			}
		case L'&':
			{
				wscRet.append(L"&#38;");
				break;
			}
		default:
			wscRet.append(1, wscText[i]);
		}
	}
	return wscRet;
}

////////////////////////////////////////////////////////////////////////////////////////

static void ShowCustomChat(const std::wstring& wscXML)
{
	try {
		RenderDisplayList rdl;
		XMLReader xmlr;

		std::wstring wscXMLFull;
		wscXMLFull.reserve(10240);
		wscXMLFull = L"<?xml version=\"1.0\" encoding=\"UTF-16\"?><RDL><PUSH/>";
		wscXMLFull += wscXML;
		wscXMLFull += L"<PARA/><POP/></RDL>\x000A\x000A";

		try {
			if(!xmlr.read_buffer(rdl, (PCHAR)wscXMLFull.c_str(), wscXMLFull.length()*2))
				throw L"XMLReader::read_buffer()";
		}
		CATCH(L"XMLReader", throw L"Exception while XML->RDL")

		char szBuf[0x8000];
		UINT iWritten;
		try {
			BinaryRDLWriter brdlw;
			brdlw.write_buffer(rdl, szBuf, sizeof(szBuf), iWritten);
		}
		CATCH(L"BinaryRDLWriter", throw L"Exception while RDL->BRDL")

		try {
			ReceiveChat_Trampoline(1, 0x00010000, iWritten, szBuf);
		}
		CATCH(L"ReceiveChat", throw L"Exception while showing chat")
	}
	CATCH(L"ShowCustomChat", DO_NOTHING)
}

////////////////////////////////////////////////////////////////////////////////////////

static void LogChat(UINT uiChannel, const std::ci_wstring& wscMessage)
{
	if(!g_Prefs->bLogChat())
		 return;

	char* szChannel = NULL;
	switch(uiChannel)
	{
	case 0x00010000:
		{
			szChannel = "UNIV";
			break;
		}
	case 0x00010003:
		{
			szChannel = "GROP";
			break;
		}
	case 0x00010001:
		{
			szChannel = "SYST";
			break;
		}
	default:
		{
			if(uiChannel <= 0xFFFF)
				szChannel = "PRIV";
			else
				szChannel = "UNKN";
			break;
		}
	}

	try {
		FILE* f =
			_wfopen(g_Prefs->wscChatLogPath().empty()? L"EG_chat.log" :
					g_Prefs->wscChatLogPath().c_str(), L"a+t");
		if(!f)
			throw L"_wfopen failed.";

		long ti = time(NULL);
		tm   *t = localtime(&ti);

		fprintf(f, "[%04d/%02d/%02d %02d:%02d:%02d]\t%s\t%s\n",
			t->tm_year+1900, t->tm_mon+1, t->tm_mday,
			t->tm_hour, t->tm_min, t->tm_sec,
			szChannel,
			wstos(wscMessage.c_str(), CP_UTF8).c_str());
		fclose(f);
	}
	CATCH(L"LogChat", DO_NOTHING)		
}

////////////////////////////////////////////////////////////////////////////////////////

void __stdcall ReceiveChat_Detoured(UINT p1, UINT uiChannel, ULONG ulSizeOfBRDL, PVOID pBRDL)
{
	if(uiChannel == 0x00010004)
	{
		(ReceiveChat_Trampoline)(p1, uiChannel, ulSizeOfBRDL, pBRDL);
		return;
	}

	wchar_t wszBuf[10240] = L"";
	try {
		try {
			BinaryRDLReader brdl;
			UINT uiRet;
			brdl.extract_text_from_buffer(wszBuf, sizeof(wszBuf), uiRet, (PCHAR)pBRDL,
				ulSizeOfBRDL);
		}
		CATCH(L"BinaryRDLReader", throw L"Exception while BRDL->TXT.")

		std::ci_wstring wscMsg = wszBuf;
		std::ci_wstring::size_type stDivider = wscMsg.find(L": ");
		std::ci_wstring wscSender = wscMsg.substr(0, stDivider);
		std::ci_wstring wscText = wscMsg.substr(stDivider+2);

		// console commands
		// "/clientcmd <param>" is redirected by flhook back to client as 
		// "CONSOLE: <param>" from uiChannel 0
		if(!uiChannel && (wscSender == L"CONSOLE"))
		{ // todo add settings change from ingame
			wchar_t* wszReply = NULL;
			if(wscText == L"%rehash")
			{
				g_Prefs->Load();
				wszReply = L"Settings are reloaded!";
			}
/*			else if(wscText==L"%qwe")
			{// testing

			}
*/
			if(wszReply)
			{
				std::wstring wscReply;
				wscReply.reserve(10240);
				wscReply += L"<TRA data=\"0x605CDE05\" mask=\"-1\"/><TEXT>EG Client</TEXT>"
							L"<TRA data=\"0x605CDE00\" mask=\"-1\"/><TEXT>: ";
				wscReply += wszReply;
				wscReply += L"</TEXT>";

				ShowCustomChat(wscReply);
				return;
			}
		}

		// nickname ignores
		// do not ignore messages from console and admins 
		if(uiChannel && (wscSender != L"CONSOLE") && (wscSender.find(L"[admin]") != 0))
		{
			for(CIgnoreList::const_iterator it = g_Prefs->Ignores().begin();
				it != g_Prefs->Ignores().end(); ++it)
			{
				if((wscSender == it->first) || 
					//full match
					((it->second & 0x2) && (wscSender.find(it->first) != std::ci_wstring::npos)))
					//partial match and flag set
				{
					if(!(it->second & 0x1))
						return; //full ignore, private flag not set
					if(uiChannel <= 0xFFFF)
						return; //private only ignore
				}
			}
		}

		// logging
		LogChat(uiChannel, wscMsg);

		// custom chat styles
		DWORD dwStyle = 0;
		wchar_t *wszSenderColor, *wszTextColor;

		if(wscSender == L"CONSOLE") wszSenderColor = L"00FF00";
		else wszSenderColor = L"FFFFFF";

		if((uiChannel == 0x00010000) && g_Prefs->dwUniverseChatFont())
		{
			wszTextColor = L"FFFFFF";
			dwStyle = g_Prefs->dwUniverseChatFont();
		}
		else if((uiChannel == 0x00010003) && g_Prefs->dwGroupChatFont())
		{
			wszTextColor = L"FF7BFF";
			dwStyle = g_Prefs->dwGroupChatFont();
		}
		else if((uiChannel == 0x00010001) && g_Prefs->dwSystemChatFont())
		{
			wszTextColor = L"E6C684";
			dwStyle = g_Prefs->dwSystemChatFont();
		}
		else if((uiChannel <= 0xFFFF) && g_Prefs->dwPrivateChatFont())
		{
			wszTextColor = L"19BD3A";
			dwStyle = g_Prefs->dwPrivateChatFont();
		}

		if(dwStyle)
		{
			wchar_t wszStyle[8];
			swprintf(wszStyle, L"%02X", dwStyle);

			std::wstring wscCustomMsg;
			wscCustomMsg.reserve(10240);
			wscCustomMsg = L"<TRA data=\"0x";
			wscCustomMsg += wszSenderColor;
			wscCustomMsg += wszStyle;
			wscCustomMsg += L"\" mask=\"-1\"/><TEXT>";
			wscCustomMsg += XMLSpecialChars(wscSender);
			wscCustomMsg += L": </TEXT><TRA data=\"0x";
			wscCustomMsg += wszTextColor;
			wscCustomMsg += wszStyle;
			wscCustomMsg += L"\" mask=\"-1\"/><TEXT>";
			wscCustomMsg += XMLSpecialChars(wscText);
			wscCustomMsg += L"</TEXT>";

			ShowCustomChat(wscCustomMsg);
			return;
		}
	}
	CATCH(L"ReceiveChat", DO_NOTHING)

	(ReceiveChat_Trampoline)(p1, uiChannel, ulSizeOfBRDL, pBRDL);
}

////////////////////////////////////////////////////////////////////////////////////////
