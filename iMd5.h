#pragma once

#include "iHashBase.h"

class _declspec(dllexport) CMD5 : public CHashBase
{
public:
	CMD5(VOID);
	~CMD5(VOID);

public:
	inline ULONG HashDigestSize(void)
	{
		return 16;
	}

private:
	ULONG BaseData[4];
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
	VOID Md5Calc();
};