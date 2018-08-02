#include "iMd5.h"
#include "macro.h"
#include <memory.h>

#define F(x,y,z) ((x & y) | ((~x) & z))
#define G(x,y,z) ((x & z) | (y & (~z)))
#define H(x,y,z) (x ^ y ^ z)
#define I(x,y,z) (y ^ (x | (~z)))

void FF(unsigned int &a, unsigned int b, unsigned int c, unsigned int d, unsigned int Mj, unsigned int s, unsigned int ti)
{
	a = b + ROL(a + F(b, c, d) + Mj + ti, s);
}

void GG(unsigned int &a, unsigned int b, unsigned int c, unsigned int d, unsigned int Mj, unsigned int s, unsigned int ti)
{
	a = b + ROL(a + G(b, c, d) + Mj + ti, s);
}

void HH(unsigned int &a, unsigned int b, unsigned int c, unsigned int d, unsigned int Mj, unsigned int s, unsigned int ti)
{
	a = b + ROL(a + H(b, c, d) + Mj + ti, s);
}

void II(unsigned int &a, unsigned int b, unsigned int c, unsigned int d, unsigned int Mj, unsigned int s, unsigned int ti)
{
	a = b + ROL(a + I(b, c, d) + Mj + ti, s);
}

CMD5::CMD5(void)
{

}

CMD5::~CMD5(void)
{

}

void CMD5::SetBaseData(unsigned char* pBaseDataIn)
{
	memcpy(BaseData, pBaseDataIn, 16);
}

void CMD5::GetBaseData(unsigned char* pBaseDataOut)
{
	memcpy(pBaseDataOut, BaseData, 16);
}

void CMD5::SetCalcData(unsigned char* pCalcDataIn)
{
	memcpy(CalcData, pCalcDataIn, 64);
}

bool CMD5::InitHash(unsigned char* pBaseData)
{
	unsigned char InitData[16] = {
		0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF, 0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10
	};

	if (!pBaseData)
	{
		SetBaseData(InitData);
	}
	else
	{
		SetBaseData(pBaseData);
	}

	return true;
}

bool CMD5::CalcHash(unsigned char* pBufferIn, int BufferInSize, unsigned char* pDigestOut)
{
	unsigned int DataBuf[16] = { 0x00 };
	int LastSize;
	int i;

	if (!pBufferIn || BufferInSize <= 0)
	{
		return false;
	}

	LastSize = BufferInSize;
	for (i = 0; LastSize >= 0; i++, LastSize -= 64)
	{
		if (LastSize >= 64)
		{
			memset(DataBuf, 0x00, sizeof(DataBuf));
			memcpy(DataBuf, pBufferIn + i * 64, sizeof(DataBuf));
			SetCalcData((unsigned char*)DataBuf);
			Md5Calc();
		}
		else if (LastSize < 64 && LastSize >= 56)
		{
			memset(DataBuf, 0x00, sizeof(DataBuf));
			memcpy(DataBuf, pBufferIn + i * 64, LastSize);
			*(unsigned char*)((unsigned char*)DataBuf + LastSize) = 0x80;
			SetCalcData((unsigned char*)DataBuf);
			Md5Calc();

			memset(DataBuf, 0x00, sizeof(DataBuf));
			*(unsigned long long*)((unsigned char*)DataBuf + 56) = BufferInSize * 8;
			SetCalcData((unsigned char*)DataBuf);
			Md5Calc();
		}
		else if (LastSize < 56)
		{
			memset(DataBuf, 0x00, sizeof(DataBuf));
			memcpy(DataBuf, pBufferIn + i * 64, LastSize);
			*(unsigned char*)((unsigned char*)DataBuf + LastSize) = 0x80;
			*(unsigned long long*)((unsigned char*)DataBuf + 56) = BufferInSize * 8;
			SetCalcData((unsigned char*)DataBuf);
			Md5Calc();
		}
	}

	GetBaseData(pDigestOut);

	return true;
}

