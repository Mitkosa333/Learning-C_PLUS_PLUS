#include "HTMLManager.h"

HTMLManager::~HTMLManager()
{
	clean();
}

HTMLManager & HTMLManager::getInstance()
{
	static HTMLManager instance;
	return instance;
}

void HTMLManager::Menu()
{
	MyString command;
	while (1)
	{
		std::cout << "Enter command:" << std::endl;
		std::cout << ">";
		std::cin >> command;
		if (compare(command, "add"))
		{
			Add();
		}
		else if (compare(command, "remove"))
		{
			Remove();
		}
		else if (compare(command, "print"))
		{
			Print();
		}
		else if (compare(command, "moveTo"))
		{
			MoveTo();
		}
		else if (compare(command, "load"))
		{
			Load();
		}
		else if (compare(command, "save"))
		{
			Save();
		}
		else if (compare(command, "exit"))
		{
			return;
		}
		else
		{
			std::cout << "Wrong Command!" << std::endl;
		}
	}
}

void HTMLManager::Add()
{
	TagFactory factory;
	MyString type;
	std::cin >> type;

	MyString descr;
	MyString link;
	MyString content;

	if (compare(type, "link") || compare(type, "video"))
	{
		getline(std::cin, descr);
		getline(std::cin, link);
		getline(std::cin, content);
	}
	else if (compare(type, "image"))
	{
		getline(std::cin, descr);
		getline(std::cin, link);
	}
	else if (compare(type, "text") || is_header("header"))
	{
		getline(std::cin, descr);
		getline(std::cin, content);
	}
	else
	{
		std::cerr << "Invalid Type!" << std::endl;
		return;
	}

	MyVector<MyString> new_tag;
	new_tag.push_back(type);
	new_tag.push_back(descr);
	new_tag.push_back(link);
	new_tag.push_back(content);

	Tags* result = factory.CreateTagKeyboard(new_tag);
	if (result != nullptr)
	{
		HTMLdata.push_back(result);
	}
}

void HTMLManager::Remove()
{
	MyString descr;
	getline(std::cin, descr);
	bool is_found = false;
	int line = 0;
	for (int i = 0; i < HTMLdata.get_cur_objects(); i++)
	{
		if (compare(descr, HTMLdata[i]->getDescr()))
		{
			is_found = true;
			line = i;
			break;
		}
	}

	if (is_found == true)
	{
		delete HTMLdata[line];
		for (int i = line; i < HTMLdata.get_cur_objects() - 1; i++)
		{
			HTMLdata[i] = HTMLdata[i + 1];
		}
		HTMLdata.pop_back();
	}
	else
	{
		std::cerr << "Line does not exist!" << std::endl;
	}
}

void HTMLManager::Print() const
{
	std::cout << "Printing Tags:" << std::endl;
	for (int i = 0; i < HTMLdata.get_cur_objects(); i++)
	{
		std::cout << i + 1 << ". ";
		HTMLdata[i]->PrintOnConsole();
		std::cout << std::endl;
	}
}

void HTMLManager::MoveTo()
{
	int to = 0;
	std::cin >> to;
	to -= 1;
	
	MyString descr;
	std::cin.get();
	getline(std::cin, descr);
	bool is_found = false;
	int from = 0;
	for (int i = 0; i < HTMLdata.get_cur_objects(); i++)
	{
		if (compare(descr, HTMLdata[i]->getDescr()))
		{
			is_found = true;
			from = i;
			break;
		}
	}

	if (from != to	&& to < HTMLdata.get_cur_objects() && to >= 0 && is_found == true)
	{
		if (from < to)
		{
			for (int i = from; i < to; i++)
			{
				swap(HTMLdata[i], HTMLdata[i + 1]);
			}
		}
		else
		{
			for (int i = from; i > to; i--)
			{
				swap(HTMLdata[i], HTMLdata[i - 1]);
			}
		}
	}
	else
	{
		std::cerr << "Invalid Numbers!" << std::endl;
	}
}

void HTMLManager::Load()
{
	clean();
	
	char file_name[_MAX_PATH];
	std::cin.getline(file_name, _MAX_PATH);

	std::ifstream loadFile(file_name);
	char temp = 0;
	MyVector<MyString> tag;
	MyString tempString;
	bool flag = false;
	while (loadFile.get(temp))
	{
		if ((temp != '<' && temp != '>' && temp != ' ' && temp != '\n' && temp != '=') || flag)
		{
			if (temp == '\"')
			{
				flag = !flag;
				continue;
			}
			tempString.push_back(temp);
		}
		else if (tempString.get_size() != 0)
		{
			tag.push_back(tempString);
			tempString.clear();
			if (temp == '>')
			{
				while (loadFile.get(temp) && temp != '<')
				{
					if (temp != '\n')
					{
						tempString.push_back(temp);
					}
				}
				tag.push_back(tempString);
				tempString.clear();
			}

		}

		if ((temp == '>' || temp == '<')&& tag.get_cur_objects() != 0)
		{
			TagFactory factory;
			Tags* result = factory.CreateTagFile(tag);
			if (result != nullptr)
			{
				HTMLdata.push_back(result);
			}
			tag.clear();
		}
	}

	loadFile.close();
}

void HTMLManager::Save() const
{
	char file_name[_MAX_PATH];
	std::cin.getline(file_name, _MAX_PATH);

	std::ofstream saveFile(file_name);
	
	if (saveFile.good())
	{
		BegOfFile(saveFile);
		AddTagsToFile(saveFile);
		EndOfFile(saveFile);
	}
	else
	{
		std::cerr << "Can't open file!" << std::endl;
	}
	saveFile.close();
}

void HTMLManager::BegOfFile(std::ofstream & saveFile) const
{
	saveFile << "<!DOCTYPE html>" << std::endl;
	saveFile << "<html>" << std::endl;
	saveFile << "<head> </head>" << std::endl;
	saveFile << "<body>" << std::endl;
}

void HTMLManager::AddTagsToFile(std::ofstream & saveFile) const
{
	for (int i = 0; i < HTMLdata.get_cur_objects(); i++)
	{
		HTMLdata[i]->PrintInFile(saveFile);
		saveFile << std::endl;
		saveFile << "<br>" << std::endl;
	}
}

void HTMLManager::EndOfFile(std::ofstream & saveFile) const
{
	saveFile << "</body>" << std::endl;
	saveFile << "</html>" << std::endl;
}

void HTMLManager::clean()
{
	for (int i = 0; i < HTMLdata.get_cur_objects(); i++)
	{
		delete HTMLdata[i];
	}
	HTMLdata.clear();
}
