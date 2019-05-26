#include "MiniginPCH.h"
#include "BinReader.h"



BinReader::BinReader(const std::string& readfile)
	:m_Available(false)
	, m_Reader{ std::ifstream(readfile.c_str(), std::ios::in | std::ios::binary) }
{
	if (m_Reader.is_open())
		m_Available = true;
}

void BinReader::CloseFile()
{
	m_Reader.close();
}
