#ifndef LINKTAG_H
#define LINKTAG_H

#include "Tags.h"

class LinkTag : public Tags
{
public:
	LinkTag(const MyString&, const MyString&, const MyString&);
	LinkTag(const LinkTag&);
	LinkTag& operator= (const LinkTag&);

public:
	void PrintOnConsole() const;
	void PrintInFile(std::ostream&) const;

private:
	MyString link;
};

#endif // LINKTAG_H
