#pragma once

#pragma warning(disable: 26495)

// ���̺귯��
#pragma comment(lib, "ws2_32")
#pragma comment(lib, "mswsock.lib")

// ������
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <MSWSock.h>
#include <windows.h>
#include <process.h>

// C ��Ÿ�� ���̺귯��
#include <stdlib.h>
#include <stdio.h>

// std �ڷᱸ��
#include <unordered_map>
#include <map>
#include <vector>

#include "Define.h"
#include "RingBuffer.h"
#include "SerializePacket.h"
#include "SystemLog.h"

using namespace std;
