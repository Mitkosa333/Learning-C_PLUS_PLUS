#include <iostream>
#include <fstream>

#include "Text.h"

int main()
{
	char path[_MAX_PATH];

	std::cout << "Choose file path:" << std::endl;
	std::cout << ">";
	std::cin >> path;

	std::ifstream myFile(path);
	
	Text myText (myFile);
	myText.WordCompareData("fmiLife");

	myFile.close();
}