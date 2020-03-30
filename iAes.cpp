#include "iAes.h"
#include "macro.h"

const unsigned char CAES::SBox[256] = {
	0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5,
	0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
	0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0,
	0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
	0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc,
	0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
	0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a,
	0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
	0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0,
	0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
	0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b,
	0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
	0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85,
	0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
	0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5,
	0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
	0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17,
	0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
	0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88,
	0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
	0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c,
	0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
	0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9,
	0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
	0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6,
	0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
	0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e,
	0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
	0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94,
	0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
	0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68,
	0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16};

const unsigned char CAES::InvSBox[256] = {
	0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38,
	0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
	0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87,
	0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
	0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d,
	0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
	0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2,
	0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
	0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16,
	0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
	0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda,
	0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
	0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a,
	0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
	0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02,
	0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
	0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea,
	0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
	0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85,
	0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
	0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89,
	0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
	0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20,
	0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
	0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31,
	0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
	0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d,
	0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
	0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0,
	0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
	0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26,
	0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d};

const unsigned long CAES::Rcon[11] = {
	0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36};

const unsigned long long CAES::LastBox[16] = {
	0x0000, 0x1c20, 0x3840, 0x2460,
	0x7080, 0x6ca0, 0x48c0, 0x54e0,
	0xe100, 0xfd20, 0xd940, 0xc560,
	0x9180, 0x8da0, 0xa9c0, 0xb5e0};

const int CAES::Nb = 4;

CAES::CAES(void)
{
}

CAES::~CAES(void)
{
}

bool CAES::SetAESKey(unsigned char *pKey, int KeySize)
{
	if (KeySize != 16 && KeySize != 24 && KeySize != 32)
	{
		return false;
	}

	memset(key, 0x00, sizeof(key));
	memcpy(key, pKey, KeySize);

	return true;
}

bool CAES::AesInit(unsigned char *pKey, int KeySize, unsigned char *pGCMNonce, int NonceSizeIn, int EncryptMode)
{
	if (!SetAESKey(pKey, KeySize))
	{
		return false;
	}

	switch (KeySize)
	{
	case AES_128_TYPE:
		Nk = 4;
		Nr = 10;
		AesType = AES_128_TYPE;
		break;

	case AES_192_TYPE:
		Nk = 6;
		Nr = 12;
		AesType = AES_192_TYPE;
		break;

	case AES_256_TYPE:
		Nk = 8;
		Nr = 14;
		AesType = AES_256_TYPE;
		break;

	default:
		return false;
	}

	switch (EncryptMode)
	{
	case AES_ECB:
		EncryptType = AES_ECB;
		break;

	case AES_CBC:
		EncryptType = AES_CBC;
		break;

	case AES_CFB:
		EncryptType = AES_CFB;
		break;

	case AES_GCM:
		EncryptType = AES_GCM;
		break;

	case AES_XTS:
		EncryptType = AES_XTS;
		break;

	default:
		return false;
	}

	if (EncryptType == AES_GCM)
	{
		NonceSize = NonceSizeIn;
		memset(BaseEncryptData, 0x00, sizeof(BaseEncryptData));
		memset(WorkingData, 0x00, sizeof(WorkingData));
		memset(GCMNonce, 0x00, sizeof(GCMNonce));
		memcpy(GCMNonce, pGCMNonce, NonceSize);
	}

	return true;
}

void CAES::AesSetIv(unsigned char *pSetIv)
{
	memcpy(Iv, pSetIv, 16);
}

unsigned char CAES::xtime(unsigned char cByte)
{
	return cByte >= 0x80 ? (cByte << 1) ^ 0x1b : cByte << 1;
}

void CAES::SubWord(unsigned char *dwTemp)
{
	dwTemp[0] = SBox[dwTemp[0]];
	dwTemp[1] = SBox[dwTemp[1]];
	dwTemp[2] = SBox[dwTemp[2]];
	dwTemp[3] = SBox[dwTemp[3]];
}

