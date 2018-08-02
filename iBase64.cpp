#include "iBase64.h"
#include <memory.h>

const unsigned char CBASE64::Base64Table[64] = {
	0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48,
	0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f, 0x50,
	0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58,
	0x59, 0x5a, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66,
	0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e,
	0x6f, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76,
	0x77, 0x78, 0x79, 0x7a, 0x30, 0x31, 0x32, 0x33,
	0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x2b, 0x2f
};

CBASE64::CBASE64(void)
{
	memset(ReverseBase64Table, 0x00, sizeof(ReverseBase64Table));

	for (int i = 0; i < 64; i++)
	{
		ReverseBase64Table[Base64Table[i]] = i;
	}
}

CBASE64::~CBASE64(void)
{

}

bool CBASE64::Base64Encode(unsigned char* pBufferIn, int BufferInSize, unsigned char* pBufferOut, int &BufferOutSize)
{
	int i = 0;

	if (!pBufferIn || !pBufferOut)
	{
		return false;
	}

	if (BufferInSize == 0 || BufferOutSize == 0)
	{
		return false;
	}

	if (BufferOutSize < (BufferInSize + 2) / 3 * 4)
	{
		BufferOutSize = BufferInSize / 3 * 4 + 4;
		return false;
	}

	memset(pBufferOut, 0x00, BufferOutSize);

	for (i = 0; i < BufferInSize / 3; i++)
	{
		pBufferOut[i * 4] = Base64Table[pBufferIn[i * 3] >> 2];
		pBufferOut[i * 4 + 1] = Base64Table[((pBufferIn[i * 3] << 4) & 0x30) | ((pBufferIn[i * 3 + 1] >> 4) & 0xf)];
		pBufferOut[i * 4 + 2] = Base64Table[((pBufferIn[i * 3 + 1] << 2) & 0x3c) | (pBufferIn[i * 3 + 2] >> 6)];
		pBufferOut[i * 4 + 3] = Base64Table[pBufferIn[i * 3 + 2] & 0x3f];
	}

	if (BufferInSize % 3 == 1)
	{
		pBufferOut[i * 4] = Base64Table[pBufferIn[i * 3] >> 2];
		pBufferOut[i * 4 + 1] = Base64Table[(pBufferIn[i * 3] << 4) & 0x30];
		pBufferOut[i * 4 + 2] = '=';
		pBufferOut[i * 4 + 3] = '=';
	}
	else if (BufferInSize % 3 == 2)
	{
		pBufferOut[i * 4] = Base64Table[pBufferIn[i * 3] >> 2];
		pBufferOut[i * 4 + 1] = Base64Table[((pBufferIn[i * 3] << 4) & 0x30) | ((pBufferIn[i * 3 + 1] >> 4) & 0xf)];
		pBufferOut[i * 4 + 2] = Base64Table[(pBufferIn[i * 3 + 1] << 2) & 0x3c];
		pBufferOut[i * 4 + 3] = '=';
	}

	BufferOutSize = BufferInSize % 3 ? BufferInSize / 3 * 4 + 4 : BufferInSize / 3 * 4;

	return true;
}

bool CBASE64::Base64Decode(unsigned char* pBufferIn, int BufferInSize, unsigned char* pBufferOut, int &BufferOutSize)
{
	int i = 0;
	int j = 0;

	if (!pBufferIn || !pBufferOut)
	{
		return false;
	}

	if (BufferInSize == 0 || BufferOutSize == 0)
	{
		return false;
	}

	if (BufferOutSize < BufferInSize / 4 * 3)
	{
		BufferOutSize = BufferInSize / 4 * 3;
		return false;
	}

	memset(pBufferOut, 0x00, BufferOutSize);

	for (i = 0; i < BufferInSize / 4 - 1; i++)
	{
		pBufferOut[i * 3] = (ReverseBase64Table[pBufferIn[i * 4]] << 2) | (ReverseBase64Table[pBufferIn[i * 4 + 1]] >> 4);
		pBufferOut[i * 3 + 1] = (ReverseBase64Table[pBufferIn[i * 4 + 1]] << 4) | (ReverseBase64Table[pBufferIn[i * 4 + 2]] >> 2);
		pBufferOut[i * 3 + 2] = (ReverseBase64Table[pBufferIn[i * 4 + 2]] << 6) | (ReverseBase64Table[pBufferIn[i * 4 + 3]]);
	}

	j = 0;
	while (pBufferIn[i * 4 + j] != '=' && (i * 4 + j + 1) < BufferInSize)
	{
		j++;
	}

	if (j == 1)
	{
		pBufferOut[i * 3] = (ReverseBase64Table[pBufferIn[i * 4]] << 2) | (ReverseBase64Table[pBufferIn[i * 4 + 1]] >> 4);
		if (pBufferOut[i * 3] == 0x00)
		{
			j -= 1;
		}
	}
	else if (j == 2)
	{
		pBufferOut[i * 3] = (ReverseBase64Table[pBufferIn[i * 4]] << 2) | (ReverseBase64Table[pBufferIn[i * 4 + 1]] >> 4);
		pBufferOut[i * 3 + 1] = (ReverseBase64Table[pBufferIn[i * 4 + 1]] << 4) | (ReverseBase64Table[pBufferIn[i * 4 + 2]] >> 2);
		if (pBufferOut[i * 3 + 1] == 0x00)
		{
			j -= 1;
		}
	}
	else if (j == 3)
	{
		pBufferOut[i * 3] = (ReverseBase64Table[pBufferIn[i * 4]] << 2) | (ReverseBase64Table[pBufferIn[i * 4 + 1]] >> 4);
		pBufferOut[i * 3 + 1] = (ReverseBase64Table[pBufferIn[i * 4 + 1]] << 4) | (ReverseBase64Table[pBufferIn[i * 4 + 2]] >> 2);
		pBufferOut[i * 3 + 2] = (ReverseBase64Table[pBufferIn[i * 4 + 2]] << 6) | (ReverseBase64Table[pBufferIn[i * 4 + 3]]);
		if (pBufferOut[i * 3 + 2] == 0x00)
		{
			j -= 1;
		}
	}

	BufferOutSize = i * 3 + j;

	return true;
}