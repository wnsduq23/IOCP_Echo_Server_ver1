#pragma once

// ��Ʈ��ũ I/O ����
enum class NET_TYPE { RECV, SEND };

// I/O overlapped ����ü Ȯ��
struct NetworkOverlapped
{
    OVERLAPPED _ovl;
    NET_TYPE _type;
    // �ʿ��� �߰� �ʵ尡 ������ �߰�
};

class Session
{
public:
    // ������: session ID, ����, Ŭ���̾�Ʈ �ּ� ����
    Session(__int64 id, SOCKET sock, SOCKADDR_IN addr)
        : _ID(id), _sock(sock), _clientAddr(addr), _recvBuf(MAX_BUFFER_SIZE), _sendBuf(MAX_BUFFER_SIZE),
          _IOCount(0), _sendFlag(0)
    {
        InitializeCriticalSection(&_cs);
        ZeroMemory(&_recvOvl, sizeof(_recvOvl));
        ZeroMemory(&_sendOvl, sizeof(_sendOvl));

        // WSABUF �迭 �ʱ�ȭ (�� ���� ���)
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

    // Public ��� ���� (���� ������Ʈ������ ĸ��ȭ�� ����� getter/setter ���)
    __int64 _ID;
    SOCKET _sock;
    SOCKADDR_IN _clientAddr;

    CRITICAL_SECTION _cs;

    // ���� �� �۽� ����
    RingBuffer _recvBuf;
    RingBuffer _sendBuf;

    // Overlapped I/O ����ü (����/�۽�)
    NetworkOverlapped _recvOvl;
    NetworkOverlapped _sendOvl;

    // WSABUF �迭 (I/O ��û �� ���)
    WSABUF _wsaRecvbuf[2];
    WSABUF _wsaSendbuf[2];

    // I/O ���� ī���� �� �÷���
    volatile LONG _IOCount = 0;
    volatile LONG _sendFlag = 0;

    // �߰������� �ʿ��� �Լ����� ���� ����
};
