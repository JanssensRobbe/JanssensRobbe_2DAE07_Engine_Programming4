#include "pch.h"
#include "Builder.h"
#include "BinWriter.h"
#include <iostream>

Builder::Builder(unsigned w, unsigned h)
	:m_Width(w)
	, m_Height(h)
{
	m_Level.resize(w * h);
	for (unsigned int i = 0; i < w * h; ++i)
	{
		m_Level[i] = false;
	}
}



void Builder::SetTunnel(unsigned index, bool state)
{
	m_Level[index] = state;
}



void Builder::Write(std::string fileName)
{
	BinWriter writer{ fileName + ".bin" };
	for (bool element : m_Level)
		writer.Write<bool>(element);
	writer.CloseFile();
}



void Builder::Show()
{
	std::cout << '\t';
	for (unsigned i = 0; i < m_Width; ++i)
		std::cout << i << '\t';
	std::cout << std::endl;
	for (unsigned i = 0; i < m_Height; ++i)
	{
		std::cout << i << '\t';
		for (unsigned j = 0; j < m_Width; ++j)
		{
			if (!m_Level[i*m_Width + j])
				std::cout << 'O' << '\t';
			else
				std::cout << 'X' << '\t';
		}
		std::cout << std::endl;

	}

}