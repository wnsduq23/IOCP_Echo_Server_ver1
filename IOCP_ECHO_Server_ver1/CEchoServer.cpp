#include "pch.h"
#include "Session.h"
#include "CEchoServer.h"
#include "CLanServer.h"
//#include "SerializePacket.h"

CEchoServer* CEchoServer::GetInstance()
{
	static CEchoServer _CEchoServer;
	return &_CEchoServer;
}
bool CEchoServer::OnConnectionRequest(const WCHAR* ip, USHORT port)
{
	return true;
}

void CEchoServer::OnAccept(const UINT64 sessionID)
{
	// Ŭ���̾�Ʈ ���� ����
	// wprintf(L"[Content] Client Join : %lld\n", sessionID);
}

void CEchoServer::OnClientLeave(const UINT64 sessionID)
{
	// Ŭ���̾�Ʈ ���� ó��
	// wprintf(L"[Content] Client Leave : %lld\n", sessionID);
}

void CEchoServer::OnMessage(const UINT64 sessionID, SerializePacket* message, int threadID)
{
	// Content ��� Ȯ�� -> ó��
	// ������ �׳� ���

	__int64 num;
	*message >> num;
	// printf("[Content] Client ID : %lld, Recv Msg : %lld\n", sessionID, num);

	SerializePacket packet;
	//packet << (USHORT)sizeof(__int64) << num;
	packet << (SHORT)sizeof(__int64) << num;
	CLanServer::GetInstance()->MsgToSendData(sessionID, &packet, threadID);
}
