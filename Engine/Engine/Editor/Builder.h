#pragma once
#include <vector>
class Builder
{
public:
	Builder(unsigned w, unsigned h);
	~Builder() = default;

	void SetTunnel(unsigned index, bool state = true);
	void Write(std::string fileName);
	void Show();
private:
	std::vector<bool> m_Level;
	unsigned m_Width = 0, m_Height = 0;

};

