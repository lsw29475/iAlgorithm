#include "iDes.h"
#include "macro.h"

const unsigned char CDES::DataExchangeTable[64] = {
	58, 50, 42, 34, 26, 18, 10, 2,
	60, 52, 44, 36, 28, 20, 12, 4,
	62, 54, 46, 38, 30, 22, 14, 6,
	64, 56, 48, 40, 32, 24, 16, 8,
	57, 49, 41, 33, 25, 17,  9, 1,
	59, 51, 43, 35, 27, 19, 11, 3,
	61, 53, 45, 37, 29, 21, 13, 5,
	63, 55, 47, 39, 31, 23, 15, 7
};

const unsigned char CDES::KeyExchangeTable[64] = {
	57, 49,  41, 33,  25,  17,  9,
	1,  58,  50, 42,  34,  26, 18,
	10,  2,  59, 51,  43,  35, 27,
	19, 11,   3, 60,  52,  44, 36,
	63, 55,  47, 39,  31,  23, 15,
	7,  62,  54, 46,  38,  30, 22,
	14,  6,  61, 53,  45,  37, 29,
	21, 13,   5, 28,  20,  12,  4
};

const unsigned char CDES::KeyExchangeTable2[64] = {
	14, 17, 11, 24,  1,  5,  
	3, 28, 15,  6, 21, 10,
	23, 19, 12,  4, 26,  8, 
	16,  7, 27, 20, 13,  2,
	41, 52, 31, 37, 47, 55, 
	30, 40, 51, 45, 33, 48,
	44, 49, 39, 56, 34, 53, 
	46, 42, 50, 36, 29, 32
};

const int CDES::KeyExtensionIteration[16] = {
	1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 
	2, 2, 2, 2, 2, 1
 };

const unsigned char CDES::RDataExchangeTable[48] = {
	32,  1,  2,  3,  4,  5,
	4,  5,  6,  7,  8,  9,
	8,  9, 10, 11, 12, 13,
	12, 13, 14, 15, 16, 17,
	16, 17, 18, 19, 20, 21,
	20, 21, 22, 23, 24, 25,
	24, 25, 26, 27, 28, 29,
	28, 29, 30, 31, 32,  1
};

const unsigned char CDES::SBox[8][4][16] =
{
	// S1
	14,  4,	13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7,
	0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8,
	4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0,
	15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13,
	// S2 
	15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10,
	3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5,
	0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15,
	13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9,
	// S3 
	10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8,
	13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1,
	13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7,
	1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12,
	// S4 
	7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15,
	13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9,
	10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4,
	3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14,
	// S5 
	2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9,
	14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6,
	4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14,
	11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3,
	// S6 
	12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11,
	10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8,
	9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6,
	4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13,
	// S7 
	4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1,
	13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6,
	1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2,
	6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12,
	// S8 
	13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7,
	1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2,
	7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8,
	2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11
};

const unsigned char CDES::PBox[32] = {
	16, 7, 20, 21, 29, 12, 28, 17,
	1,  15, 23, 26, 5,  18, 31, 10,
	2,  8, 24, 14, 32, 27, 3,  9,
	19, 13, 30, 6,  22, 11, 4,  25
};

const unsigned char CDES::IPTable[64] = {
	40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31,
	38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29,
	36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27,
	34, 2, 42, 10, 50, 18, 58, 26, 33, 1, 41,  9, 49, 17, 57, 25
};

CDES::CDES(void)
{

}

CDES::~CDES(void)
{

}

bool CDES::DesInit(unsigned char* pKey, int KeySize)
{
	if (KeySize != 8)
	{
		return false;
	}

    memset(key, 0x00,sizeof(key));
	memcpy(key, pKey, KeySize);

	return true;
}

void CDES::DesSetIv(unsigned char* pSetIv)
{
	memcpy(Iv, pSetIv, 8);
}

void CDES::GenerateSubKey()
{
	iBit TempBit,TempBit1;

	for (int i = 0; i < 8; i++)
	{
		TempBit.setData(key[i], 8);
		TempBit1.iCat(TempBit);
	}

	for (int i = 0; i < 28; i++)
	{
		KeyPlusC.iCat(TempBit1.getData(), (int)KeyExchangeTable[i] - 1);
	}

	for (int i = 28; i < 56; i++)
	{
		KeyPlusD.iCat(TempBit1.getData(), (int)KeyExchangeTable[i] - 1);
	}
}

