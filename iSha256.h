#pragma once

#include "iHashBase.h"

class _declspec(dllexport) CSHA256 : public CHashBase
{
public:
	CSHA256(void);
	~CSHA256(void);

public:
	inline unsigned int HashDigestSize(void)
	{
		return 64;
	}

private:
	unsigned int BaseData[8];
	unsigned char CalcData[64];

public:
	bool InitHash(unsigned char* pBaseData = 0);
	bool CalcHash(unsigned char* pBufferIn, int BufferInSize, unsigned char* pDigestOut);

public:
	void GetBaseData(unsigned char* pBaseDataOut);

private:
	void SetBaseData(unsigned char* pBaseDataIn);
	void SetCalcData(unsigned char* pCalcDataIn);

private:
	void Sha256Calc();

};