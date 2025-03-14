#pragma once
class CEchoServer
{
public:
	static CEchoServer* GetInstance();
	bool OnConnectionRequest(const WCHAR* ip, USHORT port);
	void OnAccept(const UINT64 sessionID); // Accept 후 접속 처리 완료 후 호출
	void OnClientLeave(const UINT64 sessionID); // Release 후 호출
	void OnMessage(const UINT64 sessionID, SerializePacket* message, int threadID);
};
