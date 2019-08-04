#include "iBit.h"

iBit::iBit()
{

}

iBit::~iBit()
{

}

iBit::iBit(unsigned char In)
{
	setData(In);
}

iBit::iBit(unsigned long In)
{
	setData(In);
}

void iBit::setData(unsigned char In, int Bits)
{
	char Temp[16] = { 0x00 };

	m_Data = "";
	_itoa_s((int)In, Temp, 2);

	if (Bits == 0)
	{
		m_Data = Temp;
	}
	else if (Bits <= 8 && (size_t)Bits>strlen((const char*)Temp))
	{
		for (int i = 0; (size_t)i < (size_t)Bits - strlen((const char*)Temp); i++)
		{
			m_Data += "0";
		}
		m_Data += Temp;
	}
	else
	{
		m_Data = Temp;
	}

	m_Size = m_Data.size();
}

void iBit::setData(unsigned long In, int Bits)
{
	char Temp[16] = { 0x00 };

	m_Data = "";
	_ultoa_s(In, Temp, 2);

	if (Bits == 0)
	{
		m_Data = Temp;
	}
	else if ((size_t)Bits <= 8 && (size_t)Bits > strlen((const char*)Temp))
	{
		for (int i = 0; (size_t)i < (size_t)Bits - strlen((const char*)Temp); i++)
		{
			m_Data += "0";
		}
		m_Data += Temp;
	}
	else
	{
		m_Data = Temp;
	}

	m_Size = m_Data.size();
}

size_t iBit::getSize()
{
	m_Size = m_Data.size();
	return m_Size;
}

std::string iBit::getData()
{
	return m_Data;
}

void iBit::iCat(iBit In)
{
	m_Data += In.getData();
	m_Size = m_Data.size();
}

void iBit::iCat(std::string In)
{
	m_Data += In;
	m_Size = m_Data.size();
}

void iBit::iCat(std::string In, int pos)
{
	char szTemp[5] = { 0x00 };

	szTemp[0] = In.at(pos);
	m_Data += szTemp;

	m_Size = m_Data.size();
}

void iBit::iCat(std::string In, int StartPos, int Size)
{
	char* pTemp = NULL;

	pTemp = new char[Size + 1];
	memset(pTemp, 0x00, Size + 1);
	memcpy(pTemp, In.c_str() + StartPos, Size);

	m_Data += pTemp;
	m_Size = m_Data.size();
	delete[] pTemp;
}

void iBit::iLeftShift(int Pos)
{
	char* pTemp = NULL;

	m_Size = m_Data.size();
	pTemp = new char[m_Size + 1];
	memset(pTemp, 0x00, m_Size + 1);

	memcpy(pTemp, m_Data.c_str() + Pos, m_Size - Pos);
	memcpy(pTemp + m_Size - Pos, m_Data.c_str(), Pos);

	m_Data = pTemp;
	delete[] pTemp;
}

void iBit::iRightShift(int Pos)
{
	char* pTemp = NULL;

	m_Size = m_Data.size();
	pTemp = new char[m_Size + 1];
	memset(pTemp, 0x00, m_Size + 1);

	memcpy(pTemp, m_Data.c_str() + (m_Size - Pos), Pos);
	memcpy(pTemp + m_Size - Pos, m_Data.c_str(), m_Size - Pos);

	m_Data = pTemp;
	delete[] pTemp;
}

void iBit::iXor(iBit In)
{
	iBit Temp;

	for (int i = 0; (size_t)i < m_Size; i++)
	{
		if ((m_Data.c_str()[i] == '0' && In.getData().c_str()[i] == '0') || (m_Data.c_str()[i] == '1' && In.getData().c_str()[i] == '1'))
		{
			Temp.iCat("0");
		}
		else
		{
			Temp.iCat("1");
		}
	}

	m_Data = Temp.getData();
}

void iBit::iClear()
{
	m_Data = "";
}