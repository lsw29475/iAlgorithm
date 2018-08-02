#pragma once
#include "iBit.h"

class _declspec(dllexport) CDES
{
public:
	CDES(void);
	~CDES(void);

private:
	unsigned char key[8];

private:
	static const unsigned char DataExchangeTable[64];
	static const unsigned char RDataExchangeTable[48];

	static const unsigned char KeyExchangeTable[64];
	static const unsigned char KeyExchangeTable2[64];
	static const int KeyExtensionIteration[16];

	static const unsigned char SBox[8][4][16];
	static const unsigned char PBox[32];
	static const unsigned char IPTable[64];

public:
	bool DesInit(unsigned char* pKey, int KeySize);
	void DesSetIv(unsigned char* pSetIv);

	bool Encrypt_ECB(unsigned char* pBufferIn, int BufferInSize, unsigned char* pBufferOut, int BufferOutSize);
	bool Decrypt_ECB(unsigned char* pBufferIn, int BufferInSize, unsigned char* pBufferOut, int BufferOutSize);

	bool Encrypt_CBC(unsigned char* pBufferIn, int BufferInSize, unsigned char* pBufferOut, int BufferOutSize);
	bool Decrypt_CBC(unsigned char* pBufferIn, int BufferInSize, unsigned char* pBufferOut, int BufferOutSize);

	//bool Encrypt_CFB(unsigned char* pBufferIn, int BufferInSize, unsigned char* pBufferOut, int BufferOutSize);
	//bool Decrypt_CFB(unsigned char* pBufferIn, int BufferInSize, unsigned char* pBufferOut, int BufferOutSize);

private:
	void GenerateSubKey();
	void ExtensionSubKey();

	void ExtensionData(unsigned char* pBufferIn, iBit &DataL0, iBit &DataR0);
	void DataExtensionIteration(iBit &DataL0, iBit &DataR0, bool blEncrypt);

	iBit DataExchange(iBit DataR, iBit Key);

private:
	iBit KeyPlusC, KeyPlusD;
	iBit KeyPlusExt[16];
	unsigned char Iv[8];
};