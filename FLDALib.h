
class __declspec(dllimport) CDPClient
{
public:
	 CDPClient(class CDPClient const &);
	 CDPClient(void);
	 virtual ~CDPClient(void);
	 class CDPClient & operator=(class CDPClient const &);
	 bool AddConnectAttempt(unsigned short const *,unsigned short *);
	 void CancelEnums(void);
	 void Cleanup(void);
	 void Close(void);
	 void DispatchMsgs(unsigned long);
	 bool EnumerateHost(unsigned short const *,unsigned long,unsigned long,unsigned long,unsigned long);
	 bool EnumerateHosts(void);
	 struct IDirectPlay8Client * GetClient(void);
	 long GetConnectResult(void);
	 static unsigned long __cdecl GetLastMsgTimestamp(void);
	 static unsigned long __cdecl GetLinkQuality(void);
	 static unsigned long __cdecl GetPingDelay(void);
	 static unsigned long __cdecl GetSendQueueSize(void);
	 static bool __cdecl IsPingOutstanding(void);
	 bool ProcessConnectAttempt(void);
	 bool Send(unsigned char *,unsigned long);
	 void SetGUID(struct _GUID &);
	 static void __cdecl SetSourcePort(unsigned long);

protected:
	 bool ConnectToServer(unsigned short const *,unsigned short const *);
	 static long __stdcall HandleClientMsg(void *,unsigned long,void *);
	 static unsigned long  m_dwLastMsgReceivedTime;
	 static unsigned long  m_dwLinkQuality;
	 static unsigned long  m_dwPingLastTime;
	 static unsigned long  m_dwPingReceiveCount;
	 static unsigned long  m_dwPingReceiveTime;
	 static unsigned long  m_dwPingSendCount;
	 static unsigned long  m_dwPingSendTime;
	 static unsigned long  m_dwRoundTripTime;
	 static unsigned long  m_dwSourcePort;

public:
	unsigned char data[2048];
};

///
////////////////////////////////////////////////////////////////////////////////////////
///
