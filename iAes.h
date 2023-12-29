#pragma once

class _declspec(dllexport) CAES
{
public:
	CAES(void);
	~CAES(void);

public:
	enum AES_TYPE
	{
		AES_128_TYPE = 16,
		AES_192_TYPE = 24,
		AES_256_TYPE = 32,
	};

	enum AES_ENCRYPT_TYPE
	{
		AES_ECB = 1,
		AES_CBC = 2,
		AES_CFB = 3,
		AES_GCM = 4,
		AES_XTS = 5,
	};

	enum AES_CFB_TYPE
	{
		CFB_8 = 8,
		CFB_128 = 128,
	};

private:
	int Nk;
	int Nr;
	static const int Nb;
	unsigned long key[8];
	unsigned char Iv[16];
	unsigned long RoundKey[60];

	int NonceSize;
	unsigned char GCMNonce[16];
	unsigned long long HTableHigh[16];
	unsigned long long HTableLow[16];
	unsigned char BaseEncryptData[16];
	unsigned char WorkingData[16];

	int AesType;
	int EncryptType;

private:
	static const unsigned long Rcon[11];
	static const unsigned char SBox[256];
	static const unsigned char InvSBox[256];
	static const unsigned long long LastBox[16];

public:
	void AesSetIv(unsigned char *pSetIv);

	bool AesInit(unsigned char *pKey, int KeySize, unsigned char *pGCMNonce, int NonceSizeIn, int EncryptMode);

	bool Encrypt_ECB(unsigned char *pBufferIn, int BufferInSize, unsigned char *pBufferOut, int BufferOutSize);
	bool Decrypt_ECB(unsigned char *pBufferIn, int BufferInSize, unsigned char *pBufferOut, int BufferOutSize);

	bool Encrypt_CBC(unsigned char *pBufferIn, int BufferInSize, unsigned char *pBufferOut, int BufferOutSize);
	bool Decrypt_CBC(unsigned char *pBufferIn, int BufferInSize, unsigned char *pBufferOut, int BufferOutSize);

	bool Encrypt_CFB(unsigned char* pBufferIn, int BufferInSize, unsigned char* pBufferOut, int BufferOutSize, int CfbType);
	bool Decrypt_CFB(unsigned char* pBufferIn, int BufferInSize, unsigned char* pBufferOut, int BufferOutSize, int CfbType);

	bool Encrypt_GCM(unsigned char *pBufferIn, int BufferInSize, unsigned char *pBufferOut, int BufferOutSize, unsigned char *pAdditionData, int AdditionDataSize, unsigned char* pTag, int TagSize);
	bool Decrypt_GCM(unsigned char *pBufferIn, int BufferInSize, unsigned char *pBufferOut, int BufferOutSize, unsigned char *pAdditionData, int AdditionDataSize, unsigned char* pTag, int TagSize);

	bool Encrypt_XTS(unsigned char *pBufferIn, int BufferInSize, unsigned char *pBufferOut, int BufferOutSize);
	bool Decrypt_XTS(unsigned char *pBufferIn, int BufferInSize, unsigned char *pBufferOut, int BufferOutSize);

private:
	bool SetAESKey(unsigned char *pKey, int KeySize);
	void AesRoundEncrypt(unsigned char *pBlockIn, unsigned char *pBlockOut);
	void AesRoundDecrypt(unsigned char *pBlockIn, unsigned char *pBlockOut);

private:
	//对密钥进行拓展，拓展为轮密钥
	void AESKeyExpansion();
	//将状态元素与轮密钥进行简单亦或运算
	void AddRoundKey(unsigned char *pState, unsigned char *pRoundKey);
	//Subunsigned chars  以状态数组中每个字节元素的高4位作行标，低4位作列标，取对应SBox元素
	void SubByte(unsigned char *pState);
	//对状态数组进行位移
	void ShiftRows(unsigned char *pState);
	//对状态数组进行矩阵相乘运算
	void MixColumns(unsigned char *State);

	void InvSubBytes(unsigned char *pState);
	void InvShiftRows(unsigned char *pState);
	void InvMixColumns(unsigned char *pState);

	void AESGCMGenerateTable();
	bool AESGCMHandleNonce(unsigned char *pAdditionData, int AdditionDataSize);
	void AESGCMMult(unsigned char *pIn, unsigned char *pOut);

	void Encrypt_CFB_8(unsigned char *pBufferIn, int BufferInSize, unsigned char *pBufferOut, int BufferOutSize);
    void Encrypt_CFB_128(unsigned char *pBufferIn, int BufferInSize, unsigned char *pBufferOut, int BufferOutSize);
    void Decrypt_CFB_8(unsigned char *pBufferIn, int BufferInSize, unsigned char *pBufferOut, int BufferOutSize);
    void Decrypt_CFB_128(unsigned char *pBufferIn, int BufferInSize, unsigned char *pBufferOut, int BufferOutSize);

private:
	unsigned char xtime(unsigned char cByte);
	void SubWord(unsigned char *dwTemp);
	void RotWord(unsigned char *dwTemp);
};