void CDES::ExtensionSubKey()
{
	iBit KeyPlusTempArray[2][17];
	iBit KeyPlusTemp;
	iBit KeyPlusExtTemp[16];

	KeyPlusTempArray[0][0] = KeyPlusC;
	KeyPlusTempArray[1][0] = KeyPlusD;

	for (int i = 1; i < 17; i++)
	{
		KeyPlusTemp = KeyPlusTempArray[0][i - 1];
		KeyPlusTemp.iLeftShift(KeyExtensionIteration[i - 1]);
		KeyPlusTempArray[0][i] = KeyPlusTemp;

		KeyPlusTemp = KeyPlusTempArray[1][i - 1];
		KeyPlusTemp.iLeftShift(KeyExtensionIteration[i - 1]);
		KeyPlusTempArray[1][i] = KeyPlusTemp;
	}

	for (int i = 0; i < 16; i++)
	{
		KeyPlusExtTemp[i].iCat(KeyPlusTempArray[0][i + 1]);
		KeyPlusExtTemp[i].iCat(KeyPlusTempArray[1][i + 1]);
	}

	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 48; j++)
		{
			KeyPlusExt[i].iCat(KeyPlusExtTemp[i].getData(), KeyExchangeTable2[j] - 1);
		}
	}
}

void CDES::ExtensionData(unsigned char* pBufferIn, iBit &DataL0, iBit &DataR0)
{
	iBit TempBit, TempBit1;

	for (int i = 0; i < 8; i++)
	{
		TempBit.setData(pBufferIn[i], 8);
		TempBit1.iCat(TempBit);
	}

	for (int i = 0; i < 32; i++)
	{
		DataL0.iCat(TempBit1.getData(), (int)DataExchangeTable[i] - 1);
	}

	for (int i = 32; i < 64; i++)
	{
		DataR0.iCat(TempBit1.getData(), (int)DataExchangeTable[i] - 1);
	}
}

iBit CDES::DataExchange(iBit DataR, iBit Key)
{
	iBit Temp, SBoxTemp, PBoxTemp, BitOutPut;
	iBit TempSBoxBit[8];
	iBit BitRow, BitColumn;

	for (int i = 0; i < 48; i++)
	{
		Temp.iCat(DataR.getData(), (int)RDataExchangeTable[i] - 1);
	}

	Temp.iXor(Key);
	for (int i = 0; i < 8; i++)
	{
		BitRow.iClear();
		BitColumn.iClear();

		TempSBoxBit[i].iCat(Temp.getData(), i * 6, 6);

		BitRow.iCat(TempSBoxBit[i].getData(), 0);
		BitRow.iCat(TempSBoxBit[i].getData(), 5);
		BitColumn.iCat(TempSBoxBit[i].getData(), 1, 4);

		SBoxTemp.setData(SBox[i][strtol(BitRow.getData().c_str(), NULL, 2)][strtol(BitColumn.getData().c_str(), NULL, 2)], 4);
		PBoxTemp.iCat(SBoxTemp.getData());
	}

	for (int i = 0; i < 32; i++)
	{
		BitOutPut.iCat(PBoxTemp.getData().c_str(), PBox[i] - 1);
	}

	return BitOutPut;
}

void CDES::DataExtensionIteration(iBit &DataL0, iBit &DataR0, bool blEncrypt)
{
	iBit DataLFir, DataRFir, DataLSec, DataRSec;

	DataLFir = DataL0;
	DataRFir = DataR0;

	if (blEncrypt)
	{
		for (int i = 0; i < 16; i++)
		{
			DataLSec = DataRFir;
			DataLFir.iXor(DataExchange(DataRFir, KeyPlusExt[i]));
			DataRSec = DataLFir;

			DataLFir = DataLSec;
			DataRFir = DataRSec;
		}
	}
	else
	{
		for (int i = 15; i >= 0; i--)
		{
			DataLSec = DataRFir;
			DataLFir.iXor(DataExchange(DataRFir, KeyPlusExt[i]));
			DataRSec = DataLFir;

			DataLFir = DataLSec;
			DataRFir = DataRSec;
		}
	}

	DataL0 = DataLFir;
	DataR0 = DataRFir;
}