void CMD5::Md5Calc()
{
	unsigned int a = BaseData[0];
	unsigned int b = BaseData[1];
	unsigned int c = BaseData[2];
	unsigned int d = BaseData[3];

	FF(a, b, c, d, CalcData[0], 7, 0xd76aa478);
	FF(d, a, b, c, CalcData[1], 12, 0xe8c7b756);
	FF(c, d, a, b, CalcData[2], 17, 0x242070db);
	FF(b, c, d, a, CalcData[3], 22, 0xc1bdceee);
	FF(a, b, c, d, CalcData[4], 7, 0xf57c0faf);
	FF(d, a, b, c, CalcData[5], 12, 0x4787c62a);
	FF(c, d, a, b, CalcData[6], 17, 0xa8304613);
	FF(b, c, d, a, CalcData[7], 22, 0xfd469501);
	FF(a, b, c, d, CalcData[8], 7, 0x698098d8);
	FF(d, a, b, c, CalcData[9], 12, 0x8b44f7af);
	FF(c, d, a, b, CalcData[10], 17, 0xffff5bb1);
	FF(b, c, d, a, CalcData[11], 22, 0x895cd7be);
	FF(a, b, c, d, CalcData[12], 7, 0x6b901122);
	FF(d, a, b, c, CalcData[13], 12, 0xfd987193);
	FF(c, d, a, b, CalcData[14], 17, 0xa679438e);
	FF(b, c, d, a, CalcData[15], 22, 0x49b40821);

	GG(a, b, c, d, CalcData[1], 5, 0xf61e2562);
	GG(d, a, b, c, CalcData[6], 9, 0xc040b340);
	GG(c, d, a, b, CalcData[11], 14, 0x265e5a51);
	GG(b, c, d, a, CalcData[0], 20, 0xe9b6c7aa);
	GG(a, b, c, d, CalcData[5], 5, 0xd62f105d);
	GG(d, a, b, c, CalcData[10], 9, 0x02441453);
	GG(c, d, a, b, CalcData[15], 14, 0xd8a1e681);
	GG(b, c, d, a, CalcData[4], 20, 0xe7d3fbc8);
	GG(a, b, c, d, CalcData[9], 5, 0x21e1cde6);
	GG(d, a, b, c, CalcData[14], 9, 0xc33707d6);
	GG(c, d, a, b, CalcData[3], 14, 0xf4d50d87);
	GG(b, c, d, a, CalcData[8], 20, 0x455a14ed);
	GG(a, b, c, d, CalcData[13], 5, 0xa9e3e905);
	GG(d, a, b, c, CalcData[2], 9, 0xfcefa3f8);
	GG(c, d, a, b, CalcData[7], 14, 0x676f02d9);
	GG(b, c, d, a, CalcData[12], 20, 0x8d2a4c8a);

	HH(a, b, c, d, CalcData[5], 4, 0xfffa3942);
	HH(d, a, b, c, CalcData[8], 11, 0x8771f681);
	HH(c, d, a, b, CalcData[11], 16, 0x6d9d6122);
	HH(b, c, d, a, CalcData[14], 23, 0xfde5380c);
	HH(a, b, c, d, CalcData[1], 4, 0xa4beea44);
	HH(d, a, b, c, CalcData[4], 11, 0x4bdecfa9);
	HH(c, d, a, b, CalcData[7], 16, 0xf6bb4b60);
	HH(b, c, d, a, CalcData[10], 23, 0xbebfbc70);
	HH(a, b, c, d, CalcData[13], 4, 0x289b7ec6);
	HH(d, a, b, c, CalcData[0], 11, 0xeaa127fa);
	HH(c, d, a, b, CalcData[3], 16, 0xd4ef3085);
	HH(b, c, d, a, CalcData[6], 23, 0x04881d05);
	HH(a, b, c, d, CalcData[9], 4, 0xd9d4d039);
	HH(d, a, b, c, CalcData[12], 11, 0xe6db99e5);
	HH(c, d, a, b, CalcData[15], 16, 0x1fa27cf8);
	HH(b, c, d, a, CalcData[2], 23, 0xc4ac5665);

	II(a, b, c, d, CalcData[0], 6, 0xf4292244);
	II(d, a, b, c, CalcData[7], 10, 0x432aff97);
	II(c, d, a, b, CalcData[14], 15, 0xab9423a7);
	II(b, c, d, a, CalcData[5], 21, 0xfc93a039);
	II(a, b, c, d, CalcData[12], 6, 0x655b59c3);
	II(d, a, b, c, CalcData[3], 10, 0x8f0ccc92);
	II(c, d, a, b, CalcData[10], 15, 0xffeff47d);
	II(b, c, d, a, CalcData[1], 21, 0x85845dd1);
	II(a, b, c, d, CalcData[8], 6, 0x6fa87e4f);
	II(d, a, b, c, CalcData[15], 10, 0xfe2ce6e0);
	II(c, d, a, b, CalcData[6], 15, 0xa3014314);
	II(b, c, d, a, CalcData[13], 21, 0x4e0811a1);
	II(a, b, c, d, CalcData[4], 6, 0xf7537e82);
	II(d, a, b, c, CalcData[11], 10, 0xbd3af235);
	II(c, d, a, b, CalcData[2], 15, 0x2ad7d2bb);
	II(b, c, d, a, CalcData[9], 21, 0xeb86d391);

	BaseData[0] += a;
	BaseData[1] += b;
	BaseData[2] += c;
	BaseData[3] += d;
}