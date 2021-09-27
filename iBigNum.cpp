#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "iBigNum.h"

CBIGNUM::CBIGNUM(void)
{
    memset(m_data, 0x00, sizeof(m_data));
}

CBIGNUM::~CBIGNUM(void)
{
}

CBIGNUM::CBIGNUM(const char *pString)
{
    if (strlen(pString) > MAX_NUM_COUNT)
    {
        return;
    }

    memset(m_data, 0x00, sizeof(m_data));
    memcpy(m_data, pString, strlen(pString));
}

int CBIGNUM::GetBitNumSize()
{
    return strlen(m_data);
}

void CBIGNUM::SetBitNum(int Pos, char Data)
{
    m_data[Pos] = Data;
}

char CBIGNUM::GetBitNum(int Pos)
{
    return m_data[Pos];
}

void CBIGNUM::SetData(char *pIn)
{
    memcpy(m_data, pIn, strlen(pIn));
}

char *CBIGNUM::GetData()
{
    return m_data;
}

void CBIGNUM::ReverseBitNum()
{
    char temp;

    for (int i = 0, j = GetBitNumSize() - 1; i < GetBitNumSize() / 2; i++, j--)
    {
        temp = GetBitNum(i);
        SetBitNum(i, GetBitNum(j));
        SetBitNum(j, temp);
    }
}

void CBIGNUM::Complement(int Bits)
{
    char temp[MAX_NUM_COUNT];

    memset(temp, 0x00, sizeof(temp));
    memset(temp, 0x30, Bits);
    strcat(m_data, temp);
}

void CBIGNUM::Empty()
{
    memset(m_data, 0x00, sizeof(m_data));
}

void CBIGNUM::AppendBits(char *Data)
{
    strcat(m_data, Data);
}

void CBIGNUM::AppendBit(char Data)
{
    m_data[strlen(m_data)] = Data;
}

void CBIGNUM::RemovePrefix()
{
    int temp;

    for (temp = 0;; temp++)
    {
        if (m_data[temp] != '0')
        {
            break;
        }
    }

    memcpy(m_data, m_data + temp, sizeof(m_data) - temp);
}

bool CBIGNUM::operator<(CBIGNUM &n)
{
    CBIGNUM temp;

    temp.SetData(m_data);
    return !(temp >= n);
}

bool CBIGNUM::operator==(CBIGNUM &n)
{
    return strcmp(GetData(), n.GetData()) == 0;
}

bool CBIGNUM::operator!=(CBIGNUM &n)
{
    return strcmp(GetData(), n.GetData()) != 0;
}

bool CBIGNUM::operator>=(CBIGNUM &n)
{
    if (!strcmp(GetData(), n.GetData()))
    {
        return true;
    }

    if (GetBitNumSize() > n.GetBitNumSize())
    {
        return true;
    }
    else if (GetBitNumSize() < n.GetBitNumSize())
    {
        return false;
    }
    else if (GetBitNumSize() == n.GetBitNumSize())
    {
        for (int i = 0; i < GetBitNumSize(); i++)
        {
            if (GetBitNum(i) > n.GetBitNum(i))
            {
                return true;
            }
            else if (GetBitNum(i) < n.GetBitNum(i))
            {
                return false;
            }
        }
    }
}

CBIGNUM CBIGNUM::operator+(CBIGNUM &n)
{
    CBIGNUM left_temp;
    CBIGNUM right_temp;
    CBIGNUM result;

    int i_left_num;
    int i_right_num;
    int i_result_num;

    char c_left_num;
    char c_right_num;
    char c_result_num[2];

    bool blAdd = false;

    if (GetBitNumSize() > n.GetBitNumSize())
    {
        left_temp.SetData(m_data);
        for (int i = 0; i < GetBitNumSize() - n.GetBitNumSize(); i++)
        {
            right_temp.SetBitNum(i, '0');
        }
        for (int j = GetBitNumSize() - n.GetBitNumSize(), i = 0; j < GetBitNumSize(); j++, i++)
        {
            right_temp.SetBitNum(j, n.GetBitNum(i));
        }
    }
    else if (GetBitNumSize() < n.GetBitNumSize())
    {
        left_temp.SetData(n.GetData());
        for (int i = 0; i < n.GetBitNumSize() - GetBitNumSize(); i++)
        {
            right_temp.SetBitNum(i, '0');
        }
        for (int j = n.GetBitNumSize() - GetBitNumSize(), i = 0; j < n.GetBitNumSize(); j++, i++)
        {
            right_temp.SetBitNum(j, m_data[i]);
        }
    }
    else if (GetBitNumSize() == n.GetBitNumSize())
    {
        left_temp.SetData(m_data);
        right_temp.SetData(n.GetData());
    }

    for (int i = 0, j = left_temp.GetBitNumSize() - 1; i < left_temp.GetBitNumSize(); i++, j--)
    {
        c_left_num = left_temp.GetBitNum(j);
        c_right_num = right_temp.GetBitNum(j);
        i_left_num = atoi(&c_left_num);
        i_right_num = atoi(&c_right_num);
        i_result_num = i_left_num + i_right_num;

        if (blAdd)
        {
            i_result_num += 1;
            blAdd = false;
        }

        if (i_result_num >= 10)
        {
            i_result_num -= 10;
            blAdd = true;
        }

        _itoa(i_result_num, c_result_num, 10);
        result.SetBitNum(i, c_result_num[0]);
    }

    if (blAdd)
    {
        result.SetBitNum(result.GetBitNumSize(), '1');
    }

    result.ReverseBitNum();
    return result;
}

