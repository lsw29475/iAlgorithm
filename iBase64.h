#pragma once

#include <windows.h>

class _declspec(dllexport) CBASE64
{
public:
	CBASE64(VOID);
	~CBASE64(VOID);

public:
	BOOL Base64Encode(BYTE* pBufferIn, int BufferInSize, BYTE* pBufferOut, int &BufferOutSize);
	BOOL Base64Decode(BYTE* pBufferIn, int BufferInSize, BYTE* pBufferOut, int &BufferOutSize);

private:
	static const BYTE Base64Table[64];
	BYTE ReverseBase64Table[256];
};