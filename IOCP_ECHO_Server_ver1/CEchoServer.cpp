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
	// 클라이언트 정보 생성
	// wprintf(L"[Content] Client Join : %lld\n", sessionID);
}

void CEchoServer::OnClientLeave(const UINT64 sessionID)
{
	// 클라이언트 종료 처리
	// wprintf(L"[Content] Client Leave : %lld\n", sessionID);
}

void CEchoServer::OnMessage(const UINT64 sessionID, SerializePacket* message, int threadID)
{
	// Content 헤더 확인 -> 처리
	// 지금은 그냥 출력

	__int64 num;
	*message >> num;
	// printf("[Content] Client ID : %lld, Recv Msg : %lld\n", sessionID, num);

	SerializePacket packet;
	//packet << (USHORT)sizeof(__int64) << num;
	packet << (SHORT)sizeof(__int64) << num;
	CLanServer::GetInstance()->MsgToSendData(sessionID, &packet, threadID);
}
