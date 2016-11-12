#pragma once

#include <windows.h>

class _declspec(dllexport) CRC4
{
public:
	CRC4(VOID);
	~CRC4(VOID);

private:
	BYTE* pRC4Key;
	int RC4KeySize;

	BYTE* pRC4StreamKey;
	int RC4StreamKeySize;

	BYTE State[256];
	BYTE Temp[256];

public:
	inline ULONG KeyMaxSize(void)
	{
		return 256;
	}

	inline ULONG KeyMinSize(void)
	{
		return 1;
	}

public:
	BOOL InitKey(BYTE* pKey, int KeySize);
	BOOL EncryptData(BYTE* pBufferIn, int BufferInSize, BYTE* pBufferOut, int BufferOutSize);
	BOOL DecryptData(BYTE* pBufferIn, int BufferInSize, BYTE* pBufferOut, int BufferOutSize);

private:
	BOOL SetKey(BYTE* pKey, int KeySize);

private:
	VOID InitStateAndTemp();
	VOID RangeState();
	VOID KeyStream(int BufferLength);
};