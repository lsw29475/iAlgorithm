#include "iRc4.h"
#include "macro.h"

CRC4::CRC4(VOID)
{
	pRC4Key = NULL;
	RC4KeySize = 0;

	pRC4StreamKey = NULL;
	RC4StreamKeySize = 0;
}

CRC4::~CRC4(VOID)
{
	if (pRC4Key)
	{
		delete[] pRC4Key;
		pRC4Key = NULL;
		RC4KeySize = 0;
	}

	if (pRC4StreamKey)
	{
		delete[] pRC4StreamKey;
		pRC4StreamKey = NULL;
		RC4StreamKeySize = 0;
	}
}

VOID CRC4::InitStateAndTemp()
{
	for (int i = 0; i < 256; i++)
	{
		State[i] = i;
		Temp[i] = pRC4Key[i % RC4KeySize];
	}
}

VOID CRC4::RangeState()
{
	int j = 0;
	BYTE tmp;

	for (int i = 0; i < 256; ++i)
	{
		j = (j + State[i] + Temp[i]) % 256;
		tmp = State[i];
		State[i] = State[j];    
		State[j] = tmp;
	}
}

VOID CRC4::KeyStream(int BufferLength)
{
	int i = 0, j = 0, t;
	BYTE tmp;

	if (pRC4StreamKey)
	{
		delete[] pRC4StreamKey;
		pRC4StreamKey = NULL;
		RC4StreamKeySize = 0;
	}

	pRC4StreamKey = new BYTE[BufferLength];
	memset(pRC4StreamKey, 0x00, BufferLength);
	RC4StreamKeySize = BufferLength;

	for (int n = 0; n < RC4StreamKeySize; n++)
	{
		i = (i + 1) % 256;
		j = (j + State[i]) % 256;

		tmp = State[i];
		State[i] = State[j];
		State[j] = tmp;

		t = (State[i] + State[j]) % 256;
		pRC4StreamKey[n] = State[t];
	}
}

BOOL CRC4::SetKey(BYTE* pKey, int KeySize)
{
	if (KeySize < 1 || KeySize > 256)
	{
		return FALSE;
	}

	if (pRC4Key)
	{
		delete[] pRC4Key;
		pRC4Key = NULL;
		KeySize = 0;
	}

	pRC4Key = new BYTE[KeySize];
	memset(pRC4Key, 0x00, KeySize);

	memcpy(pRC4Key, pKey, KeySize);
	RC4KeySize = KeySize;

	return TRUE;
}

BOOL CRC4::InitKey(BYTE* pKey, int KeySize)
{
	if (!SetKey(pKey, KeySize))
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CRC4::EncryptData(BYTE* pBufferIn, int BufferInSize, BYTE* pBufferOut, int BufferOutSize)
{
	if ((BufferOutSize != BufferInSize) && (BufferOutSize < BufferInSize))
	{
		return FALSE;
	}

	InitStateAndTemp();
	RangeState();
	KeyStream(BufferInSize);

	for (int i = 0; i < BufferInSize; i++)
	{
		pBufferOut[i] = pBufferIn[i] ^ pRC4StreamKey[i];
	}

	return TRUE;
}

BOOL CRC4::DecryptData(BYTE* pBufferIn, int BufferInSize, BYTE* pBufferOut, int BufferOutSize)
{
	if ((BufferOutSize != BufferInSize) && (BufferOutSize < BufferInSize))
	{
		return FALSE;
	}

	InitStateAndTemp();
	RangeState();
	KeyStream(BufferInSize);

	for (int i = 0; i < BufferInSize; i++)
	{
		pBufferOut[i] = pBufferIn[i] ^ pRC4StreamKey[i];
	}

	return TRUE;
}