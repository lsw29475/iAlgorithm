#pragma once

#include "iHashBase.h"

class _declspec(dllexport) CSHA1 : public CHashBase
{
public:
	CSHA1(VOID);
	~CSHA1(VOID);

public:
	inline unsigned int HashDigestSize(void)
	{
		return 20;
	}

private:
	unsigned int BaseData[5];
	unsigned int CalcData[16];

public:
	bool InitHash(unsigned char* pBaseData = NULL);
	bool CalcHash(unsigned char* pBufferIn, int BufferInSize, unsigned char* pDigestOut);

public:
	VOID GetBaseData(unsigned char* pBaseDataOut);

private:
	VOID SetBaseData(unsigned char* pBaseDataIn);
	VOID SetCalcData(unsigned char* pCalcDataIn);

private:
	VOID Sha1Calc();
};