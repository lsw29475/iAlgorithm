#include "iRc4.h"
#include "macro.h"

CRC4::CRC4(void)
{
	pRC4Key = NULL;
	RC4KeySize = 0;

	pRC4StreamKey = NULL;
	RC4StreamKeySize = 0;
}

CRC4::~CRC4(void)
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

void CRC4::InitStateAndTemp()
{
	for (int i = 0; i < 256; i++)
	{
		State[i] = i;
		Temp[i] = pRC4Key[i % RC4KeySize];
	}
}

void CRC4::RangeState()
{
	int j = 0;
	unsigned char tmp;

	for (int i = 0; i < 256; ++i)
	{
		j = (j + State[i] + Temp[i]) % 256;
		tmp = State[i];
		State[i] = State[j];    
		State[j] = tmp;
	}
}

void CRC4::KeyStream(int BufferLength)
{
	int i = 0, j = 0, t;
	unsigned char tmp;

	if (pRC4StreamKey)
	{
		delete[] pRC4StreamKey;
		pRC4StreamKey = NULL;
		RC4StreamKeySize = 0;
	}

	pRC4StreamKey = new unsigned char[BufferLength];
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

bool CRC4::SetKey(unsigned char* pKey, int KeySize)
{
	if (KeySize < 1 || KeySize > 256)
	{
		return false;
	}

	if (pRC4Key)
	{
		delete[] pRC4Key;
		pRC4Key = NULL;
		KeySize = 0;
	}

	pRC4Key = new unsigned char[KeySize];
	memset(pRC4Key, 0x00, KeySize);

	memcpy(pRC4Key, pKey, KeySize);
	RC4KeySize = KeySize;

	return true;
}

bool CRC4::InitKey(unsigned char* pKey, int KeySize)
{
	if (!SetKey(pKey, KeySize))
	{
		return false;
	}

	return true;
}

bool CRC4::EncryptData(unsigned char* pBufferIn, int BufferInSize, unsigned char* pBufferOut, int BufferOutSize)
{
	if ((BufferOutSize != BufferInSize) && (BufferOutSize < BufferInSize))
	{
		return false;
	}

	InitStateAndTemp();
	RangeState();
	KeyStream(BufferInSize);

	for (int i = 0; i < BufferInSize; i++)
	{
		pBufferOut[i] = pBufferIn[i] ^ pRC4StreamKey[i];
	}

	return true;
}

bool CRC4::DecryptData(unsigned char* pBufferIn, int BufferInSize, unsigned char* pBufferOut, int BufferOutSize)
{
	if ((BufferOutSize != BufferInSize) && (BufferOutSize < BufferInSize))
	{
		return false;
	}

	InitStateAndTemp();
	RangeState();
	KeyStream(BufferInSize);

	for (int i = 0; i < BufferInSize; i++)
	{
		pBufferOut[i] = pBufferIn[i] ^ pRC4StreamKey[i];
	}

	return true;
}