// Editor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include "Builder.h"

int main()
{
	int w = 0;
	int h = 0;
	int posX = 0, posY = 0;

	std::string name{};
	std::string function{};

	std::cout << "'Add posX posY' = tunnel" << std::endl;
	std::cout << "'Delete posX posY' = remove tunnel" << std::endl;
	std::cout << "'Show 'Random number' 'Random number'' = show level" << std::endl;
	std::cout << "'Close 'Random number' 'Random number'' = create bin file" << std::endl;

	std::cout << "fileName: ";
	std::cin >> name;
	std::cout << "Width: ";
	std::cin >> w;
	std::cout << "Height: ";
	std::cin >> h;

	

	if (w <= 0 || h <= 0)
	{
		std::cout << "width or height is less than or equal to 0 and is not allowed" << std::endl;
		return 0;
	}

	Builder newLevel{ static_cast<unsigned>(w), static_cast<unsigned>(h) };

	while (function != "Close")
	{
		std::cout << ">> ";
		std::cin >> function >> posX >> posY;
		if (function == "Add")
		{
			if (posX < w && posY < h)
				newLevel.SetTunnel(posY*w + posX, true);
		}
		if (function == "Delete")
		{
			if (posX < w && posY < h)
				newLevel.SetTunnel(posY*w+ posX, false);
		}
		if (function == "Show")
		{
			newLevel.Show();
		}

	}

	newLevel.Write(name);
	return 0;

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