void CAES::RotWord(unsigned char *dwTemp)
{
	unsigned char cTmp = dwTemp[0];
	dwTemp[0] = dwTemp[1];
	dwTemp[1] = dwTemp[2];
	dwTemp[2] = dwTemp[3];
	dwTemp[3] = cTmp;
}

void CAES::SubByte(unsigned char *pState)
{
	for (int i = 0; i < Nb * 4; i++)
	{
		pState[i] = SBox[pState[i]];
	}
}

void CAES::InvSubBytes(unsigned char *pState)
{
	for (int i = 0; i < Nb * 4; i++)
	{
		pState[i] = InvSBox[pState[i]];
	}
}

void CAES::MixColumns(unsigned char *State)
{
	unsigned char temp[4][4] = {0x00};
	unsigned char out[4][4] = {0x00};

	memcpy(temp, State, 16);

	for (unsigned long j = 0; j < 4; j++)
	{
		out[j][0] = xtime(temp[j][0]) ^ xtime(temp[j][1]) ^ temp[j][1] ^ temp[j][2] ^ temp[j][3];
		out[j][1] = temp[j][0] ^ xtime(temp[j][1]) ^ xtime(temp[j][2]) ^ temp[j][2] ^ temp[j][3];
		out[j][2] = temp[j][0] ^ temp[j][1] ^ xtime(temp[j][2]) ^ xtime(temp[j][3]) ^ temp[j][3];
		out[j][3] = xtime(temp[j][0]) ^ temp[j][0] ^ temp[j][1] ^ temp[j][2] ^ xtime(temp[j][3]);
	}

	memcpy(State, out, 16);
}

void CAES::InvMixColumns(unsigned char *State)
{
	unsigned char temp[4][4] = {0x00};
	unsigned char out[4][4] = {0x00};
	unsigned char tmp;

	memcpy(temp, State, 16);

	for (unsigned long j = 0; j < 4; j++)
	{
		tmp = xtime(xtime(xtime(temp[j][0] ^ temp[j][1] ^ temp[j][2] ^ temp[j][3])));
		out[j][0] = xtime(xtime(temp[j][0] ^ temp[j][2])) ^ temp[j][1] ^ temp[j][2] ^ temp[j][3] ^ xtime(temp[j][0] ^ temp[j][1]) ^ tmp;
		out[j][1] = xtime(xtime(temp[j][1] ^ temp[j][3])) ^ temp[j][0] ^ temp[j][2] ^ temp[j][3] ^ xtime(temp[j][1] ^ temp[j][2]) ^ tmp;
		out[j][2] = xtime(xtime(temp[j][2] ^ temp[j][0])) ^ temp[j][0] ^ temp[j][1] ^ temp[j][3] ^ xtime(temp[j][2] ^ temp[j][3]) ^ tmp;
		out[j][3] = xtime(xtime(temp[j][3] ^ temp[j][1])) ^ temp[j][0] ^ temp[j][1] ^ temp[j][2] ^ xtime(temp[j][3] ^ temp[j][0]) ^ tmp;
	}

	memcpy(State, out, 16);
}

void CAES::ShiftRows(unsigned char *pState)
{
	unsigned char Temp;

	for (unsigned long i = 0; i <= 3; i++)
	{
		if (i == 1)
		{
			Temp = *(unsigned char *)(pState + i);
			*(unsigned char *)(pState + i) = *(unsigned char *)(pState + i + 4);
			*(unsigned char *)(pState + i + 4) = *(unsigned char *)(pState + i + 4 * 2);
			*(unsigned char *)(pState + i + 4 * 2) = *(unsigned char *)(pState + i + 4 * 3);
			*(unsigned char *)(pState + i + 4 * 3) = Temp;
		}

		if (i == 2)
		{
			Temp = *(unsigned char *)(pState + i);
			*(unsigned char *)(pState + i) = *(unsigned char *)(pState + i + 4 * 2);
			*(unsigned char *)(pState + i + 4 * 2) = Temp;
			Temp = *(unsigned char *)(pState + i + 4);
			*(unsigned char *)(pState + i + 4) = *(unsigned char *)(pState + i + 4 * 3);
			*(unsigned char *)(pState + i + 4 * 3) = Temp;
		}

		if (i == 3)
		{
			Temp = *(unsigned char *)(pState + i);
			*(unsigned char *)(pState + i) = *(unsigned char *)(pState + i + 4 * 3);
			*(unsigned char *)(pState + i + 4 * 3) = *(unsigned char *)(pState + i + 4 * 2);
			*(unsigned char *)(pState + i + 4 * 2) = *(unsigned char *)(pState + i + 4);
			*(unsigned char *)(pState + i + 4) = Temp;
		}
	}
}

