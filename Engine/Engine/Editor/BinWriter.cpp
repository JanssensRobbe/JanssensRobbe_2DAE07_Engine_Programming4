
#include "pch.h"
#include "BinWriter.h"
#include <iostream>



BinWriter::BinWriter(const std::string& path)
	: m_Writer(std::ofstream(path.c_str(), std::ios::out | std::ios::binary))
{
	if (m_Writer.is_open())
	{
		m_Exists = true;
	}
	else
	{
		std::cout << "Failed to write: " << path << '\n';
	}

}

void BinWriter::CloseFile()
{
	m_Exists = false;
	m_Writer.close();
}