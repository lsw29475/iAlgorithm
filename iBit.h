#pragma once

#include <vector>
#include <iostream>

using namespace std;

class _declspec(dllexport) iBit
{
public:
	iBit();
	iBit(unsigned long In);
	iBit(unsigned char In);
	~iBit();

public:
	std::size_t getSize();
	std::string getData();

	void setData(unsigned long In, int Bits = 0);
	void setData(unsigned char In, int Bits = 0);

public:
	void iCat(iBit In);
	void iCat(std::string In);
	void iCat(std::string In, int pos);
	void iCat(std::string In, int StartPos, int Size);

	void iLeftShift(int Pos);
	void iRightShift(int Pos);

	void iXor(iBit In);

	void iClear();

private:
	std::string m_Data;
	std::size_t m_Size;
};