#include "Text.h"

bool Text::LoadFile()
{
	std::ifstream textFile(this->nameOfSourceFile);
	if (!textFile.good())
	{
		return false;
	}
	
	this->numOfLines = CountLinesInFile(textFile);
	
	this->content = new String[this->numOfLines];
	for (int i = 0; i < this->numOfLines; i++)
	{
		getline(textFile, this->content[i]);
	}

	textFile.close();
}

void Text::TransformFileExtToMd()
{
	int i = 0;
	while (this->nameOfSourceFile[i] != '.')
	{
		i++;
	}

	i++;
	this->nameOfSourceFile[i] = 'm';
	i++;
	this->nameOfSourceFile[i] = 'd';
	i++;
	this->nameOfSourceFile[i] = '\0';

}

unsigned Text::CountLinesInFile(std::ifstream& textFile) const 
{
	unsigned counter = 0;
	String tester;
	while (getline(textFile, tester))
	{
		counter++;
	}

	textFile.clear();
	textFile.seekg(0, std::ios::beg);

	return counter;
}

Text::Text()
{
	for (;;)
	{
		std::cout << "Enter file name:";
		std::cin.getline(this->nameOfSourceFile, _MAX_PATH);
		if (!LoadFile())
		{
			std::cout << "No Such File!" << std::endl;
		}
		else
		{
			TransformFileExtToMd();
			break;
		}
	}
}

Text::Text(const char * fileName)
{
	strncpy(this->nameOfSourceFile, fileName, _MAX_PATH);
	for (;;)
	{
		if (!LoadFile())
		{
			std::cout << "No Such File!" << std::endl;
			std::cout << "Enter file name:";
			std::cin.getline(this->nameOfSourceFile, _MAX_PATH);

		}
		else
		{
			TransformFileExtToMd();
			break;
		}
	}
}

Text::Text(const Text & obj)
{
	this->numOfLines = obj.numOfLines;
	strncpy(this->nameOfSourceFile, obj.nameOfSourceFile, _MAX_PATH);
	this->content = new String[this->numOfLines];
	for (int i = 0; i < this->numOfLines; i++)
	{
		this->content[i] = obj.content[i];
	}
}

unsigned Text::getWordsOnLine(const unsigned line)
{
	return this->content[line - 1].CountWords();
}

void Text::makeHeading(const unsigned line)
{
	this->content[line - 1].AddSymbolInBeg('#');
}

void Text::makeItalic(const unsigned line, const unsigned from, const unsigned to)
{
	this->content[line - 1].AddSymbolsAroundWords(italic, symbol, from, to);
}

void Text::makeBold(const unsigned line, const unsigned from, const unsigned to)
{
	this->content[line - 1].AddSymbolsAroundWords(bold, symbol, from, to);
}

void Text::makeCombine(const unsigned line, const unsigned from, const unsigned to)
{
	this->content[line - 1].AddSymbolsAroundWords(combine, symbol, from, to);
}

void Text::addLine(const String & newLine)
{
	String* buffer = new String[this->numOfLines];
	for (int i = 0; i < this->numOfLines; i++)
	{
		buffer[i] = this->content[i];
	}
	delete[] this->content;
	this->numOfLines++;
	this->content = new String[this->numOfLines];
	for (int i = 0; i < this->numOfLines-1; i++)
	{
		this->content[i] = buffer[i];
	}
	this->content[numOfLines - 1] = newLine;
	delete[] buffer;

	ChooseCommand(numOfLines);
}

void Text::remove(const unsigned line)
{
	String* buffer = new String[this->numOfLines];
	for (int i = 0; i < this->numOfLines; i++)
	{
		buffer[i] = this->content[i];
	}
	delete[] this->content;
	this->numOfLines--;
	this->content = new String[this->numOfLines];
	int i = 0;
	while (i < line - 1)
	{
		this->content[i] = buffer[i];
		i++;
	}
	int j = i;
	i++;
	while (j < this->numOfLines)
	{
		this->content[j] = buffer[i];
		j++;
		i++;
	}
	delete[] buffer;
}

void Text::ChooseCommand(const unsigned line)
{
	String command;

	for (;;)
	{
		std::cout << "Choose command for the new line:" << std::endl;
		std::cin >> command;
		if (command == "makeHeading")
		{
			if (getNumOfLines() >= line)
			{
				makeHeading(line);
			}
			else
			{
				std::cout << "Line does not exist" << std::endl;
			}
		}
		else if (command == "makeItalic")
		{
			unsigned from;
			unsigned to;
			std::cin >> from >> to;
			if (getNumOfLines() >= line)
			{
				if ((getWordsOnLine(line) >= from) && (getWordsOnLine(line) >= to))
				{
					makeItalic(line, from, to);
				}
				else
				{
					std::cout << "Word range doesn't exist!" << std::endl;
				}
			}
			else
			{
				std::cout << "Line does not exist" << std::endl;
			}
		}
		else if (command == "makeBold")
		{
			unsigned from;
			unsigned to;
			std::cin >> from >> to;
			if (getNumOfLines() >= line)
			{
				if ((getWordsOnLine(line) >= from) && (getWordsOnLine(line) >= to))
				{
					makeBold(line, from, to);
				}
				else
				{
					std::cout << "Word range doesn't exist!" << std::endl;
				}
			}
			else
			{
				std::cout << "Line does not exist" << std::endl;
			}
		}
		else if (command == "makeCombine")
		{
			unsigned from;
			unsigned to;
			std::cin >> from >> to;
			if (getNumOfLines() >= line)
			{
				if ((getWordsOnLine(line) >= from) && (getWordsOnLine(line) >= to))
				{
					makeCombine(line, from, to);
				}
				else
				{
					std::cout << "Word range doesn't exist!" << std::endl;
				}
			}
			else
			{
				std::cout << "Line does not exist" << std::endl;
			}
		}
		else if (command == "remove")
		{
			if (getNumOfLines() >= line)
			{
				remove(line);
				std::cout << "The new line was removed, back to main menu..." << std::endl;
				return;
			}
			else
			{
				std::cout << "Line does not exist" << std::endl;
			}
		}
		else if (command == "exit")
		{
			std::cout << "Exiting from line commands, going back to main menu..." << std::endl;
			return;
		}
		else if (command == "done")
		{
			std::cout << "Exiting from line commands, going back to main menu..." << std::endl;
			return;
		}
		else
		{
			std::cout << "Wrong command" << std::endl;
		}
	}
}

bool Text::SaveFile()
{
	std::ofstream textFile (this->nameOfSourceFile, std::ios::trunc);
	if (!textFile.good())
	{
		return false;
	}
	for (int i = 0; i < this->numOfLines; i++)
	{
		textFile << this->content[i].getContent() << std::endl;
	}

	textFile.close();
	return true;
}

Text::~Text()
{
	delete[] this->content;
}
