#pragma once

#include <windows.h>

class _declspec(dllexport) CHashBase
{
public:
	CHashBase(VOID);
	virtual ~CHashBase(VOID);

public:
	virtual inline unsigned int HashDigestSize(VOID) = 0;

public:
	virtual bool InitHash(unsigned char* pBaseData = NULL) = 0;
	virtual bool CalcHash(unsigned char* pBufferIn, int ulBufferInSize, unsigned char* pDigestOut) = 0;
};