bool CDES::Encrypt_ECB(unsigned char* pBufferIn, int BufferInSize, unsigned char* pBufferOut, int BufferOutSize)
{
	iBit DataL0, DataR0;
	iBit BitIPChange, BitOutPut;
	iBit BitTemp;

	if (BufferInSize % 8 != 0 || BufferOutSize < BufferInSize)
	{
		return false;
	}

	GenerateSubKey();
	ExtensionSubKey();

	for (int i = 0; i < BufferInSize / 8; i++)
	{
		DataL0.iClear();
		DataR0.iClear();
		BitOutPut.iClear();
		BitTemp.iClear();
		ExtensionData(pBufferIn + i * 8, DataL0, DataR0);
		DataExtensionIteration(DataL0, DataR0, true);

		BitIPChange = DataR0;
		BitIPChange.iCat(DataL0);

		for (int j = 0; j < 64; j++)
		{
			BitOutPut.iCat(BitIPChange.getData().c_str(), IPTable[j] - 1);
		}

		for (int j = 0; j < 8; j++)
		{
			BitTemp.iClear();
			BitTemp.iCat(BitOutPut.getData().c_str(), j * 8, 8);
			pBufferOut[i * 8 + j] = strtol(BitTemp.getData().c_str(), NULL, 2);
		}
	}

	return true;
}

bool CDES::Decrypt_ECB(unsigned char* pBufferIn, int BufferInSize, unsigned char* pBufferOut, int BufferOutSize)
{
	iBit DataL0, DataR0;
	iBit BitIPChange, BitOutPut;
	iBit BitTemp;

	if (BufferInSize % 8 != 0 || BufferOutSize < BufferInSize)
	{
		return false;
	}

	GenerateSubKey();
	ExtensionSubKey();

	for (int i = 0; i < BufferInSize / 8; i++)
	{
		DataL0.iClear();
		DataR0.iClear();
		BitOutPut.iClear();
		BitTemp.iClear();
		ExtensionData(pBufferIn + i * 8, DataR0, DataL0);
		DataExtensionIteration(DataR0, DataL0, false);

		BitIPChange = DataL0;
		BitIPChange.iCat(DataR0);

		for (int j = 0; j < 64; j++)
		{
			BitOutPut.iCat(BitIPChange.getData().c_str(), IPTable[j] - 1);
		}

		for (int j = 0; j < 8; j++)
		{
			BitTemp.iClear();
			BitTemp.iCat(BitOutPut.getData().c_str(), j * 8, 8);
			pBufferOut[i * 8 + j] = strtol(BitTemp.getData().c_str(), NULL, 2);
		}
	}

	return true;
}

bool CDES::Encrypt_CBC(unsigned char* pBufferIn, int BufferInSize, unsigned char* pBufferOut, int BufferOutSize)
{
	iBit DataL0, DataR0;
	iBit BitIPChange, BitOutPut;
	iBit BitTemp;

	if (BufferInSize % 8 != 0 || BufferOutSize < BufferInSize)
	{
		return false;
	}

	GenerateSubKey();
	ExtensionSubKey();

	for (int i = 0; i < BufferInSize / 8; i++)
	{
		DataL0.iClear();
		DataR0.iClear();
		BitOutPut.iClear();
		BitTemp.iClear();

		for (int j = 0; j < 8; j++)
		{
			Iv[j] ^= *(pBufferIn + i * 8 + j);
		}
		ExtensionData(Iv, DataL0, DataR0);
		DataExtensionIteration(DataL0, DataR0, true);

		BitIPChange = DataR0;
		BitIPChange.iCat(DataL0);

		for (int j = 0; j < 64; j++)
		{
			BitOutPut.iCat(BitIPChange.getData().c_str(), IPTable[j] - 1);
		}

		for (int j = 0; j < 8; j++)
		{
			BitTemp.iClear();
			BitTemp.iCat(BitOutPut.getData().c_str(), j * 8, 8);
			pBufferOut[i * 8 + j] = strtol(BitTemp.getData().c_str(), NULL, 2);
		}

		DesSetIv(pBufferOut + i * 8);
	}

	return true;
}

