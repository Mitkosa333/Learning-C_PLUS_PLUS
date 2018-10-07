#include "Moderator.h"

Moderator::Moderator() 
	: User()
{
}

Moderator::Moderator(const char* username, const short age)
	: User(username, age)
{
}

Moderator & Moderator::operator=(const Moderator & obj)
{
	if (this != &obj)
	{
		User::operator=(obj);
	}
	return *this;
}

void Moderator::Block(User& obj) const
{
	obj.setBlockStatus(true);
}

void Moderator::Unblock(User& obj) const
{
	obj.setBlockStatus(false);
}

bool Moderator::RemovePost(PostBase & obj, char* owner)
{
	unsigned id = 0;
	std::cin >> id;
	Post* post = obj.getPost(id);
	if (post == nullptr)
	{
		std::cout << "No such post!" << std::endl;
		return false;
	}
	else
	{
		return obj.RemovePost(id, owner);
	}
}
