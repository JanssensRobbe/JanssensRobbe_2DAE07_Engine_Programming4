#pragma once
#include <string>
#include <fstream>



class BinWriter
{
public:
	BinWriter(const std::string& filepath);
	~BinWriter() = default;
	template<typename T>
	void Write(T value)
	{
		m_Writer.write((char*)&value, sizeof(T));
	}

	void CloseFile();

private:
	std::ofstream m_Writer;
	bool m_Exists = false;
};

