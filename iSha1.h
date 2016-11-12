#pragma once

#include "iHashBase.h"

class _declspec(dllexport) CSHA1 : public CHashBase
{
public:
	CSHA1(VOID);
	~CSHA1(VOID);

public:
	inline ULONG HashDigestSize(void)
	{
		return 20;
	}

private:
	ULONG BaseData[5];
	ULONG CalcData[16];

public:
	BOOL InitHash(BYTE* pBaseData = NULL);
	BOOL CalcHash(BYTE* pBufferIn, int BufferInSize, BYTE* pDigestOut);

public:
	VOID GetBaseData(BYTE* pBaseDataOut);

private:
	VOID SetBaseData(BYTE* pBaseDataIn);
	VOID SetCalcData(BYTE* pCalcDataIn);

private:
	VOID Sha1Calc();
};