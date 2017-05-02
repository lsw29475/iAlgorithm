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

	enum AES_ENCRYPT_MODE
	{
		AES_ECB = 1,
		AES_CBC = 2,
		AES_CFB = 3,
	};

private:
	int Nk;
	int Nr;
	static const int Nb;
	unsigned long key[8];
	unsigned char Iv[16];
	unsigned long RoundKey[60];
	int AesType;
	int EncryptType;

private:
	static const unsigned long Rcon[11];
	static const unsigned char SBox[256];
	static const unsigned char InvSBox[256];

public:
	void AesSetIv(unsigned char* pSetIv);

	bool AesInit(unsigned char* pKey, int KeySize, int EncryptMode);

	bool Encrypt_ECB(unsigned char* pBufferIn, int BufferInSize, unsigned char* pBufferOut, int BufferOutSize);
	bool Decrypt_ECB(unsigned char* pBufferIn, int BufferInSize, unsigned char* pBufferOut, int BufferOutSize);

	bool Encrypt_CBC(unsigned char* pBufferIn, int BufferInSize, unsigned char* pBufferOut, int BufferOutSize);
	bool Decrypt_CBC(unsigned char* pBufferIn, int BufferInSize, unsigned char* pBufferOut, int BufferOutSize);

	bool Encrypt_CFB(unsigned char* pBufferIn, int BufferInSize, unsigned char* pBufferOut, int BufferOutSize);
	bool Decrypt_CFB(unsigned char* pBufferIn, int BufferInSize, unsigned char* pBufferOut, int BufferOutSize);

private:
	bool SetAESKey(unsigned char* pKey, int KeySize);
	void AesRoundEncrypt(unsigned char* pBlockIn, unsigned char* pBlockOut);
	void AesRoundDecrypt(unsigned char* pBlockIn, unsigned char* pBlockOut);

private:
	//对密钥进行拓展，拓展为轮密钥
	void AESKeyExpansion();
	//将状态元素与轮密钥进行简单亦或运算
	void AddRoundKey(unsigned char* pState, unsigned char* pRoundKey);
	//SubBytes  以状态数组中每个字节元素的高4位作行标，低4位作列标，取对应SBox元素
	void SubBytes(unsigned char* pState);
	//对状态数组进行位移
	void ShiftRows(unsigned char* pState);
	//对状态数组进行矩阵相乘运算
	void MixColumns(unsigned char* State);

	void InvSubBytes(unsigned char* pState);
	void InvShiftRows(unsigned char* pState);
	void InvMixColumns(unsigned char* pState);

private:
	unsigned char xtime(unsigned char cByte);
	void SubWord(unsigned char* dwTemp);
	void RotWord(unsigned char* dwTemp);
};