void CAES::InvShiftRows(unsigned char *pState)
{
	unsigned char Temp;

	for (unsigned long i = 0; i <= 3; i++)
	{
		if (i == 1)
		{
			Temp = *(unsigned char *)(pState + i + 4 * 3);
			*(unsigned char *)(pState + i + 4 * 3) = *(unsigned char *)(pState + i + 4 * 2);
			*(unsigned char *)(pState + i + 4 * 2) = *(unsigned char *)(pState + i + 4);
			*(unsigned char *)(pState + i + 4) = *(unsigned char *)(pState + i);
			*(unsigned char *)(pState + i) = Temp;
		}

		if (i == 2)
		{
			Temp = *(unsigned char *)(pState + i + 4 * 3);
			*(unsigned char *)(pState + i + 4 * 3) = *(unsigned char *)(pState + i + 4);
			*(unsigned char *)(pState + i + 4) = Temp;
			Temp = *(unsigned char *)(pState + i + 4 * 2);
			*(unsigned char *)(pState + i + 4 * 2) = *(unsigned char *)(pState + i);
			*(unsigned char *)(pState + i) = Temp;
		}

		if (i == 3)
		{
			Temp = *(unsigned char *)(pState + i + 4 * 3);
			*(unsigned char *)(pState + i + 4 * 3) = *(unsigned char *)(pState + i);
			*(unsigned char *)(pState + i) = *(unsigned char *)(pState + i + 4);
			*(unsigned char *)(pState + i + 4) = *(unsigned char *)(pState + i + 4 * 2);
			*(unsigned char *)(pState + i + 4 * 2) = Temp;
		}
	}
}

void CAES::AddRoundKey(unsigned char *pState, unsigned char *pRoundKey)
{
	for (unsigned long i = 0; i < 16; i++)
	{
		pState[i] ^= pRoundKey[i];
	}
}

void CAES::AESKeyExpansion()
{
	int i = 0;
	unsigned int dwTemp;

	memset(RoundKey, 0x00, sizeof(RoundKey));
	memcpy(RoundKey, key, 32);

	i = Nk;

	while (i < 4 * (Nr + 1))
	{
		dwTemp = RoundKey[i - 1];
		if (i % Nk == 0)
		{
			RotWord((unsigned char *)&dwTemp);
			SubWord((unsigned char *)&dwTemp);
			dwTemp ^= Rcon[i / Nk];
		}
		else if ((Nk > 6) && (i % Nk == 4))
		{
			SubWord((unsigned char *)&dwTemp);
		}

		RoundKey[i] = RoundKey[i - Nk] ^ dwTemp;
		i++;
	}
}

void CAES::AesRoundEncrypt(unsigned char *pBlockIn, unsigned char *pBlockOut)
{
	unsigned char state[4][4] = {0x00};

	memcpy(state, pBlockIn, 16);

	AESKeyExpansion();

	AddRoundKey((unsigned char *)state, (unsigned char *)RoundKey);

	for (int ulRound = 1; ulRound <= Nr - 1; ulRound++)
	{
		SubByte((unsigned char *)state);
		ShiftRows((unsigned char *)state);
		MixColumns((unsigned char *)state);
		AddRoundKey((unsigned char *)state, (unsigned char *)RoundKey + ulRound * 16);
	}

	SubByte((unsigned char *)state);
	ShiftRows((unsigned char *)state);
	AddRoundKey((unsigned char *)state, (unsigned char *)RoundKey + Nr * 16);

	memcpy(pBlockOut, state, 16);
}

