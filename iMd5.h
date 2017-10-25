#pragma once

#include "iHashBase.h"

class _declspec(dllexport) CMD5 : public CHashBase
{
public:
	CMD5(VOID);
	~CMD5(VOID);

public:
	inline unsigned int HashDigestSize(void)
	{
		return 16;
	}

private:
	unsigned int BaseData[4];
	unsigned int CalcData[16];

public:
	bool InitHash(unsigned char* pBaseData = NULL);
	bool CalcHash(unsigned char* pBufferIn, int BufferInSize, unsigned char* pDigestOut);

public:
	void GetBaseData(unsigned char* pBaseDataOut);

private:
	void SetBaseData(unsigned char* pBaseDataIn);
	void SetCalcData(unsigned char* pCalcDataIn);

private:
	void Md5Calc();
};