#include <iostream>

#include "String.h"
#include "Text.h"

void Program(Text&);

int main()
{
	Text data;
	Program(data);

	return 0;
}

void Program(Text& data)
{
	String command;

	for (;;)
	{
		std::cout << "Choose command:" << std::endl;
		std::cin >> command;
		if (command == "makeHeading")
		{
			unsigned line;
			std::cin >> line;
			if (data.getNumOfLines() >= line)
			{
				data.makeHeading(line);
			}
			else
			{
				std::cout << "Line does not exist" << std::endl;
			}
		}
		else if (command == "makeItalic")
		{
			unsigned line;
			unsigned from;
			unsigned to;
			std::cin >> line >> from >> to;
			if (data.getNumOfLines() >= line)
			{
				if ((data.getWordsOnLine(line) >= from) && (data.getWordsOnLine(line) >= to))
				{
					data.makeItalic(line, from, to);
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
			unsigned line;
			unsigned from;
			unsigned to;
			std::cin >> line >> from >> to;
			if (data.getNumOfLines() >= line)
			{
				if ((data.getWordsOnLine(line) >= from) && (data.getWordsOnLine(line) >= to))
				{
					data.makeBold(line, from, to);
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
			unsigned line;
			unsigned from;
			unsigned to;
			std::cin >> line >> from >> to;
			if (data.getNumOfLines() >= line)
			{
				if ((data.getWordsOnLine(line) >= from) && (data.getWordsOnLine(line) >= to))
				{
					data.makeCombine(line, from, to);
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
		else if (command == "addLine")
		{
			std::cin.get();
			String newLine;
			getline(std::cin, newLine);
			data.addLine(newLine);
		}
		else if (command == "remove")
		{
			unsigned line;
			std::cin >> line;
			if (data.getNumOfLines() >= line)
			{
				data.remove(line);
			}
			else
			{
				std::cout << "Line does not exist" << std::endl;
			}
		}
		else if (command == "exit")
		{
			if (!data.SaveFile())
			{
				std::cout << "Problem accured, last information was not saved to file!!!" << std::endl;
				std::cout << "Do you wish to quit the program without saving (yes or no): ";
				std::cin >> command;
				if (command == "yes")
				{
					return;
				}
			}
			else
			{
				return;
			}

		}
		else
		{
			std::cout << "Wrong command" << std::endl;
		}
	}
}