#include "iSha256.h"
#include "macro.h"

static const unsigned int K[64] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b,
	0x59f111f1, 0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01,
	0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7,
	0xc19bf174, 0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
	0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da, 0x983e5152,
	0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
	0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc,
	0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819,
	0xd6990624, 0xf40e3585, 0x106aa070, 0x19a4c116, 0x1e376c08,
	0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f,
	0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

#define STORE32(x, y)                                                                     \
     { (y)[0] = (uint8_t)(((x)>>24)&255); (y)[1] = (uint8_t)(((x)>>16)&255);   \
       (y)[2] = (uint8_t)(((x)>>8)&255); (y)[3] = (uint8_t)((x)&255); }

#define LOAD32(x, y)                            \
     { x = ((uint32_t)((y)[0] & 255)<<24) | \
           ((uint32_t)((y)[1] & 255)<<16) | \
           ((uint32_t)((y)[2] & 255)<<8)  | \
           ((uint32_t)((y)[3] & 255)); }

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
#define H(x) (ROR(x, 2) ^ ROR(x, 13) ^ ROR(x, 22))
#define I(x) (ROR(x, 6) ^ ROR(x, 11) ^ ROR(x, 25))
#define J(x) (ROR(x, 7) ^ ROR(x, 18) ^ SHR(x, 3))
#define L(x) (ROR(x, 17) ^ ROR(x, 19) ^ SHR(x, 10))

#define Sha256Round( a, b, c, d, e, f, g, h, i)     \
    t0 = h + I(e) + F(e, f, g) + K[i] + W[i];             \
    t1 = H(a) + G(a, b, c);                            \
    d += t0;                                           \
    h = t0 + t1;

CSHA256::CSHA256(void)
{

}

CSHA256::~CSHA256(void)
{

}

void CSHA256::SetBaseData(unsigned char* pBaseDataIn)
{
	memcpy(BaseData, pBaseDataIn, 32);
}

void CSHA256::GetBaseData(unsigned char* pBaseDataOut)
{
	for (int i = 0; i < 8; i++)
	{
		STORE32(BaseData[i], pBaseDataOut + 4 * i);
	}
}

void CSHA256::SetCalcData(unsigned char* pCalcDataIn)
{
	memcpy(CalcData, pCalcDataIn, 64);
}

bool CSHA256::InitHash(unsigned char* pBaseData /* = NULL */)
{
	unsigned char InitData[32] = {
		0x67, 0xE6, 0x09, 0x6A, 0x85, 0xAE, 0x67, 0xBB, 0x72, 0xF3, 0x6E, 0x3C, 0x3A, 0xF5, 0x4F, 0xA5,
		0x7F, 0x52, 0x0E, 0x51, 0x8C, 0x68, 0x05, 0x9B, 0xAB, 0xD9, 0x83, 0x1F, 0x19, 0xCD, 0xE0, 0x5B,

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

bool CSHA256::CalcHash(unsigned char* pBufferIn, int BufferInSize, unsigned char* pDigestOut)
{
	unsigned char DataBuf[64] = { 0x00 };
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
			Sha256Calc();
		}
		else if (LastSize < 64 && LastSize >= 56)
		{
			memset(DataBuf, 0x00, sizeof(DataBuf));
			memcpy(DataBuf, pBufferIn + i * 64, LastSize);
			*(unsigned char*)((unsigned char*)DataBuf + LastSize) = 0x80;
			SetCalcData((unsigned char*)DataBuf);
			Sha256Calc();

			memset(DataBuf, 0x00, sizeof(DataBuf));
			*(unsigned long long*)((unsigned char*)DataBuf + 56) = Tranverse64(BufferInSize * 8);
			SetCalcData((unsigned char*)DataBuf);
			Sha256Calc();
		}
		else if (LastSize < 56)
		{
			memset(DataBuf, 0x00, sizeof(DataBuf));
			memcpy(DataBuf, pBufferIn + i * 64, LastSize);
			*(unsigned char*)((unsigned char*)DataBuf + LastSize) = 0x80;
			*(unsigned long long*)((unsigned char*)DataBuf + 56) = Tranverse64(BufferInSize * 8);
			SetCalcData((unsigned char*)DataBuf);
			Sha256Calc();
		}
	}

	GetBaseData(pDigestOut);

	return true;
}

void CSHA256::Sha256Calc()
{
	unsigned int StateTemp[8] = { 0x00 };
	unsigned int W[64] = { 0x00 };
	unsigned int t0;
	unsigned int t1;
	unsigned int t;

	memcpy(StateTemp, BaseData, sizeof(BaseData));

	for (int i = 0; i < 16; i++)
	{
		LOAD32(W[i], CalcData + i * 4);
	}

	for (int i = 16; i < 64; i++)
	{
		W[i] = L(W[i - 2]) + W[i - 7] + J(W[i - 15]) + W[i - 16];
	}

	for (int i = 0; i < 64; i++)
	{
		Sha256Round(StateTemp[0], StateTemp[1], StateTemp[2], StateTemp[3], StateTemp[4], StateTemp[5], StateTemp[6], StateTemp[7], i);
		t = StateTemp[7];
		StateTemp[7] = StateTemp[6];
		StateTemp[6] = StateTemp[5];
		StateTemp[5] = StateTemp[4];
		StateTemp[4] = StateTemp[3];
		StateTemp[3] = StateTemp[2];
		StateTemp[2] = StateTemp[1];
		StateTemp[1] = StateTemp[0];
		StateTemp[0] = t;
	}

	for (int i = 0; i < 8; i++)
	{
		BaseData[i] = BaseData[i] + StateTemp[i];
	}
}