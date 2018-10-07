#ifndef TAGS_H
#define TAGS_H

#include <fstream>
#include "MyString.h"

class Tags
{
public:
	virtual ~Tags();

public:
	virtual void PrintOnConsole() const = 0;
	virtual void PrintInFile(std::ostream&) const = 0;
	
public:
	const MyString& getDescr() const;

protected:
	MyString content;
	MyString descr;
};
 
#endif // TAGS_H