#pragma once

#include <windows.h>

class _declspec(dllexport) CHashBase
{
public:
	CHashBase(VOID);
	virtual ~CHashBase(VOID);

public:
	virtual inline ULONG HashDigestSize(VOID) = 0;

public:
	virtual BOOL InitHash(BYTE* pBaseData = NULL) = 0;
	virtual BOOL CalcHash(BYTE* pBufferIn, int ulBufferInSize, BYTE* pDigestOut) = 0;
};