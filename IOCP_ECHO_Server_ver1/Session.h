#pragma once

// 네트워크 I/O 종류
enum class NET_TYPE { RECV, SEND };

// I/O overlapped 구조체 확장
struct NetworkOverlapped
{
    OVERLAPPED _ovl;
    NET_TYPE _type;
    // 필요한 추가 필드가 있으면 추가
};

class Session
{
public:
    // 생성자: session ID, 소켓, 클라이언트 주소 전달
    Session(__int64 id, SOCKET sock, SOCKADDR_IN addr)
        : _ID(id), _sock(sock), _clientAddr(addr), _recvBuf(MAX_BUFFER_SIZE), _sendBuf(MAX_BUFFER_SIZE),
          _IOCount(0), _sendFlag(0)
    {
        InitializeCriticalSection(&_cs);
        ZeroMemory(&_recvOvl, sizeof(_recvOvl));
        ZeroMemory(&_sendOvl, sizeof(_sendOvl));

        // WSABUF 배열 초기화 (두 버퍼 사용)
        _wsaRecvbuf[0].buf = nullptr;
        _wsaRecvbuf[0].len = 0;
        _wsaRecvbuf[1].buf = nullptr;
        _wsaRecvbuf[1].len = 0;

        _wsaSendbuf[0].buf = nullptr;
        _wsaSendbuf[0].len = 0;
        _wsaSendbuf[1].buf = nullptr;
        _wsaSendbuf[1].len = 0;
    }
    ~Session()
    {
        DeleteCriticalSection(&_cs);
    }

    // Public 멤버 변수 (실제 프로젝트에서는 캡슐화를 고려해 getter/setter 사용)
    __int64 _ID;
    SOCKET _sock;
    SOCKADDR_IN _clientAddr;

    CRITICAL_SECTION _cs;

    // 수신 및 송신 버퍼
    RingBuffer _recvBuf;
    RingBuffer _sendBuf;

    // Overlapped I/O 구조체 (수신/송신)
    NetworkOverlapped _recvOvl;
    NetworkOverlapped _sendOvl;

    // WSABUF 배열 (I/O 요청 시 사용)
    WSABUF _wsaRecvbuf[2];
    WSABUF _wsaSendbuf[2];

    // I/O 관련 카운터 및 플래그
    volatile LONG _IOCount = 0;
    volatile LONG _sendFlag = 0;

    // 추가적으로 필요한 함수들은 여기 선언
};
