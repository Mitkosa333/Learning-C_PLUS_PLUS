#include "TagFactory.h"

Tags * TagFactory::CreateTagFile(const MyVector<MyString>& strings) const
{
	Tags* result = nullptr;

	MyString type = strings[0];
	MyString content;
	MyString descr;
	MyString link;

	for (int i = 1; i < strings.get_cur_objects(); i++)
	{
		if (compare(strings[i], "descr"))
		{
			i++;
			descr = strings[i];
		}
		else if (compare(strings[i], "src") || compare(strings[i], "href"))
		{
			i++;
			link = strings[i];
		}
		else
		{
			content = strings[i];
		}
	}

	if (type[0] == 'h' && !compare(type,"head") && !compare(type, "html"))
	{
		unsigned size = 0;
		if (type[1] >= '0' && type[1] <= '9')
		{
			size = type[1] - '0';
		}
		result = new HeaderTag(content, descr, size);
	}
	else if (compare(type, "p"))
	{
		result = new ParagraphTag(content, descr);
	}
	else if (compare(type, "img"))
	{
		result = new ImageTag(link, descr);
	}
	else if (compare(type, "iframe"))
	{
		result = new VideoTag(content, descr, link);
	}
	else if (compare(type, "href"))
	{
		result = new LinkTag(content, descr, link);
	}
	return result;
}

Tags * TagFactory::CreateTagKeyboard(const MyVector<MyString>& strings) const
{
	Tags* result = nullptr;
	MyString type;
	MyString descr;
	MyString link;
	MyString content;
	for (int i = 0; i < strings.get_cur_objects(); i++)
	{
		if (i == 0)
		{
			type = strings[i];
		}
		else if (i == 1)
		{
			descr = strings[i];
		}
		else if (i == 2)
		{
			link = strings[i];
		}
		else if (i == 3)
		{
			content = strings[i];
		}
	}

	if (is_header(type))
	{
		unsigned size = 0;
		if (type[6] >= '0' && type[6] <= '9')
		{
			size = type[6] - '0';
		}
		result = new HeaderTag(content, descr, size);
	}
	else if (compare(type, "text"))
	{
		result = new ParagraphTag(content, descr);
	}
	else if (compare(type, "image"))
	{
		result = new ImageTag(link, descr);
	}
	else if (compare(type, "video"))
	{
		result = new VideoTag(content, descr, link);
	}
	else if (compare(type, "link"))
	{
		result = new LinkTag(content, descr, link);
	}
	return result;
}

bool is_header(const MyString & type)
{
	return (type[0] == 'h' && type[1] == 'e' && type[2] == 'a' && type[3] == 'd' && type[4] == 'e' && type[5] == 'r');
}
