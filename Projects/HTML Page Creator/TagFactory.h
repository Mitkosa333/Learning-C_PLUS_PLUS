#ifndef TAG_FACTORY_H
#define TAG_FACTORY_H

#include "MyString.h"
#include "MyVector.hpp"
#include "HeaderTag.h"
#include "ImageTag.h"
#include "LinkTag.h"
#include "ParagaphTag.h"
#include "VideoTag.h"
#include "Tags.h"

class TagFactory
{
public:
	Tags * CreateTagFile(const MyVector<MyString>&) const;
	Tags* CreateTagKeyboard(const MyVector<MyString>&) const;
};

bool is_header(const MyString&);

#endif //TAG_FACTORY_H