void CAES::AesRoundDecrypt(unsigned char *pBlockIn, unsigned char *pBlockOut)
{
	unsigned char state[4][4] = {0x00};

	memcpy(state, pBlockIn, 16);

	AESKeyExpansion();

	AddRoundKey((unsigned char *)state, (unsigned char *)RoundKey + Nr * 16);

	for (int ulRound = 1; ulRound <= Nr - 1; ulRound++)
	{
		InvShiftRows((unsigned char *)state);
		InvSubBytes((unsigned char *)state);
		AddRoundKey((unsigned char *)state, (unsigned char *)RoundKey + Nr * 16 - ulRound * 16);
		InvMixColumns((unsigned char *)state);
	}

	InvShiftRows((unsigned char *)state);
	InvSubBytes((unsigned char *)state);
	AddRoundKey((unsigned char *)state, (unsigned char *)RoundKey);

	memcpy(pBlockOut, state, 16);
}

bool CAES::Encrypt_ECB(unsigned char *pBufferIn, int BufferInSize, unsigned char *pBufferOut, int BufferOutSize)
{
	if (BufferInSize % 16 != 0)
	{
		return false;
	}

	if (BufferOutSize < BufferInSize)
	{
		return false;
	}

	if (EncryptType != AES_ECB)
	{
		return false;
	}

	for (int i = 0; i < BufferInSize / 16; i++)
	{
		AesRoundEncrypt(pBufferIn + i * 16, pBufferOut + i * 16);
	}

	return true;
}

bool CAES::Decrypt_ECB(unsigned char *pBufferIn, int BufferInSize, unsigned char *pBufferOut, int BufferOutSize)
{
	if (BufferInSize % 16 != 0)
	{
		return false;
	}

	if (BufferOutSize < BufferInSize)
	{
		return false;
	}

	if (EncryptType != AES_ECB)
	{
		return false;
	}

	for (int i = 0; i < BufferInSize / 16; i++)
	{
		AesRoundDecrypt(pBufferIn + i * 16, pBufferOut + i * 16);
	}

	return true;
}

bool CAES::Encrypt_CBC(unsigned char *pBufferIn, int BufferInSize, unsigned char *pBufferOut, int BufferOutSize)
{
	if (BufferInSize % 16 != 0)
	{
		return false;
	}

	if (BufferOutSize < BufferInSize)
	{
		return false;
	}

	if (EncryptType != AES_CBC)
	{
		return false;
	}

	for (int i = 0; i < BufferInSize / 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			Iv[j] ^= *(pBufferIn + i * 16 + j);
		}
		AesRoundEncrypt(Iv, pBufferOut + i * 16);
		AesSetIv(pBufferOut + i * 16);
	}

	return true;
}

bool CAES::Decrypt_CBC(unsigned char *pBufferIn, int BufferInSize, unsigned char *pBufferOut, int BufferOutSize)
{
	if (BufferInSize % 16 != 0)
	{
		return false;
	}

	if (BufferOutSize < BufferInSize)
	{
		return false;
	}

	if (EncryptType != AES_CBC)
	{
		return false;
	}

	for (int i = 0; i < BufferInSize / 16; i++)
	{
		AesRoundDecrypt(pBufferIn + i * 16, pBufferOut + i * 16);
		for (int j = 0; j < 16; j++)
		{
			*(pBufferOut + i * 16 + j) ^= Iv[j];
		}
		AesSetIv(pBufferIn + i * 16);
	}

	return true;
}

