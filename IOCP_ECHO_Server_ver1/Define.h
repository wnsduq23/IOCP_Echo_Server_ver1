#pragma once

#define dfSERVER_PORT  6000

// 프로토콜: 헤더 길이 2 Byte, 데이터 길이 8 Byte (에코)
#define dfHEADER_LEN sizeof(stHeader)
//#define dfDATA_LEN 8

struct stHeader
{
	short _shLen;
};
// 기타 정의
// 예: 최대 버퍼 크기 (필요 시 수정)
#define MAX_BUFFER_SIZE 1024

