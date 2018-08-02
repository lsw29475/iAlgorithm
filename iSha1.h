#pragma once

#include "iHashBase.h"

class _declspec(dllexport) CSHA1 : public CHashBase
{
public:
	CSHA1(void);
	~CSHA1(void);

public:
	inline unsigned int HashDigestSize(void)
	{
		return 20;
	}

private:
	unsigned int BaseData[5];
	unsigned int CalcData[16];

public:
	bool InitHash(unsigned char* pBaseData = 0);
	bool CalcHash(unsigned char* pBufferIn, int BufferInSize, unsigned char* pDigestOut);

public:
	void GetBaseData(unsigned char* pBaseDataOut);

private:
	void SetBaseData(unsigned char* pBaseDataIn);
	void SetCalcData(unsigned char* pCalcDataIn);

private:
	void Sha1Calc();
};