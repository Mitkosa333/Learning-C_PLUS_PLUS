#ifndef STRING_H
#define STRING_H

#include <iostream>

const unsigned MAX_SIZE = 1024;

class String 
{
private:
	char* content;
	unsigned length;

public:
	String();
	String(const char*);
	String(const String&);
	String& operator=(const String&);
	String& operator=(const char*);
	

	void setElement(const unsigned, const char);
	char getElement(const unsigned i) const { return content[i]; }
	void setContent(const char*);
	char* getContent() const { return content; } 
	
	void AddSymbolInBeg(const char);
	void AddSymbolsAroundWords(const unsigned, const char, unsigned, unsigned);

	bool operator==(const String&);
	bool operator==(const char*);

	unsigned CountWords() const;
	
	~String();

	friend std::ostream& operator<<(std::ostream&, const String&);
	friend std::istream& operator>>(std::istream&, String&);
	friend std::istream& getline(std::istream&, String&);
};

std::ostream& operator<<(std::ostream&, const String&);
std::istream& operator>>(std::istream&, String&);
std::istream& getline(std::istream&, String&);

#endif //STRING_H
