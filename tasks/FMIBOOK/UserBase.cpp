#include "UserBase.h"

UserBase::UserBase()
	: users(nullptr), moderators(nullptr)
{
	numOfCurUsers = 0;
	numOfCurModerators = 0;
}

UserBase::UserBase(const UserBase & obj)
{
	User* tempUsers = nullptr;
	Moderator* tempMods = nullptr;

	if (obj.users != nullptr)
	{
		tempUsers = new User[obj.numOfCurUsers];
		for (unsigned i = 0; i < obj.numOfCurUsers; i++)
		{
			tempUsers[i] = obj.users[i];
		}

	}
	if (obj.moderators != nullptr)
	{
		tempMods = new Moderator[obj.numOfCurModerators];
		for (unsigned i = 0; i < obj.numOfCurModerators; i++)
		{
			tempMods[i] = obj.moderators[i];
		}
	}

	users = tempUsers;
	moderators = tempMods;
	Admin temp("admin", 21);
	admin = temp;
	numOfCurUsers = obj.numOfCurUsers;
	numOfCurModerators = obj.numOfCurModerators;
}

UserBase & UserBase::operator=(const UserBase & obj)
{
	if (this != &obj)
	{
		User* tempUsers = nullptr;
		Moderator* tempMods = nullptr;

		if (obj.users != nullptr)
		{
			tempUsers = new User[obj.numOfCurUsers];
			for (unsigned i = 0; i < obj.numOfCurUsers; i++)
			{
				tempUsers[i] = obj.users[i];
			}

		}
		if (obj.moderators != nullptr)
		{
			tempMods = new Moderator[obj.numOfCurModerators];
			for (unsigned i = 0; i < obj.numOfCurModerators; i++)
			{
				tempMods[i] = obj.moderators[i];
			}
		}

		Clean();

		users = tempUsers;
		moderators = tempMods;
		Admin temp("admin", 21);
		admin = temp;
		numOfCurUsers = obj.numOfCurUsers;
		numOfCurModerators = obj.numOfCurModerators;
	}
	return *this;
}

UserBase::~UserBase()
{
	Clean();
}

bool UserBase::UserManagement(const char* username, const char* secondCommand)
{
	if (strcmp(username, admin.getName()) == 0)
	{
		if ((strcmp(secondCommand, "block") == 0))
		{
			BlockUser(admin);
			return true;
		}
		else if ((strcmp(secondCommand, "unblock") == 0))
		{
			UnblockUser(admin);
			return true;
		}
		else if ((strcmp(secondCommand, "add_user") == 0))
		{
			AddUser(admin);
			return true;
		}
		else if ((strcmp(secondCommand, "add_moderator") == 0))
		{
			AddModerator(admin);
			return true;
		}
		else if ((strcmp(secondCommand, "remove_user") == 0))
		{
			RemoveUser(admin);
			return true;
		}
		else if ((strcmp(secondCommand, "remove_moderator") == 0))
		{
			RemoveModerator(admin);
			return true;
		}
		else
		{
			return false;
		}
	}

	for (unsigned i = 0; i < numOfCurModerators; i++)
	{
		if (strcmp(username, moderators[i].getName()) == 0)
		{
			if ((strcmp(secondCommand, "block") == 0))
			{
				BlockUser(moderators[i]);
				return true;
			}
			else if (strcmp(secondCommand, "unblock") == 0)
			{
				UnblockUser(moderators[i]);
				return true;
			}
		}
	}
	return false;
}

void UserBase::BlockUser(const Moderator& obj)
{
	char secondUser[256];
	std::cin >> secondUser;
	User* user2 = ChooseUser(secondUser);
	if (user2 == nullptr)
	{
		std::cout << "No such user!" << std::endl;
	}
	else
	{
		std::cout << "Blocking User " << *user2->getName() << " !" << std::endl;
		obj.Block(*user2);
	}
}

void UserBase::UnblockUser(const Moderator & obj)
{
	char secondUser[256];
	std::cin >> secondUser;
	User* user2 = ChooseUser(secondUser);
	
	if (user2 == nullptr)
	{
		std::cout << "No such user!" << std::endl;
	}
	else
	{
		std::cout << "Unblocking User " << *user2->getName() << " !" << std::endl;
		obj.Unblock(*user2);
	}
}

void UserBase::AddUser(const Admin& obj)
{
	char nickname[256];
	short age;
	std::cin >> nickname >> age;

	if ((strcmp(nickname, "") == 0) || (age == 0))
	{
		std::cout << "Wrong Parameters!" << std::endl;
		return;
	}

	if (!isUsernameFree(nickname))
	{
		std::cout << "Username already taken!" << std::endl;
		return;
	}

	if (ifPowerOf2(numOfCurUsers))
	{
		DoubleMaxUsers();
	}

	obj.AddUser(users, numOfCurUsers, nickname, age);
	numOfCurUsers++;
	std::cout << "Added User \"" << nickname << "\" !" << std::endl;
}

void UserBase::AddModerator(const Admin& obj)
{
	char nickname[256];
	short age;
	std::cin >> nickname >> age;

	if ((strcmp(nickname, "") == 0) || (age == 0))
	{
		std::cout << "Wrong Parameters!" << std::endl;
		return;
	}

	if (!isUsernameFree(nickname))
	{
		std::cout << "Username already taken!" << std::endl;
		return;
	}

	if (ifPowerOf2(numOfCurModerators))
	{
		DoubleMaxMods();
	}

	obj.AddModerator(moderators, numOfCurModerators, nickname, age);
	numOfCurModerators++;
	std::cout << "Added Moderator \"" << nickname << "\" !" << std::endl;
}

