#include "User.h"

User::User()
{
	nickname = nullptr;
	setNewUser("", 0);
}

User::User(const char * nickname, const short age) : nickname(nullptr)
{
	setNewUser(nickname, age); 
}

User::User(const User & obj)
{
	setNewUser(obj.nickname, obj.age); 
}

User & User::operator=(const User & obj)
{
	if (this != &obj)
	{
		Clear();
		setOldUser(obj.nickname, obj.age, obj.is_blocked, obj.numOfOwnedPosts); 
	}
	return *this;
}

void User::ChangeNickname(const char* nickname)
{
	std::cout << "Changed nickname from \"" << this->nickname << "\" to \"" << nickname << "\" !" << std::endl;
	setName(nickname);
}

void User::setBlockStatus(const bool block)
{
	this->is_blocked = block;
}

bool User::RemovePost(PostBase & obj, char* owner)
{
	unsigned id = 0;
	std::cin >> id;
	Post* post = obj.getPost(id);
	if (post == nullptr)
	{
		std::cout << "No such post" << std::endl;
		return false;
	}
	else if (strcmp(nickname, post->getCreator()) == 0)
	{
		return obj.RemovePost(id, owner);
	}
	else
	{
		std::cout << "That post doesn't belong to the user to be removed" << std::endl;
		return false;
	}
}

void User::AddToPostNumber()
{
	numOfOwnedPosts++;
}

void User::RemoveFromPostNumber()
{
	numOfOwnedPosts--;
}

User::~User()
{
	Clear();
}

void User::setName(const char* nickname)
{
	char* buffer = new char[strlen(nickname) + 1];
	delete[] this->nickname;
	nickname = buffer;

}

void User::Clear()
{
	delete[] this->nickname;
	this->nickname = nullptr;
}

void User::setNewUser(const char * nickname, const short age)
{
	char* buffer = new char[strlen(nickname) + 1];
	strncpy(buffer, nickname, strlen(nickname) + 1);
	this->nickname = buffer;
	this->age = age;
	this->is_blocked = false;
	this->numOfOwnedPosts = 0;
}

void User::setOldUser(const char * nickname, const short age, const bool is_blocked, const unsigned posts)
{
	char* nickBuffer = new char[strlen(nickname) + 1];
	strncpy(nickBuffer, nickname, strlen(nickname) + 1);

	this->nickname = nickBuffer;
	this->age = age;
	this->is_blocked = is_blocked;
	this->numOfOwnedPosts = posts;
}
