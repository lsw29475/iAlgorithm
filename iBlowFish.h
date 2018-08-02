#pragma once

class _declspec(dllexport) CBLOWFISH
{
public:
	CBLOWFISH(void);
	~CBLOWFISH(void);

private:
	unsigned char* pBlowFishKey;
	int BlowFishKeySize;

	static const unsigned int PBox[18];
	static const unsigned int SBox[4][256];

	unsigned int Key_PBox[18];
	unsigned int Key_SBox[4][256];

public:
	inline unsigned int KeyMaxSize(void)
	{
		return 256;
	}

	inline unsigned int KeyMinSize(void)
	{
		return 1;
	}

public:
	bool InitKey(unsigned char* pKey, int KeySize);
	bool EncryptData(unsigned char* pBufferIn, int BufferInSize, unsigned char* pBufferOut, int BufferOutSize);
	bool DecryptData(unsigned char* pBufferIn, int BufferInSize, unsigned char* pBufferOut, int BufferOutSize);

private:
	bool SetKey(unsigned char* pKey, int KeySize);

private:
	void KeyExpansion();
	void BlowFishRoundEncrypt(unsigned int* DataL, unsigned int* DataR);
	void BlowFishRoundDecrypt(unsigned int* DataL, unsigned int* DataR);
};