bool UserBase::RemoveUser(const Admin& obj)
{
	char nickname[256];
	std::cin >> nickname;
	if (obj.RemoveUser(users, numOfCurUsers, nickname))
	{
		std::cout << "Removed User \"" << nickname << "\" !" << std::endl;
		return true;
	}
	else
	{
		return false;
	}
}

bool UserBase::RemoveModerator(const Admin& obj)
{
	char nickname[256];
	std::cin >> nickname;
	if (obj.RemoveUser(moderators, numOfCurModerators, nickname))
	{
		std::cout << "Removed Moderator \"" << nickname << "\" !" << std::endl;
		return true;
	}
	else
	{
		return false;
	}
}

void UserBase::Clean()
{
	delete[] users;
	users = nullptr;
	delete[] moderators;
	moderators = nullptr;
}

bool UserBase::isUsernameFree(const char* newUsername)
{
	User* check = ChooseUser(newUsername);
	if (check == nullptr)
	{
		return true;
	}
	return false;
}

User* UserBase::ChooseUser(const char* username)
{
	for (unsigned i = 0; i < numOfCurUsers; i++)
	{
		if (strcmp(username, users[i].getName()) == 0)
		{
			return &users[i];
		}
	}

	if (strcmp(username, admin.getName()) == 0)
	{
		return &admin;
	}

	for (unsigned i = 0; i < numOfCurModerators; i++)
	{
		if (strcmp(username, moderators[i].getName()) == 0)
		{
			return &moderators[i];
		}
	}
	return nullptr;
}

Moderator* UserBase::ChooseModerator(const char* username)
{
	if (strcmp(username, admin.getName()) == 0)
	{
		return &admin;
	}

	for (unsigned i = 0; i < numOfCurModerators; i++)
	{
		if (strcmp(username, moderators[i].getName()) == 0)
		{
			return &moderators[i];
		}
	}

	return nullptr;
}

User* UserBase::YoungestUser()
{
	User* youngestUser = nullptr;
	short check = 256;
	for (unsigned i = 0; i < numOfCurUsers; i++)
	{
		if (check > users[i].getAge())
		{
			check = users[i].getAge();
			youngestUser = &users[i];
		}
	}

	if (check > admin.getAge())
	{
		check = admin.getAge();
		youngestUser = &admin;
	}

	for (unsigned i = 0; i < numOfCurModerators; i++)
	{
		if (check > moderators[i].getAge())
		{
			check = moderators[i].getAge();
			youngestUser = &moderators[i];
		}
	}
	return youngestUser;
}

User* UserBase::OldestUser()
{
	User* oldestUser = nullptr;
	short check = 0;
	for (unsigned i = 0; i < numOfCurUsers; i++)
	{
		if (check < users[i].getAge())
		{
			check = users[i].getAge();
			oldestUser = &users[i];
		}
	}

	if (check < admin.getAge())
	{
		check = admin.getAge();
		oldestUser = &admin;
	}

	for (unsigned i = 0; i < numOfCurModerators; i++)
	{
		if (check < moderators[i].getAge())
		{
			check = moderators[i].getAge();
			oldestUser = &moderators[i];
		}
	}
	return oldestUser;
}

User* UserBase::UserWithMostPosts()
{
	User* mostActiveUser = nullptr;
	short check = 0;
	for (unsigned i = 0; i < numOfCurUsers; i++)
	{
		if (check < users[i].getNumOfPosts())
		{
			check = users[i].getNumOfPosts();
			mostActiveUser = &users[i];
		}
	}

	if (check < admin.getNumOfPosts())
	{
		check = admin.getNumOfPosts();
		mostActiveUser = &admin;
	}

	for (unsigned i = 0; i < numOfCurModerators; i++)
	{
		if (check < moderators[i].getNumOfPosts())
		{
			check = moderators[i].getNumOfPosts();
			mostActiveUser = &moderators[i];
		}
	}
	return mostActiveUser;
}

void UserBase::printBlockedUsers() const
{
	std::cout << "Blocked Users:" << std::endl;
	unsigned counter = 0;
	for (unsigned i = 0; i < numOfCurUsers; i++)
	{
		if (users[i].getBlockedStatus() == true)
		{
			counter++;
			std::cout << "-" << users[i].getName() << std::endl;
		}
	}

	if (admin.getBlockedStatus() == true)
	{
		counter++;
		std::cout << "-" << admin.getName() << std::endl;
	}

	for (unsigned i = 0; i < numOfCurModerators; i++)
	{
		if (moderators[i].getBlockedStatus() == true)
		{
			counter++;
			std::cout << "-" << moderators[i].getName() << std::endl;
		}
	}
	std::cout << "Total blocked users: " << counter << std::endl;
}

void UserBase::DoubleMaxUsers()
{
	User* temp = nullptr;
	if (numOfCurUsers == 0)
	{
		temp = new User[numOfCurUsers + 1];
	}
	else
	{
		temp = new User[numOfCurUsers * 2];
		for (unsigned i = 0; i < numOfCurUsers; i++)
		{	
			temp[i] = users[i];
		}
	}
	delete[] users;
	users = temp;
}

void UserBase::DoubleMaxMods()
{
	Moderator* temp = nullptr;
	if (numOfCurModerators == 0)
	{
		temp = new Moderator[numOfCurModerators + 1];
	}
	else
	{
		temp = new Moderator[numOfCurModerators * 2];
		for (unsigned i = 0; i < numOfCurModerators; i++)
		{
			temp[i] = moderators[i];
		}
	}
	delete[] moderators;
	moderators = temp;
}
