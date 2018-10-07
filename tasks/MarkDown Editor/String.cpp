#include "String.h"

String::String()
{
	this->length = 0;
	this->content = new char[this->length + 1];
	this->content[this->length] = '\0';
}

String::String(const char* source)
{
	this->length = strlen(source);
	this->content = new char[this->length + 1];
	strncpy(this->content, source, this->length + 1);
}

String::String(const String & obj)
{
	this->length = obj.length;
	this->content = new char[this->length + 1];
	strncpy(this->content, obj.content, this->length + 1);
}

String & String::operator=(const String & obj)
{
	if (this != &obj)
	{
		setContent(obj.content);
	}
	return *this;
}

String & String::operator=(const char * sourse)
{
	setContent(sourse);
	return *this;
}

void String::setElement(const unsigned i, const char ch)
{
	this->content[i] = ch;
}

void String::setContent(const char * source)
{
	unsigned tempLength = strlen(source);
	char* tempContent = new char[tempLength + 1];
	strncpy(tempContent, source, tempLength + 1);
	delete[] this->content;
	this->length = tempLength;
	this->content = tempContent;
}

void String::AddSymbolInBeg(const char ch)
{
	char* buffer = new char[this->length + 1];
	strcpy(buffer, this->content);
	delete[] this->content;
	this->length++;
	this->content = new char[this->length + 1];
	for (int i = 0; buffer[i - 1]; i++)
	{
		if (i == 0)
		{
			this->content[i] = ch;
		}
		else
		{
			this->content[i] = buffer[i - 1];
		}
	}
	this->content[this->length] = '\0';
	delete[] buffer;
}

void String::AddSymbolsAroundWords(const unsigned numOfSymbols, const char symbol, unsigned from, unsigned to)
{
	from--;
	to--;

	char* buffer = new char[this->length + 1];
	strncpy(buffer, this->content, this->length + 1);
	delete[] this->content;
	this->length += numOfSymbols * 2;
	this->content = new char[this->length + 1];
	int i = 0;
	while (buffer[i] == ' ' || buffer[i] == '\t')
	{
		this->content[i] = buffer[i];
		i++;
	}

	int counter = 1;
	while (counter < from)
	{
		if (((buffer[i] >= 'a') && (buffer[i] <= 'z')) || ((buffer[i] >= 'A') && (buffer[i] <= 'Z')))
		{
			counter++;
			while ((buffer[i] != ' ') && (buffer[i] != '\t') && (buffer[i] != '\0'))
			{
				this->content[i] = buffer[i];
				i++;
			}
		}
		else
		{
			this->content[i] = buffer[i];
			i++;
		}
	}

	if (counter != 1)
	{
		this->content[i] = buffer[i];
		i++;
	}

	int j = i;
	for (int t = 0; t < numOfSymbols; t++)
	{
		this->content[i] = symbol;
		i++;
	}

	counter = 0;

	while (counter <= to - from)
	{
		if (((buffer[j] >= 'a') && (buffer[j] <= 'z')) || ((buffer[j] >= 'A') && (buffer[j] <= 'Z')))
		{
			counter++;
			while ((buffer[j] != ' ') && (buffer[j] != '\t') && (buffer[j] != '\0'))
			{
				this->content[i] = buffer[j];
				i++;
				j++;
			}
		}
		else
		{
			this->content[i] = buffer[j];
			i++;
			j++;
		}
	} 

	for (int t = 0; t < numOfSymbols; t++)
	{
		this->content[i] = symbol;
		i++;
	}

	while (buffer[j] != '\0')
	{
		this->content[i] = buffer[j];
		i++;
		j++;
	}

	this->content[i] = '\0';

	delete[] buffer;
}

bool String::operator==(const String & obj)
{
	if (this->length != obj.length)
	{
		return false;
	}
	for (int i = 0; i < this->length; i++)
	{
		if (this->content[i] != obj.content[i])
		{
			return false;
		}
	}
	return true;
}

bool String::operator==(const char * string)
{
	if (this->length != strlen(string))
	{
		return false;
	}
	for (int i = 0; i < this->length; i++)
	{
		if (this->content[i] != string[i])
		{
			return false;
		}
	}
	return true;
}

unsigned String::CountWords() const
{
	unsigned counter = 0;
	int i = 0;
	while (this->content[i] != '\0')
	{
		if (((this->content[i] >= 'a') && (this->content[i] <= 'z')) || ((this->content[i] >= 'A') && (this->content[i] <= 'Z')))
		{
			counter++;
			while ((this->content[i] != ' ') && (this->content[i] != '\t') && (this->content[i] != '\0'))
			{
				i++;
			}
		}
		else
		{
			i++;
		}
	}
	return counter;

}

String::~String()
{
	delete[] this->content;
}

std::ostream & operator<<(std::ostream & out, const String & obj)
{
	out << obj.content;
	return out;
}

std::istream & operator>>(std::istream & in, String & obj)
{
	char buffer [MAX_SIZE];
	in >> buffer;
	obj.setContent(buffer);
	return in;
}

std::istream & getline(std::istream & in, String & obj)
{
	char buffer[MAX_SIZE];
	in.getline(buffer, MAX_SIZE);
	obj.setContent(buffer);
	return in;
}