//bool CAES::Encrypt_CFB(unsigned char* pBufferIn, int BufferInSize, unsigned char* pBufferOut, int BufferOutSize)
//{
//	if (BufferInSize % 16 != 0)
//	{
//		return false;
//	}
//
//	if (BufferOutSize < BufferInSize)
//	{
//		return false;
//	}
//
//	if (EncryptType != AES_CFB)
//	{
//		return false;
//	}
//
//	for (int i = 0; i < BufferInSize / 16; i++)
//	{
//		AesRoundEncrypt(Iv, Iv);
//		for (int j = 0; j < 16; j++)
//		{
//			Iv[j] ^= *(pBufferIn + i * 16 + j);
//		}
//		memcpy(pBufferOut + i * 16, Iv, 16);
//	}
//
//	return true;
//}
//
//bool CAES::Decrypt_CFB(unsigned char* pBufferIn, int BufferInSize, unsigned char* pBufferOut, int BufferOutSize)
//{
//	if (BufferInSize % 16 != 0)
//	{
//		return false;
//	}
//
//	if (BufferOutSize < BufferInSize)
//	{
//		return false;
//	}
//
//	if (EncryptType != AES_CFB)
//	{
//		return false;
//	}
//
//	for (int i = 0; i < BufferInSize / 16; i++)
//	{
//		AesRoundEncrypt(Iv, Iv);
//		for (int j = 0; j < 16; j++)
//		{
//			Iv[j] ^= *(pBufferIn + i * 16 + j);
//		}
//		memcpy(pBufferOut + i * 16, pBufferIn + i * 16, 16);
//
//		for (int j = 0; j < 16; j++)
//		{
//			Iv[j] ^= *(pBufferOut + i * 16 + j);
//		}
//
//		for (int j = 0; j < 16; j++)
//		{
//			*(pBufferOut + i * 16 + j) ^= Iv[j];
//		}
//
//		for (int j = 0; j < 16; j++)
//		{
//			Iv[j] ^= *(pBufferOut + i * 16 + j);
//		}
//	}
//
//	return true;
//}

void CAES::AESGCMGenerateTable()
{
	unsigned char h[16];
	unsigned long long high, low;
	unsigned long temp;

	memset(h, 0x00, sizeof(h));
	memset(HTableHigh, 0x00, sizeof(HTableHigh));
	memset(HTableLow, 0x00, sizeof(HTableLow));

	AesRoundEncrypt(h, h);

	GET_UINT32_BE(high, h, 0);
	GET_UINT32_BE(low, h, 4);
	HTableHigh[8] = (uint64_t)high << 32 | low;

	GET_UINT32_BE(high, h, 8);
	GET_UINT32_BE(low, h, 12);
	HTableLow[8] = (uint64_t)high << 32 | low;

	HTableHigh[0] = 0;
	HTableLow[0] = 0;
	high = HTableHigh[8];
	low = HTableLow[8];

	for (int i = 4; i > 0; i >>= 1)
	{
		temp = (low & 1) * 0xe1000000U;
		low = (high << 63) | (low >> 1);
		high = (high >> 1) ^ ((uint64_t)temp << 32);

		HTableLow[i] = low;
		HTableHigh[i] = high;
	}

	for (int i = 2; i <= 8; i *= 2)
	{
		low = HTableLow[i];
		high = HTableHigh[i];
		for (int j = 1; j < i; j++)
		{
			HTableHigh[i + j] = high ^ HTableHigh[j];
			HTableLow[i + j] = low ^ HTableLow[j];
		}
	}
}

