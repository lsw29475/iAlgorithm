#include "iSha1.h"
#include "macro.h"

#define F(x,y,z) ((x & y) | ((~x) & z))
#define G(x,y,z) (x ^ y ^ z)
#define H(x,y,z) ((x & y) | (x & z) | (y & z)) 
#define I(x,y,z) (x ^ y ^ z)

CSHA1::CSHA1(VOID)
{

}

CSHA1::~CSHA1(VOID)
{

}

VOID CSHA1::SetBaseData(unsigned char* pBaseDataIn)
{
	memcpy(BaseData, pBaseDataIn, 20);
}

VOID CSHA1::GetBaseData(unsigned char* pBaseDataOut)
{
	memcpy(pBaseDataOut, BaseData, 20);
}

VOID CSHA1::SetCalcData(unsigned char* pCalcDataIn)
{
	memcpy(CalcData, pCalcDataIn, 64);
}

bool CSHA1::InitHash(unsigned char* pBaseData)
{
	unsigned char InitData[20] = { 
		0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF, 0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10, 0xF0, 0xE1, 0xD2, 0xC3
	};

	if (!pBaseData)
	{
		SetBaseData(InitData);
	}
	else
	{
		SetBaseData(pBaseData);
	}

	return TRUE;
}

bool CSHA1::CalcHash(unsigned char* pBufferIn, int BufferInSize, unsigned char* pDigestOut)
{
	unsigned int DataBuf[16];
	int LastSize;
	int i;

	if (!pBufferIn || BufferInSize <= 0)
	{
		return FALSE;
	}

	LastSize = BufferInSize;
	for (i = 0; LastSize >= 0; i++, LastSize -= (i * 64))
	{
		if (LastSize >= 64)
		{
			memset(DataBuf, 0x00, sizeof(DataBuf));
			memcpy(DataBuf, pBufferIn + i * 64, sizeof(DataBuf));
			SetCalcData((unsigned char*)DataBuf);
			Sha1Calc();
		}
		else if (LastSize < 64 && LastSize >= 56)
		{
			memset(DataBuf, 0x00, sizeof(DataBuf));
			memcpy(DataBuf, pBufferIn + i * 64, LastSize);
			*(unsigned char*)((unsigned char*)DataBuf + LastSize) = 0x80;
			SetCalcData((unsigned char*)DataBuf);
			Sha1Calc();

			memset(DataBuf, 0x00, sizeof(DataBuf));
			*(unsigned long long*)((unsigned char*)DataBuf + 56) = Tranverse64(BufferInSize * 8);
			SetCalcData((unsigned char*)DataBuf);
			Sha1Calc();
		}
		else if (LastSize < 56)
		{
			memset(DataBuf, 0x00, sizeof(DataBuf));
			memcpy(DataBuf, pBufferIn + i * 64, LastSize);
			*(unsigned char*)((unsigned char*)DataBuf + LastSize) = 0x80;
			*(unsigned long long*)((unsigned char*)DataBuf + 56) = Tranverse64(BufferInSize * 8);
			SetCalcData((unsigned char*)DataBuf);
			Sha1Calc();
		}
	}

	GetBaseData(pDigestOut);

	return TRUE;
}

VOID CSHA1::Sha1Calc()
{
	unsigned int W[80];
	int i;

	unsigned int a = BaseData[0];
	unsigned int b = BaseData[1];
	unsigned int c = BaseData[2];
	unsigned int d = BaseData[3];
	unsigned int e = BaseData[4];

	unsigned int Temp;

	for (i = 0; i < 16; i++)
	{
		W[i] = Tranverse32(CalcData[i]);
	}

	for (; i < 80; i++)
	{
		W[i] = ROL(W[i - 3] ^ W[i - 8] ^ W[i - 14] ^ W[i - 16], 1);
	}

	for (i = 0; i < 80; i++)
	{
		if (i >= 0 && i <= 19)
		{
			Temp = ROL(a, 5) + F(b, c, d) + e + W[i] + 0x5A827999;
		}
		else if (i >= 20 && i <= 39)
		{
			Temp = ROL(a, 5) + G(b, c, d) + e + W[i] + 0x6ED9EBA1;
		}
		else if (i >= 40 && i <= 59)
		{
			Temp = ROL(a, 5) + H(b, c, d) + e + W[i] + 0x8F1BBCDC;
		}
		else if (i >= 60 && i <= 79)
		{
			Temp = ROL(a, 5) + I(b, c, d) + e + W[i] + 0xCA62C1D6;
		}

		e = d;
		d = c;
		c = ROL(b, 30);
		b = a;
		a = Temp;
	}

	BaseData[0] += a;
	BaseData[1] += b;
	BaseData[2] += c;
	BaseData[3] += d;
	BaseData[4] += e;

	for (i = 0; i < 5; i++)
	{
		BaseData[i] = Tranverse32(BaseData[i]);
	}
}

