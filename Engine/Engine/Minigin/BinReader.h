#pragma once
#include <iostream>
#include <string>
#include <fstream>

class BinReader
{
public:
	BinReader(const std::string& readfile);
	~BinReader() = default;
	template<typename T>
	T Read()
	{
		T value{};
		if (m_Available)
		{
			m_Reader.read((char*)&value, sizeof(T));
		}
		return value;
	}
	void CloseFile();
private:
	bool m_Available;
	std::ifstream m_Reader;
};

