#ifndef MY_STRING_H
#define MY_STRING_H

#include <iostream>

#include "MyVector.hpp"

class MyString
{
	//Big 4 (destructor is absent because it uses the destructor from "MyVector")
public:
	MyString();
	MyString(const char*);
	MyString(const MyString&);
	MyString operator=(const MyString&);

	//operators
public:
	MyString & operator+=(const MyString&);
	char& operator[](const unsigned);
	char& operator[](const unsigned) const;

	//methods
public:
	void push_back(const char);
	void clear();
	unsigned get_size() const;
	void remove_char(const unsigned& index);

	MyString subString(int firstIndex, int lastIndex) const;
	//members
private:
	MyVector<char> string_m;
};

	//outside functions using the main class
MyString get_first_word(const MyString&);
bool compare(const MyString& first, const MyString& second);
bool compare(const MyString& first, const char* second);
void swap(MyString& first, MyString& second);
MyString operator+(const MyString& first, const MyString& second);

	//stream operators
std::istream & untilSymbol(std::istream & in, MyString& obj, const char&);
std::istream & getline(std::istream & in, MyString& obj, const char del = '\n');
std::istream & operator>>(std::istream & in, MyString& obj);
std::ostream & operator<<(std::ostream & out, const MyString& obj);

#endif // MY_STRING_H