CBIGNUM CBIGNUM::operator-(CBIGNUM &n)
{
    CBIGNUM left_temp;
    CBIGNUM right_temp;
    CBIGNUM result;

    int i_left_num;
    int i_right_num;
    int i_result_num;

    char c_left_num;
    char c_right_num;
    char c_result_num[2];

    bool blSub = false;

    if (!strcmp(GetData(), n.GetData()))
    {
        return result;
    }

    if (GetBitNumSize() > n.GetBitNumSize())
    {
        left_temp.SetData(m_data);
        for (int i = 0; i < GetBitNumSize() - n.GetBitNumSize(); i++)
        {
            right_temp.SetBitNum(i, '0');
        }
        for (int j = GetBitNumSize() - n.GetBitNumSize(), i = 0; j < GetBitNumSize(); j++, i++)
        {
            right_temp.SetBitNum(j, n.GetBitNum(i));
        }
    }
    else if (GetBitNumSize() < n.GetBitNumSize())
    {
        left_temp.SetData(n.GetData());
        for (int i = 0; i < n.GetBitNumSize() - GetBitNumSize(); i++)
        {
            right_temp.SetBitNum(i, '0');
        }
        for (int j = n.GetBitNumSize() - GetBitNumSize(), i = 0; j < n.GetBitNumSize(); j++, i++)
        {
            right_temp.SetBitNum(j, m_data[i]);
        }
    }
    else if (GetBitNumSize() == n.GetBitNumSize())
    {
        for (int i = 0; i < GetBitNumSize(); i++)
        {
            if (GetBitNum(i) > n.GetBitNum(i))
            {
                left_temp.SetData(m_data);
                right_temp.SetData(n.GetData());
                break;
            }
            else if (GetBitNum(i) < n.GetBitNum(i))
            {
                left_temp.SetData(n.GetData());
                right_temp.SetData(m_data);
                break;
            }
        }
    }

    for (int i = 0, j = left_temp.GetBitNumSize() - 1; i < left_temp.GetBitNumSize(); i++, j--)
    {
        c_left_num = left_temp.GetBitNum(j);
        c_right_num = right_temp.GetBitNum(j);
        i_left_num = atoi(&c_left_num);
        i_right_num = atoi(&c_right_num);

        if (blSub)
        {
            i_left_num -= 1;
            blSub = false;
        }

        if (i_left_num < i_right_num)
        {
            i_left_num += 10;
            blSub = true;
        }

        i_result_num = i_left_num - i_right_num;
        _itoa(i_result_num, c_result_num, 10);
        result.SetBitNum(i, c_result_num[0]);
    }

    result.ReverseBitNum();
    return result;
}

CBIGNUM CBIGNUM::operator*(CBIGNUM &n)
{
    CBIGNUM left_temp;
    CBIGNUM right_temp;
    CBIGNUM calc_temp;
    CBIGNUM result;

    int i_right_num;
    char c_right_num;

    left_temp.SetData(m_data);
    if (left_temp >= n)
    {
        right_temp = n;
    }
    else
    {
        right_temp = left_temp;
        left_temp = n;
    }

    for (int i = 0; i < right_temp.GetBitNumSize(); i++)
    {
        calc_temp.Empty();
        c_right_num = right_temp.GetBitNum(i);
        i_right_num = atoi(&c_right_num);
        while (i_right_num != 0)
        {
            calc_temp = calc_temp + left_temp;
            i_right_num--;
        }

        calc_temp.Complement(right_temp.GetBitNumSize() - i - 1);
        result = result + calc_temp;
    }

    return result;
}

