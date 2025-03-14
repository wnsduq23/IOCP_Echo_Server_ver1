#pragma once

class CLanServer
{
public:
	CLanServer();
	~CLanServer();

	// Singleton instance accessor
	static CLanServer* GetInstance();

	// Thread entry point functions (to be used with _beginthreadex)
	static unsigned int WINAPI AcceptThread(void* arg);// static »©¸é ¾î¶»°ÔµÅ?
	static unsigned int WINAPI NetworkWorkerThread(void* arg);
	static unsigned int WINAPI ReleaseThread(void* arg);

	// I/O Completion handler functions
	void HandleRecvCP(__int64 sessionID, int recvBytes, int threadID);
	void HandleSendCP(__int64 sessionID, int sendBytes, int threadID);

	// Functions to post I/O requests
	void RecvPost(__int64 sessionID, int threadID);
	void SendPost(__int64 sessionID, int threadID);

	// Message processing functions
	void RecvDataToMsg(__int64 sessionID, int threadID);
	void MsgToSendData(__int64 sessionID, SerializePacket* packet, int threadID);

	// Mapping from thread ID to an index or identifier
	std::unordered_map<unsigned int, int> ThreadIDMap;

private:
	//for Completion Port Handle
	HANDLE _hNetworkCP;
	HANDLE _hReleaseCP;
	//for thread Handle
	HANDLE _releaseThread;
	HANDLE _acceptThread;
	HANDLE *_networkThreads;
	int _networkThreadCnt;

	SOCKET _listenSock = INVALID_SOCKET;

	// Session ID supplier for generating unique session IDs.
	UINT64 _sessionIDSupplier = 0;
};

extern CLanServer* g_Server;
extern std::unordered_map<UINT64, Session*>g_SessionMap;
extern SRWLOCK g_SessionMapLock;
