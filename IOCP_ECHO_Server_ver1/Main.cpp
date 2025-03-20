#include "pch.h"
#include "Session.h"
#include "CLanServer.h"
#include "CEchoServer.h"
#include "Main.h"

CLanServer* g_Server;
std::unordered_map<UINT64, Session*>g_SessionMap;
SRWLOCK g_SessionMapLock;

bool g_bShutdown = false;
int main()
{   
    // 서버 인스턴스 생성
	g_Server = new CEchoServer;

	g_Server->Start();
    // 서버 실행 중 (g_bShutdown이 true가 될 때까지 루프)
	while (!g_bShutdown)
	{
		Sleep(1000);
		if (GetAsyncKeyState(VK_ESCAPE))
		{
			g_bShutdown = true;
		}
	}
    printf("서버 종료\n");

	return 0;
}