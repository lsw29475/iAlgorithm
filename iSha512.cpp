#include "iSha512.h"
#include "macro.h"

static const uint64_t K[80] = {
	0x428a2f98d728ae22, 0x7137449123ef65cd, 0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc,
	0x3956c25bf348b538, 0x59f111f1b605d019, 0x923f82a4af194f9b, 0xab1c5ed5da6d8118,
	0xd807aa98a3030242, 0x12835b0145706fbe, 0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2,
	0x72be5d74f27b896f, 0x80deb1fe3b1696b1, 0x9bdc06a725c71235, 0xc19bf174cf692694,
	0xe49b69c19ef14ad2, 0xefbe4786384f25e3, 0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65,
	0x2de92c6f592b0275, 0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4, 0x76f988da831153b5,
	0x983e5152ee66dfab, 0xa831c66d2db43210, 0xb00327c898fb213f, 0xbf597fc7beef0ee4,
	0xc6e00bf33da88fc2, 0xd5a79147930aa725, 0x06ca6351e003826f, 0x142929670a0e6e70,
	0x27b70a8546d22ffc, 0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed, 0x53380d139d95b3df,
	0x650a73548baf63de, 0x766a0abb3c77b2a8, 0x81c2c92e47edaee6, 0x92722c851482353b,
	0xa2bfe8a14cf10364, 0xa81a664bbc423001, 0xc24b8b70d0f89791, 0xc76c51a30654be30,
	0xd192e819d6ef5218, 0xd69906245565a910, 0xf40e35855771202a, 0x106aa07032bbd1b8,
	0x19a4c116b8d2d0c8, 0x1e376c085141ab53, 0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8,
	0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb, 0x5b9cca4f7763e373, 0x682e6ff3d6b2b8a3,
	0x748f82ee5defb2fc, 0x78a5636f43172f60, 0x84c87814a1f0ab72, 0x8cc702081a6439ec,
	0x90befffa23631e28, 0xa4506cebde82bde9, 0xbef9a3f7b2c67915, 0xc67178f2e372532b,
	0xca273eceea26619c, 0xd186b8c721c0c207, 0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178,
	0x06f067aa72176fba, 0x0a637dc5a2c898a6, 0x113f9804bef90dae, 0x1b710b35131c471b,
	0x28db77f523047d84, 0x32caab7b40c72493, 0x3c9ebe0a15c9bebc, 0x431d67c49c100d4c,
	0x4cc5d4becb3e42b6, 0x597f299cfc657e2a, 0x5fcb6fab3ad6faec, 0x6c44198c4a475817
};

#define LOAD64( x, y )                                                      \
   { x = (((uint64_t)((y)[0] & 255))<<56)|(((uint64_t)((y)[1] & 255))<<48) | \
         (((uint64_t)((y)[2] & 255))<<40)|(((uint64_t)((y)[3] & 255))<<32) | \
         (((uint64_t)((y)[4] & 255))<<24)|(((uint64_t)((y)[5] & 255))<<16) | \
         (((uint64_t)((y)[6] & 255))<<8)|(((uint64_t)((y)[7] & 255))); }

#define STORE64( x, y )                                                                     \
   { (y)[0] = (uint8_t)(((x)>>56)&255); (y)[1] = (uint8_t)(((x)>>48)&255);     \
     (y)[2] = (uint8_t)(((x)>>40)&255); (y)[3] = (uint8_t)(((x)>>32)&255);     \
     (y)[4] = (uint8_t)(((x)>>24)&255); (y)[5] = (uint8_t)(((x)>>16)&255);     \
     (y)[6] = (uint8_t)(((x)>>8)&255); (y)[7] = (uint8_t)((x)&255); }

#define F(x,y,z) (z ^ (x & (y ^ z)))
#define G(x,y,z) (((x | y) & z) | (x & y))
#define H(x) (ROR64(x, 28) ^ ROR64(x, 34) ^ ROR64(x, 39))
#define I(x) (ROR64(x, 14) ^ ROR64(x, 18) ^ ROR64(x, 41))
#define J(x) (ROR64(x, 1) ^ ROR64(x, 8) ^ SHR64(x, 7))
#define L(x) (ROR64(x, 19) ^ ROR64(x, 61) ^ SHR64(x, 6))

#define Sha512Round( a, b, c, d, e, f, g, h, i)     \
    t0 = h + I(e) + F(e, f, g) + K[i] + W[i];             \
    t1 = H(a) + G(a, b, c);                            \
    d += t0;                                           \
    h = t0 + t1;

CSHA512::CSHA512(void)
{

}

CSHA512::~CSHA512(void)
{

}

void CSHA512::SetBaseData(unsigned char* pBaseDataIn)
{
	memcpy(BaseData, pBaseDataIn, 64);
}

void CSHA512::GetBaseData(unsigned char* pBaseDataOut)
{
	for (int i = 0; i < 8; i++)
	{
		STORE64(BaseData[i], pBaseDataOut + 8 * i);
	}
}

void CSHA512::SetCalcData(unsigned char* pCalcDataIn)
{
	memcpy(CalcData, pCalcDataIn, 128);
}

