#pragma once

#include "iBigNum.h"

class _declspec(dllexport) CRSA
{
public:
    CRSA(void);
    ~CRSA(void);

    bool RsaEncInit(CBIGNUM q, CBIGNUM p, CBIGNUM e);
    bool RsaDecInit(CBIGNUM q, CBIGNUM p, CBIGNUM d);

    bool RsaEncrypt(unsigned char *pBufferIn, int BufferInSize, unsigned char *pBufferOut, int BufferOutSize);
    bool RsaDecrypt(unsigned char *pBufferIn, int BufferInSize, unsigned char *pBufferOut, int BufferOutSize);

private:
    void RsaRoundEncrypt(unsigned char DataIn, unsigned char *pDataOut);
    void RsaRoundDecrypt(unsigned char DataIn, unsigned char *pDataOut);

private:
    CBIGNUM m_q;
    CBIGNUM m_p;
    CBIGNUM m_e;
    CBIGNUM m_n;
    CBIGNUM m_d;
};