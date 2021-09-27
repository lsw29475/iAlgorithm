#pragma once

#define MAX_NUM_COUNT 4096

class _declspec(dllexport) CBIGNUM
{
public:
    CBIGNUM(void);
    ~CBIGNUM(void);

    CBIGNUM(const char *pString);

    bool operator<(CBIGNUM &n);
    bool operator>=(CBIGNUM &n);
    bool operator==(CBIGNUM &n);
    bool operator!=(CBIGNUM &n);

    CBIGNUM operator+(CBIGNUM &n);
    CBIGNUM operator-(CBIGNUM &n);
    CBIGNUM operator/(CBIGNUM &n);
    CBIGNUM operator*(CBIGNUM &n);
    CBIGNUM operator%(CBIGNUM &n);
    CBIGNUM BigPow(CBIGNUM &n);

public:
    int GetBitNumSize();

    void SetBitNum(int Pos, char Data);
    char GetBitNum(int Pos);

    char *GetData();
    void SetData(char *pIn);

    void ReverseBitNum();
    void Complement(int Bits);
    void Empty();
    void AppendBits(char *Data);
    void AppendBit(char Data);

    void RemovePrefix();

private:
    char m_data[MAX_NUM_COUNT];
};