bool CSHA512::InitHash(unsigned char* pBaseData /* = NULL */)
{
	unsigned char InitData[64] = {
		0x08, 0xC9, 0xBC, 0xF3, 0x67, 0xE6, 0x09, 0x6A, 0x3B, 0xA7, 0xCA, 0x84, 0x85, 0xAE, 0x67, 0xBB,
		0x2B, 0xF8, 0x94, 0xFE, 0x72, 0xF3, 0x6E, 0x3C, 0xF1, 0x36, 0x1D, 0x5F, 0x3A, 0xF5, 0x4F, 0xA5,
		0xD1, 0x82, 0xE6, 0xAD, 0x7F, 0x52, 0x0E, 0x51, 0x1F, 0x6C, 0x3E, 0x2B, 0x8C, 0x68, 0x05, 0x9B,
		0x6B, 0xBD, 0x41, 0xFB, 0xAB, 0xD9, 0x83, 0x1F, 0x79, 0x21, 0x7E, 0x13, 0x19, 0xCD, 0xE0, 0x5B
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

bool CSHA512::CalcHash(unsigned char* pBufferIn, int BufferInSize, unsigned char* pDigestOut)
{
	unsigned char DataBuf[128] = { 0x00 };
	int LastSize;
	int i;
	
	if (!pBufferIn || BufferInSize <= 0)
	{
		return false;
	}

	LastSize = BufferInSize;
	for (i = 0; LastSize >= 0; i++, LastSize -= 128)
	{
		if (LastSize >= 128)
		{
			memset(DataBuf, 0x00, sizeof(DataBuf));
			memcpy(DataBuf, pBufferIn + i * 128, sizeof(DataBuf));
			SetCalcData((unsigned char*)DataBuf);
			Sha512Calc();
		}
		else if (LastSize < 128 && LastSize >= 112)
		{
			memset(DataBuf, 0x00, sizeof(DataBuf));
			memcpy(DataBuf, pBufferIn + i * 128, LastSize);
			*(unsigned char*)((unsigned char*)DataBuf + LastSize) = 0x80;
			SetCalcData((unsigned char*)DataBuf);
			Sha512Calc();

			memset(DataBuf, 0x00, sizeof(DataBuf));
			*(unsigned long long*)((unsigned char*)DataBuf + 120) = Tranverse64(BufferInSize * 8);
			SetCalcData((unsigned char*)DataBuf);
			Sha512Calc();
		}
		else if (LastSize < 112)
		{
			memset(DataBuf, 0x00, sizeof(DataBuf));
			memcpy(DataBuf, pBufferIn + i * 128, LastSize);
			*(unsigned char*)((unsigned char*)DataBuf + LastSize) = 0x80;
			*(unsigned long long*)((unsigned char*)DataBuf + 120) = Tranverse64(BufferInSize * 8);
			SetCalcData((unsigned char*)DataBuf);
			Sha512Calc();
		}
	}

	GetBaseData(pDigestOut);

	return true;
}

void CSHA512::Sha512Calc()
{
	unsigned long long StateTemp[8] = { 0x00 };
	unsigned long long W[80] = { 0x00 };
	unsigned long long t0;
	unsigned long long t1;

	memcpy(StateTemp, BaseData, sizeof(BaseData));

	for (int i = 0; i < 16; i++)
	{
		LOAD64(W[i], CalcData + i * 8);
	}

	for (int i = 16; i < 80; i++)
	{
		W[i] = L(W[i - 2]) + W[i - 7] + J(W[i - 15]) + W[i - 16];
	}

	for (int i = 0; i < 80; i += 8)
	{
		Sha512Round(StateTemp[0], StateTemp[1], StateTemp[2], StateTemp[3], StateTemp[4], StateTemp[5], StateTemp[6], StateTemp[7], i + 0);
		Sha512Round(StateTemp[7], StateTemp[0], StateTemp[1], StateTemp[2], StateTemp[3], StateTemp[4], StateTemp[5], StateTemp[6], i + 1);
		Sha512Round(StateTemp[6], StateTemp[7], StateTemp[0], StateTemp[1], StateTemp[2], StateTemp[3], StateTemp[4], StateTemp[5], i + 2);
		Sha512Round(StateTemp[5], StateTemp[6], StateTemp[7], StateTemp[0], StateTemp[1], StateTemp[2], StateTemp[3], StateTemp[4], i + 3);
		Sha512Round(StateTemp[4], StateTemp[5], StateTemp[6], StateTemp[7], StateTemp[0], StateTemp[1], StateTemp[2], StateTemp[3], i + 4);
		Sha512Round(StateTemp[3], StateTemp[4], StateTemp[5], StateTemp[6], StateTemp[7], StateTemp[0], StateTemp[1], StateTemp[2], i + 5);
		Sha512Round(StateTemp[2], StateTemp[3], StateTemp[4], StateTemp[5], StateTemp[6], StateTemp[7], StateTemp[0], StateTemp[1], i + 6);
		Sha512Round(StateTemp[1], StateTemp[2], StateTemp[3], StateTemp[4], StateTemp[5], StateTemp[6], StateTemp[7], StateTemp[0], i + 7);
	}

	for (int i = 0; i < 8; i++)
	{
		BaseData[i] = BaseData[i] + StateTemp[i];
	}
}