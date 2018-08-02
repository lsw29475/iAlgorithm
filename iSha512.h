#pragma once

#include "iHashBase.h"

class _declspec(dllexport) CSHA512 : public CHashBase
{
public:
	CSHA512(void);
	~CSHA512(void);

public:
	inline unsigned int HashDigestSize(void)
	{
		return 64;
	}

private:
	unsigned long long BaseData[8];
	unsigned char CalcData[128];

public:
	bool InitHash(unsigned char* pBaseData = 0);
	bool CalcHash(unsigned char* pBufferIn, int BufferInSize, unsigned char* pDigestOut);

public:
	void GetBaseData(unsigned char* pBaseDataOut);

private:
	void SetBaseData(unsigned char* pBaseDataIn);
	void SetCalcData(unsigned char* pCalcDataIn);

private:
	void Sha512Calc();

};