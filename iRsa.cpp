#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "iRsa.h"

CRSA::CRSA(void)
{
}

CRSA::~CRSA(void)
{
}

bool CRSA::RsaEncInit(CBIGNUM q, CBIGNUM p, CBIGNUM e)
{
    m_q = q;
    m_p = p;
    m_e = e;

    m_n = q * p;

    return true;
}

bool CRSA::RsaDecInit(CBIGNUM q, CBIGNUM p, CBIGNUM d)
{
    m_q = q;
    m_p = p;
    m_d = d;

    m_n = q * p;

    return true;
}

void CRSA::RsaRoundEncrypt(unsigned char DataIn, unsigned char *pDataOut)
{
    CBIGNUM NumIn;
    char szTemp[4];

    _itoa(DataIn, szTemp, 10);
    NumIn.SetData(szTemp);
    NumIn = NumIn.BigPow(m_e);
    NumIn = NumIn % m_n;
    *pDataOut = atoi(NumIn.GetData());
}

void CRSA::RsaRoundDecrypt(unsigned char DataIn, unsigned char *pDataOut)
{
    CBIGNUM NumIn;
    char szTemp[4];

    _itoa(DataIn, szTemp, 10);
    NumIn.SetData(szTemp);
    NumIn = NumIn.BigPow(m_d);
    NumIn = NumIn % m_n;
    *pDataOut = atoi(NumIn.GetData());
}

bool CRSA::RsaEncrypt(unsigned char *pBufferIn, int BufferInSize, unsigned char *pBufferOut, int BufferOutSize)
{
    unsigned char temp;

    if (BufferOutSize < BufferInSize)
    {
        return false;
    }

    for (int i = 0; i < BufferInSize; i++)
    {
        RsaRoundEncrypt(*(pBufferIn + i), &temp);
        *(pBufferOut + i) = temp;
    }

    return true;
}

bool CRSA::RsaDecrypt(unsigned char *pBufferIn, int BufferInSize, unsigned char *pBufferOut, int BufferOutSize)
{
    unsigned char temp;

    if (BufferOutSize < BufferInSize)
    {
        return false;
    }

    for (int i = 0; i < BufferInSize; i++)
    {
        RsaRoundDecrypt(*(pBufferIn + i), &temp);
        *(pBufferOut + i) = temp;
    }

    return true;
}