void CAES::AESGCMMult(unsigned char *pIn, unsigned char *pOut)
{
	unsigned char low, high, rem;
	uint64_t zh, zl;

	low = pIn[15] & 0xf;

	zh = HTableHigh[low];
	zl = HTableLow[low];

	for (int i = 15; i >= 0; i--)
	{
		low = pIn[i] & 0xf;
		high = pIn[i] >> 4;

		if (i != 15)
		{
			rem = (unsigned char)zl & 0xf;
			zl = (zh << 60) | (zl >> 4);
			zh = (zh >> 4);
			zh ^= (uint64_t)LastBox[rem] << 48;
			zh ^= HTableHigh[low];
			zl ^= HTableLow[low];
		}

		rem = (unsigned char)zl & 0xf;
		zl = (zh << 60) | (zl >> 4);
		zh = (zh >> 4);
		zh ^= (uint64_t)LastBox[rem] << 48;
		zh ^= HTableHigh[high];
		zl ^= HTableLow[high];
	}

	PUT_UINT32_BE(zh >> 32, pOut, 0);
	PUT_UINT32_BE(zh, pOut, 4);
	PUT_UINT32_BE(zl >> 32, pOut, 8);
	PUT_UINT32_BE(zl, pOut, 12);
}

bool CAES::AESGCMHandleNonce(unsigned char *pAdditionData, int AdditionDataSize)
{
	unsigned char tempBuf[16];
	unsigned char *pTemp = NULL;
	int TempLength;

	if (NonceSize > 16 || AdditionDataSize > 16)
	{
		return false;
	}

	if (NonceSize == 12)
	{
		GCMNonce[15] = 1;
	}
	else
	{
		memset(tempBuf, 0x00, sizeof(tempBuf));
		PUT_UINT32_BE(NonceSize * 8, tempBuf, 12);

		pTemp = new unsigned char[NonceSize];
		memcpy(pTemp, GCMNonce, NonceSize);
		while (NonceSize > 0)
		{
			TempLength = (NonceSize < 16) ? NonceSize : 16;

			for (int i = 0; i < TempLength; i++)
			{
				GCMNonce[i] ^= pTemp[i];
			}

			AESGCMMult(GCMNonce, GCMNonce);

			NonceSize -= TempLength;
			pTemp += TempLength;
		}

		for (int i = 0; i < 16; i++)
		{
			GCMNonce[i] ^= tempBuf[i];
		}

		AESGCMMult(GCMNonce, GCMNonce);
	}

	delete[] pTemp;
	pTemp = NULL;
	AesRoundEncrypt(GCMNonce, BaseEncryptData);

	pTemp = pAdditionData;
	while (AdditionDataSize > 0)
	{
		TempLength = (AdditionDataSize < 16) ? AdditionDataSize : 16;

		for (int i = 0; i < TempLength; i++)
		{
			WorkingData[i] ^= pTemp[i];
		}

		AESGCMMult(WorkingData, WorkingData);
		AdditionDataSize -= TempLength;
		pTemp += TempLength;
	}

	return true;
}

bool CAES::Encrypt_GCM(unsigned char *pBufferIn, int BufferInSize, unsigned char *pBufferOut, int BufferOutSize, unsigned char *pAdditionData, int AdditionDataSize, unsigned char *pTag, int TagSize)
{
	int TempLength;
	unsigned char TempBuf[16];
	unsigned long long OrigSize;
	unsigned long long OrgiAdditionSize;

	if (BufferOutSize != BufferInSize)
	{
		return false;
	}

	if (EncryptType != AES_GCM)
	{
		return false;
	}

	if (TagSize > 16 || TagSize < 4)
	{
		return false;
	}

	AESKeyExpansion();
	AESGCMGenerateTable();
	if (!AESGCMHandleNonce(pAdditionData, AdditionDataSize))
	{
		return false;
	}

	while (BufferInSize > 0)
	{
		TempLength = (BufferInSize < 16) ? BufferInSize : 16;

		for (int i = 16; i > 12; i--)
		{
			if (++GCMNonce[i - 1] != 0)
			{
				break;
			}
		}

		AesRoundEncrypt(GCMNonce, TempBuf);

		for (int i = 0; i < TempLength; i++)
		{
			pBufferOut[i] = TempBuf[i] ^ pBufferIn[i];
			WorkingData[i] ^= pBufferOut[i];
		}

		AESGCMMult(WorkingData, WorkingData);
		BufferInSize -= TempLength;
		pBufferIn += TempLength;
		pBufferOut += TempLength;
	}

	if (TagSize != 0)
	{
		memcpy(pTag, BaseEncryptData, TagSize);
	}

	OrigSize = BufferOutSize * 8;
	OrgiAdditionSize = AdditionDataSize * 8;

	if (OrigSize || OrgiAdditionSize)
	{
		memset(TempBuf, 0x00, 16);

		PUT_UINT32_BE((OrgiAdditionSize >> 32), TempBuf, 0);
		PUT_UINT32_BE((OrgiAdditionSize), TempBuf, 4);
		PUT_UINT32_BE((OrigSize >> 32), TempBuf, 8);
		PUT_UINT32_BE((OrigSize), TempBuf, 12);

		for (int i = 0; i < 16; i++)
		{
			WorkingData[i] ^= TempBuf[i];
		}

		AESGCMMult(WorkingData, WorkingData);

		for (int i = 0; i < TagSize; i++)
		{
			pTag[i] ^= WorkingData[i];
		}
	}

	return true;
}

