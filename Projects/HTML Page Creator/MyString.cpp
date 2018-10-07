#include "MyString.h"

MyString::MyString()
{
	string_m.push_back('\0');
}

MyString::MyString(const char * string)
{
	for (int i = 0; string[i] != '\0'; i++)
	{
		string_m.push_back(string[i]);
	}
	string_m.push_back('\0');
}

MyString::MyString(const MyString& obj)
{
	string_m = obj.string_m;
}

MyString MyString::operator=(const MyString & obj)
{
	if (&obj != this)
	{
		string_m = obj.string_m;
	}

	return *this;
}


MyString & MyString::operator+=(const MyString & obj)
{
	string_m.pop_back();
	for (int i = 0; obj.string_m[i] != '\0'; i++)
	{
		string_m.push_back(obj.string_m[i]);
	}
	string_m.push_back('\0');
	
	return *this;
}

char & MyString::operator[](const unsigned index)
{
	return string_m[index];
}

char & MyString::operator[](const unsigned index) const
{
	return string_m[index];
}

void MyString::push_back(const char symbol)
{
	string_m.back() = symbol;
	string_m.push_back('\0');
}

void MyString::clear()
{
	MyString cleared;
	*this = cleared;
}

unsigned MyString::get_size() const
{
	return (string_m.get_cur_objects() - 1);
}

void MyString::remove_char(const unsigned & index)
{
	string_m.remove_member(index);
}

MyString MyString::subString(int firstIndex, int lastIndex) const
{
	if (firstIndex < 0
		&& firstIndex >= get_size()
		&& lastIndex <= firstIndex
		&& lastIndex < 0
		&& lastIndex >= get_size())
	{
		std::cerr << "Error: wrong indexes" << std::endl;
	}

	MyString temp;
	for (int i = firstIndex; i <= lastIndex; ++i)
	{
		temp.push_back((*this)[i]);
	}
	return temp;
}

MyString get_first_word(const MyString & string)
{
	MyString buffer;
	for (int i = 0; string[i] != ' ' && string[i] != '\0'; i++)
	{
		buffer.push_back(string[i]);
	}
	return buffer;
}

bool compare(const MyString & first, const MyString & second)
{
	if (first.get_size() != second.get_size())
	{
		return false;
	}
	for (int i = 0; first[i] != '\0'; i++)
	{
		if (first[i] != second[i])
		{
			return false;
		}
	}
	return true;
}

bool compare(const MyString & first, const char * second)
{
	if (first.get_size() != strlen(second))
	{
		return false;
	}
	for (int i = 0; first[i] != '\0'; i++)
	{
		if (first[i] != second[i])
		{
			return false;
		}
	}
	return true;
}

void swap(MyString & first, MyString & second)
{
	MyString temp = first;
	first = second;
	second = temp;
}

MyString operator+(const MyString & first, const MyString & second)
{
	MyString temp = first;
	temp += second;
	return temp;
}

std::istream & untilSymbol(std::istream & in, MyString & obj, const char& symbol)
{
	obj.clear();
	char test;
	while (in.get(test) && test != symbol && test != '\n')
	{
		obj.push_back(test);
	}

	return in;
}

std::istream & getline(std::istream & in, MyString & obj,const char del)
{
	obj.clear();
	char test = '\0';
	while (in.get(test) && test != del)
	{
		obj.push_back(test);
	}

	return in;
}

std::istream & operator>>(std::istream & in, MyString & obj)
{
	obj.clear();
	char test;
	while (in.get(test) && test != ' ' && test != '\n')
	{
		obj.push_back(test);
	}

	return in;
}

std::ostream & operator<<(std::ostream & out, const MyString & obj)
{
	for (int i = 0; obj[i] != '\0'; i++)
	{
		out << obj[i];
	}
	return out;
}
