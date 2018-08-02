#pragma once

class _declspec(dllexport) CHashBase
{
public:
	CHashBase(void);
	virtual ~CHashBase(void);

public:
	virtual inline unsigned int HashDigestSize(void) = 0;

public:
	virtual bool InitHash(unsigned char* pBaseData = 0) = 0;
	virtual bool CalcHash(unsigned char* pBufferIn, int ulBufferInSize, unsigned char* pDigestOut) = 0;
};