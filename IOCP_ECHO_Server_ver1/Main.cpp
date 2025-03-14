#include "pch.h"
#include "Session.h"
#include "CLanServer.h"
#include "CEchoServer.h"
#include "Main.h"

//CLanServer* g_LanServer;
std::unordered_map<UINT64, Session*>g_SessionMap;
SRWLOCK g_SessionMapLock;

bool g_bShutdown = false;
int main()
{   
    // ���� �ν��Ͻ� ���� (�̱���)
    CLanServer* g_LanServer = CLanServer::GetInstance();
	//CEchoServer* g_server = CEchoServer::GetInstance();

    // ���� ���� �� (g_bShutdown�� true�� �� ������ ����)
	while (!g_bShutdown)
	{
		YieldProcessor();
	}
    printf("���� ����\n");

	return 0;
}