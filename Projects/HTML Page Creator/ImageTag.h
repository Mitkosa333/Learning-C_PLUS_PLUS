#ifndef IMAGETAG_H
#define IMAGETAG_H

#include "Tags.h"

class ImageTag : public Tags
{
public:
	ImageTag(const MyString&, const MyString&);
	ImageTag(const ImageTag&);
	ImageTag& operator= (const ImageTag&);

public:
	void PrintOnConsole() const;
	void PrintInFile(std::ostream&) const;
};

#endif // IMAGETAG_H
