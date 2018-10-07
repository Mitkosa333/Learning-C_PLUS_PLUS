#ifndef VIDEOTAG_H
#define VIDEOTAG_H

#include "Tags.h"

class VideoTag : public Tags
{
public:
	VideoTag(const MyString&, const MyString&, const MyString&);
	VideoTag(const VideoTag&);
	VideoTag& operator= (const VideoTag&);

public:
	void PrintOnConsole() const;
	void PrintInFile(std::ostream&) const;

private:
	MyString link;
};

#endif //VIDEOTAG_H