bool CAES::Decrypt_GCM(unsigned char *pBufferIn, int BufferInSize, unsigned char *pBufferOut, int BufferOutSize, unsigned char *pAdditionData, int AdditionDataSize, unsigned char *pTag, int TagSize)
{
	int TempLength;
	unsigned char TempBuf[16];
	unsigned long long OrigSize;
	unsigned long long OrgiAdditionSize;

	if (BufferOutSize != BufferInSize)
	{
		return false;
	}

	if (EncryptType != AES_GCM)
	{
		return false;
	}

	if (TagSize > 16 || TagSize < 4)
	{
		return false;
	}

	AESKeyExpansion();
	AESGCMGenerateTable();
	if (!AESGCMHandleNonce(pAdditionData, AdditionDataSize))
	{
		return false;
	}

	while (BufferInSize > 0)
	{
		TempLength = (BufferInSize < 16) ? BufferInSize : 16;

		for (int i = 16; i > 12; i--)
		{
			if (++GCMNonce[i - 1] != 0)
			{
				break;
			}
		}

		AesRoundEncrypt(GCMNonce, TempBuf);

		for (int i = 0; i < TempLength; i++)
		{
			WorkingData[i] ^= pBufferIn[i];
			pBufferOut[i] = TempBuf[i] ^ pBufferIn[i];
		}

		AESGCMMult(WorkingData, WorkingData);
		BufferInSize -= TempLength;
		pBufferIn += TempLength;
		pBufferOut += TempLength;
	}

	if (TagSize != 0)
	{
		memcpy(pTag, BaseEncryptData, TagSize);
	}

	OrigSize = BufferOutSize * 8;
	OrgiAdditionSize = AdditionDataSize * 8;

	if (OrigSize || OrgiAdditionSize)
	{
		memset(TempBuf, 0x00, 16);

		PUT_UINT32_BE((OrgiAdditionSize >> 32), TempBuf, 0);
		PUT_UINT32_BE((OrgiAdditionSize), TempBuf, 4);
		PUT_UINT32_BE((OrigSize >> 32), TempBuf, 8);
		PUT_UINT32_BE((OrigSize), TempBuf, 12);

		for (int i = 0; i < 16; i++)
		{
			WorkingData[i] ^= TempBuf[i];
		}

		AESGCMMult(WorkingData, WorkingData);

		for (int i = 0; i < TagSize; i++)
		{
			pTag[i] ^= WorkingData[i];
		}
	}

	return true;
}

bool CAES::Encrypt_XTS(unsigned char *pBufferIn, int BufferInSize, unsigned char *pBufferOut, int BufferOutSize)
{
	return true;
}

bool CAES::Decrypt_XTS(unsigned char *pBufferIn, int BufferInSize, unsigned char *pBufferOut, int BufferOutSize)
{
	return true;
}