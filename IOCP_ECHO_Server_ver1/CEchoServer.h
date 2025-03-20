#pragma once
#include "CLanServer.h"
class CEchoServer : public CLanServer
{
public:
	//static CEchoServer* GetInstance();
	bool OnConnectionRequest(const WCHAR* ip, USHORT port);
	void OnAccept(const UINT64 sessionID); // Accept �� ���� ó�� �Ϸ� �� ȣ��
	void OnClientLeave(const UINT64 sessionID); // Release �� ȣ��
	void OnMessage(const UINT64 sessionID, SerializePacket* message, int threadID);
};
