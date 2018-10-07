#ifndef HEADERTAG_H
#define HEADERTAG_H

#include "Tags.h"

class HeaderTag : public Tags
{
public:
	HeaderTag();
	HeaderTag(const MyString&, const MyString&, const unsigned);
	HeaderTag(const HeaderTag&);
	HeaderTag& operator= (const HeaderTag&);

public:
	void PrintOnConsole() const;
	void PrintInFile(std::ostream&) const;

private:
	unsigned header_size;
};

#endif //HEADERTAG_H
