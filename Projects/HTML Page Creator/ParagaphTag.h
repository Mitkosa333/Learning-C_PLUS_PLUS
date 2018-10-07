#ifndef PARAGRAPHTAG_H
#define PARAGRAPHTAG_H

#include "Tags.h"

class ParagraphTag : public Tags
{
public:
	ParagraphTag(const MyString&, const MyString&);
	ParagraphTag(const ParagraphTag&);
	ParagraphTag& operator= (const ParagraphTag&);

public:
	void PrintOnConsole() const;
	void PrintInFile(std::ostream&) const;
};

#endif //PARAGRAPHTAG_H