CBIGNUM CBIGNUM::operator/(CBIGNUM &n)
{
    CBIGNUM left_temp;
    CBIGNUM right_temp;
    CBIGNUM calc_temp;
    CBIGNUM add_temp;
    CBIGNUM result_temp;
    CBIGNUM result;

    int pos;
    int i_num;
    char c_num[2];

    left_temp.SetData(m_data);
    if (left_temp >= n)
    {
        right_temp = n;
    }
    else
    {
        right_temp = left_temp;
        left_temp = n;
    }

    for (pos = 0; pos != left_temp.GetBitNumSize(); pos++)
    {
        calc_temp.AppendBit(left_temp.GetBitNum(pos));
        if (calc_temp < right_temp)
        {
            continue;
        }

        add_temp.Empty();
        for (i_num = 1; i_num < 10; i_num++)
        {
            add_temp = add_temp + right_temp;
            if (add_temp >= calc_temp)
            {
                break;
            }
        }

        result_temp.Empty();
        if (add_temp == calc_temp)
        {
            _itoa(i_num, c_num, 10);
            result_temp.SetBitNum(0, c_num[0]);
            result_temp.Complement(left_temp.GetBitNumSize() - pos - 1);
        }
        else if (add_temp < calc_temp)
        {
            _itoa(i_num - 1, c_num, 10);
            result_temp.SetBitNum(0, c_num[0]);
            result_temp.Complement(left_temp.GetBitNumSize() - pos - 1);
        }
        else
        {
            _itoa(i_num - 1, c_num, 10);
            result_temp.SetBitNum(0, c_num[0]);
            result_temp.Complement(left_temp.GetBitNumSize() - pos - 1);
            add_temp = add_temp - right_temp;
        }

        add_temp.RemovePrefix();
        result = result + result_temp;
        calc_temp = calc_temp - add_temp;
        calc_temp.RemovePrefix();
    }

    return result;
}

CBIGNUM CBIGNUM::operator%(CBIGNUM &n)
{
    CBIGNUM left_temp;
    CBIGNUM right_temp;
    CBIGNUM calc_temp;
    CBIGNUM add_temp;
    CBIGNUM result_temp;
    CBIGNUM result;

    int pos;
    int i_num;
    char c_num[2];

    left_temp.SetData(m_data);
    if (left_temp >= n)
    {
        right_temp = n;
    }
    else
    {
        right_temp = left_temp;
        left_temp = n;
    }

    for (pos = 0; pos != left_temp.GetBitNumSize(); pos++)
    {
        calc_temp.AppendBit(left_temp.GetBitNum(pos));
        calc_temp.RemovePrefix();
        if (calc_temp < right_temp)
        {
            continue;
        }

        add_temp.Empty();
        for (i_num = 1; i_num < 10; i_num++)
        {
            add_temp = add_temp + right_temp;
            if (add_temp >= calc_temp)
            {
                break;
            }
        }

        result_temp.Empty();
        if (add_temp == calc_temp)
        {
            _itoa(i_num, c_num, 10);
            result_temp.SetBitNum(0, c_num[0]);
            result_temp.Complement(left_temp.GetBitNumSize() - pos - 1);
        }
        else if (add_temp < calc_temp)
        {
            _itoa(i_num - 1, c_num, 10);
            result_temp.SetBitNum(0, c_num[0]);
            result_temp.Complement(left_temp.GetBitNumSize() - pos - 1);
        }
        else
        {
            _itoa(i_num - 1, c_num, 10);
            result_temp.SetBitNum(0, c_num[0]);
            result_temp.Complement(left_temp.GetBitNumSize() - pos - 1);
            add_temp = add_temp - right_temp;
        }

        add_temp.RemovePrefix();
        result = result + result_temp;
        calc_temp = calc_temp - add_temp;
        calc_temp.RemovePrefix();
    }

    return calc_temp;
}

CBIGNUM CBIGNUM::BigPow(CBIGNUM &n)
{
    CBIGNUM left_temp;
    CBIGNUM right_temp;
    CBIGNUM result;
    CBIGNUM sub_temp;

    result.SetData(m_data);
    left_temp.SetData(m_data);
    right_temp.SetData(n.GetData());
    sub_temp.SetData((char *)"1");

    do
    {
        result = result * left_temp;
        right_temp = right_temp - sub_temp;
        right_temp.RemovePrefix();
    } while (right_temp != sub_temp);

    return result;
}