bool CDES::Decrypt_CBC(unsigned char* pBufferIn, int BufferInSize, unsigned char* pBufferOut, int BufferOutSize)
{
	iBit DataL0, DataR0;
	iBit BitIPChange, BitOutPut;
	iBit BitTemp;

	if (BufferInSize % 8 != 0 || BufferOutSize < BufferInSize)
	{
		return false;
	}

	GenerateSubKey();
	ExtensionSubKey();

	for (int i = 0; i < BufferInSize / 8; i++)
	{
		DataL0.iClear();
		DataR0.iClear();
		BitOutPut.iClear();
		BitTemp.iClear();
		ExtensionData(pBufferIn + i * 8, DataR0, DataL0);
		DataExtensionIteration(DataR0, DataL0, false);

		BitIPChange = DataL0;
		BitIPChange.iCat(DataR0);

		for (int j = 0; j < 64; j++)
		{
			BitOutPut.iCat(BitIPChange.getData().c_str(), IPTable[j] - 1);
		}

		for (int j = 0; j < 8; j++)
		{
			BitTemp.iClear();
			BitTemp.iCat(BitOutPut.getData().c_str(), j * 8, 8);
			pBufferOut[i * 8 + j] = strtol(BitTemp.getData().c_str(), NULL, 2);
		}

		for (int j = 0; j < 8; j++)
		{
			*(pBufferOut + i * 8 + j) ^= Iv[j];
		}
		DesSetIv(pBufferIn + i * 8);
	}

	return true;
}

//bool CDES::Encrypt_CFB(unsigned char* pBufferIn, int BufferInSize, unsigned char* pBufferOut, int BufferOutSize)
//{
//	iBit DataL0, DataR0;
//	iBit BitIPChange, BitOutPut;
//	iBit BitTemp;
//
//	if (BufferInSize % 8 != 0 || BufferOutSize < BufferInSize)
//	{
//		return false;
//	}
//
//	GenerateSubKey();
//	ExtensionSubKey();
//
//	for (int i = 0; i < BufferInSize / 8; i++)
//	{
//		DataL0.iClear();
//		DataR0.iClear();
//		BitOutPut.iClear();
//		BitTemp.iClear();
//
//		ExtensionData(Iv, DataL0, DataR0);
//		DataExtensionIteration(DataL0, DataR0, true);
//
//		BitIPChange = DataR0;
//		BitIPChange.iCat(DataL0);
//
//		for (int j = 0; j < 64; j++)
//		{
//			BitOutPut.iCat(BitIPChange.getData().c_str(), IPTable[j] - 1);
//		}
//
//		for (int j = 0; j < 8; j++)
//		{
//			BitTemp.iClear();
//			BitTemp.iCat(BitOutPut.getData().c_str(), j * 8, 8);
//			Iv[j] = strtol(BitTemp.getData().c_str(), NULL, 2);
//		}
//
//		for (int j = 0; j < 8; j++)
//		{
//			Iv[j] ^= *(pBufferIn + i * 8 + j);
//		}
//		memcpy(pBufferOut + i * 8, Iv, 8);
//	}
//
//	return true;
//}
//
//bool CDES::Decrypt_CFB(unsigned char* pBufferIn, int BufferInSize, unsigned char* pBufferOut, int BufferOutSize)
//{
//	iBit DataL0, DataR0;
//	iBit BitIPChange, BitOutPut;
//	iBit BitTemp;
//
//	if (BufferInSize % 8 != 0 || BufferOutSize < BufferInSize)
//	{
//		return false;
//	}
//
//	GenerateSubKey();
//	ExtensionSubKey();
//
//	for (int i = 0; i < BufferInSize / 8; i++)
//	{
//		DataL0.iClear();
//		DataR0.iClear();
//		BitOutPut.iClear();
//		BitTemp.iClear();
//		ExtensionData(Iv, DataR0, DataL0);
//		DataExtensionIteration(DataR0, DataL0, false);
//
//		BitIPChange = DataL0;
//		BitIPChange.iCat(DataR0);
//
//		for (int j = 0; j < 64; j++)
//		{
//			BitOutPut.iCat(BitIPChange.getData().c_str(), IPTable[j] - 1);
//		}
//
//		for (int j = 0; j < 8; j++)
//		{
//			BitTemp.iClear();
//			BitTemp.iCat(BitOutPut.getData().c_str(), j * 8, 8);
//			pBufferOut[i * 8 + j] = strtol(BitTemp.getData().c_str(), NULL, 2);
//		}
//
//		for (int j = 0; j < 8; j++)
//		{
//			Iv[j] ^= *(pBufferIn + i * 8 + j);
//		}
//		memcpy(pBufferOut + i * 8, pBufferIn + i * 8, 8);
//
//		for (int j = 0; j < 8; j++)
//		{
//			Iv[j] ^= *(pBufferOut + i * 8 + j);
//		}
//
//		for (int j = 0; j < 8; j++)
//		{
//			*(pBufferOut + i * 8 + j) ^= Iv[j];
//		}
//
//		for (int j = 0; j < 8; j++)
//		{
//			Iv[j] ^= *(pBufferOut + i * 8 + j);
//		}
//	}
//
//	return true;
//}