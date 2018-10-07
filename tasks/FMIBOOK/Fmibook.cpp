#include "Fmibook.h"

Fmibook & Fmibook::getInstance()
{
	static Fmibook instance;
	return instance;
}

void Fmibook::ChoosingCommand()
{
	char command[256]; 
	char command2[256];
	while (1)
	{
		std::cout << "Enter command:" << std::endl;
		std::cout << ">";
		std::cin >> command;
		
		if (strcmp(command, "quit") == 0)
		{
			return;
		}
		
 		if (strcmp(command, "info") == 0)
		{
			Info();
		}
		else
		{
			std::cin >> command2;

			if (strcmp(command2, "post") == 0)
			{
				CreatePost(command);
			}
			else if (strcmp(command2, "remove_post") == 0)
			{
				RemovePost(command);
			}
			else if (strcmp(command2, "view_post") == 0)
			{
				ViewPost(command);
			}
			else if (strcmp(command2, "view_all_posts") == 0)
			{
				ViewAllPosts(command);
			}
			else if (strcmp(command2, "rename") == 0)
			{
				ChangeNickname(command);
			}
			else if (allUsers.UserManagement(command, command2))
			{
				;
			}
			else
			{
				std::cout << "Wrong command!" << std::endl;
			}
		}
	}
}

void Fmibook::Info()
{
	std::cout << std::endl;
	std::cout << "Current Number of Users: " << allUsers.getNumUsers() << std::endl;
	std::cout << "Current Number of Moderators: " << allUsers.getNumMods() << std::endl;
	
	std::cout << std::endl;
	allUsers.printBlockedUsers();
	
	std::cout << std::endl;
	User* user = nullptr;
	user = allUsers.YoungestUser();
	std::cout << "Youngest User: " << user->getName() << " (age " << user->getAge() << " )" << std::endl;
	user = allUsers.OldestUser();
	std::cout << "Oldest User: " << user->getName() << " (age " << user->getAge() << " )" << std::endl;
	
	std::cout << std::endl;
	user = allUsers.UserWithMostPosts();
	if (user == nullptr)
	{
		std::cout << "No posts in the system yet!" << std::endl;
	}
	else
	{
		std::cout << "The most active user is: " << user->getName() << std::endl;
		std::cout << "With: " << user->getNumOfPosts() << " posts!" << std::endl;
	}
}

void Fmibook::CreatePost(const char* username)
{
	User* user = allUsers.ChooseUser(username);
	if (user == nullptr)
	{
		std::cout << "No such user!" << std::endl;
	}
	else if (user->getBlockedStatus() == true)
	{
		std::cout << user->getName() << " is blocked! " << std::endl;
	}
	else
	{ 
		if (allPosts.CreatePost(user->getName()))
		{
			user->AddToPostNumber();
		}
	}
}

void Fmibook::RemovePost(const char * username)
{
	Moderator* mod;
	User* user;
	mod = allUsers.ChooseModerator(username);
	if (mod == nullptr)
	{
		user = allUsers.ChooseUser(username);
		if (user == nullptr)
		{
			std::cout << "No such user!" << std::endl;
			return;
		}
		char owner[256] = { 0 };
		if (user->RemovePost(allPosts, owner))
		{
			allUsers.ChooseUser(owner)->RemoveFromPostNumber();
		}
	}
	else
	{
		char owner[256] = { 0 };
		if (mod->RemovePost(allPosts, owner))
		{
			allUsers.ChooseUser(owner)->RemoveFromPostNumber();
		}
	}
}

void Fmibook::ViewPost(const char* username) 
{
	User* user = allUsers.ChooseUser(username);
	if (user == nullptr)
	{
		std::cout << "No such user!";
		return;
	}

	allPosts.ViewPost(user->getName());
}

void Fmibook::ViewAllPosts(const char* username)
{
	User* user1 = allUsers.ChooseUser(username);
	if (user1 == nullptr)
	{
		std::cout << "No such user!";
		return;
	}

	char name[256] = { 0 };
	std::cin >> name;
	
	User* user2 = allUsers.ChooseUser(name);
	if (user2 == nullptr)
	{
		std::cout << "No such owner!";
		return;
	}

	allPosts.ViewAllPosts(user1->getName(), user2->getName());
}

void Fmibook::ChangeNickname(const char * username)
{
	User* user = allUsers.ChooseUser(username);
	if (user == nullptr)
	{
		std::cout << "No such user!" << std::endl;
		return;
	}

	char newUsername[256] = { 0 };
	std::cin >> newUsername;
	if (!allUsers.isUsernameFree(newUsername))
	{
		std::cout << "Username is taken!" << std::endl;
		return;
	}
	
	allPosts.ChangeUsername(username, newUsername);
	user->ChangeNickname(newUsername);

}

Fmibook::Fmibook()
{
	
}

Fmibook::~Fmibook()
{

}
