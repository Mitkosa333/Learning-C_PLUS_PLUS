#include "PostBase.h"

PostBase::PostBase()
{
	posts = nullptr;
	numOfPosts = 0;
	randomNumGenerator = 1;
}

PostBase::~PostBase()
{
	Clean();
}

Post* PostBase::getPost(const unsigned id) const
{
	for (unsigned i = 0; i < numOfPosts; i++)
	{
		if (id == posts[i]->getId())
		{
			return posts[i];
		}
	}
	return nullptr;
}

bool PostBase::CreatePost(const char* username)
{
	char command[256];
	std::cin >> command;
	
	if (strcmp(command, "[image]") == 0)
	{
		if (ifPowerOf2(numOfPosts))
		{
			DoubleMaxPost();
		}

		char path[_MAX_PATH];
		std::cin.get();
		std::cin.getline(path, _MAX_PATH);

		char text[MAX_TEXT];
		std::cin.getline(text, MAX_TEXT);

		posts[numOfPosts] = new Image(username, text, path, randomNumGenerator);
		std::cout << "Post number " << posts[numOfPosts]->getId() << " created!" << std::endl;
		randomNumGenerator++;
		numOfPosts++;
		return true;
	}
	else if (strcmp(command, "[url]") == 0)
	{
		if (ifPowerOf2(numOfPosts))
		{
			DoubleMaxPost();
		}

		char link[MAX_LINK];
		std::cin.get();
		std::cin.getline(link, MAX_TEXT);

		char text[MAX_TEXT];
		std::cin.getline(text, MAX_TEXT);

		posts[numOfPosts] = new Link(username, text, link, randomNumGenerator);
		std::cout << "Post number " << posts[numOfPosts]->getId() << " created!" << std::endl;
		randomNumGenerator++;
		numOfPosts++;
		return true;
	}
	else if (strcmp(command, "[text]") == 0)
	{
		if (ifPowerOf2(numOfPosts))
		{
			DoubleMaxPost();
		}

		char text[MAX_TEXT];
		std::cin.get();
		std::cin.getline(text, MAX_TEXT);

		posts[numOfPosts] = new Text(username, text, randomNumGenerator);
		std::cout << "Post number " << posts[numOfPosts]->getId() << " created!" << std::endl;
		randomNumGenerator++;
		numOfPosts++;
		return true;
	}
	else
	{
		std::cout << "Wrong command!" << std::endl;
		return false;
	}
}

bool PostBase::RemovePost(const unsigned id, char* owner)
{
	unsigned wantedPost = 0;
	bool found = false;
	while (wantedPost < numOfPosts)
	{
		if (id == posts[wantedPost]->getId())
		{
			found = true;
			break;
		}
		wantedPost++;
	}

	if (found == false)
	{
		std::cout << "No such post!" << std::endl;
		return false;
	}
	else
	{
		std::cout << "Removing post number " << posts[wantedPost]->getId() << " !" << std::endl;
		strncpy(owner, posts[wantedPost]->getCreator(),strlen(posts[wantedPost]->getCreator()));
		for (unsigned i = wantedPost; i + 1 < numOfPosts; i++)
		{
			posts[i] = posts[i + 1];
		}
		numOfPosts--;
		return true;
	}
}

void PostBase::ViewPost(const char* username)
{
	unsigned num = 0;
	std::cin >> num;
	Post* post = getPost(num);
	
	if (post == nullptr)
	{
		std::cout << "No such post!" << std::endl;
	}
	else
	{
		std::cout << "Creating HTML file for post number" << post->getId() << " !" << std::endl;
		post->WriteInHTML(username);
	}
}

void PostBase::ViewAllPosts(const char* applier, const char* owner)
{
	if (!isUserOwningAnyPosts(owner))
	{
		std::cout << "User doesn't own any posts!" << std::endl;
	}
	else
	{
		char filename[_MAX_PATH] = { 0 };

		CreateFileNameByName(applier, owner, filename);

		std::ofstream myFile(filename);
		myFile << "<html>" << std::endl;
		myFile << "<body>" << std::endl;
		myFile << "Posted by: " << owner << "</br>" << std::endl;

		for (unsigned i = 0; i < numOfPosts; i++)
		{
			if (strcmp(owner, posts[i]->getCreator()) == 0)
			{
				myFile << "</br>" << std::endl;
				myFile << "Post ID: " << posts[i]->getId() << "</br>" << std::endl;
				posts[i]->WriteHTMLSpecifics(myFile);
				myFile << " </br>" << std::endl;
			}
		}

		myFile << "</body>" << std::endl;
		myFile << "</html>" << std::endl;

		myFile.close();
		
		std::cout << "Created HTML file with all posts of user \"" << owner << "\" !" << std::endl;
	}
}

void PostBase::ChangeUsername(const char* oldUsername, const char* newUsername)
{
	for (unsigned i = 0; i < numOfPosts; i++)
	{
		if (strcmp(posts[i]->getCreator(), oldUsername))
		{
			posts[i]->changeCreatorName(newUsername);
		}
	}
}

bool PostBase::isUserOwningAnyPosts(const char* owner) const
{
	for (unsigned i = 0; i < numOfPosts; i++)
	{
		if (strcmp(owner, posts[i]->getCreator()) == 0)
		{
			return true;
		}
	}
	return false;
}

void PostBase::CreateFileNameByName(const char* applier, const char* creator, char* filename) const
{
	unsigned i = 0;
	for (unsigned j = 0; applier[j] != '\0'; j++)
	{
		filename[i] = applier[j];
		i++;
	}

	filename[i] = ' ';
	i++;

	for (unsigned j = 0; creator[j] != '\0'; j++)
	{
		filename[i] = creator[j];
		i++;
	}

	filename[i] = '.';
	i++;
	filename[i] = 'h';
	i++;
	filename[i] = 't';
	i++;
	filename[i] = 'm';
	i++;
	filename[i] = 'l';
	i++;
	filename[i] = '\0';
}


void PostBase::DoubleMaxPost()
{
	Post** buffer = nullptr;
	if (numOfPosts == 0)
	{
		buffer = new Post*[numOfPosts + 1];
	}
	else
	{
		buffer = new Post*[numOfPosts * 2];
		for (unsigned i = 0; i < numOfPosts; i++)
		{
			buffer[i] = posts[i];
		}
	}
	Clean();
	posts = buffer;
}

void PostBase::Clean()
{
	for (unsigned i = 0; i < numOfPosts; i++)
	{
		delete[] posts[i];
	}
	delete[] posts;
}
