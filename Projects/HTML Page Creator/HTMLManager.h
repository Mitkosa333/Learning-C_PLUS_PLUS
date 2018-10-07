#ifndef HTMLMANAGER_H
#define HTMLMANAGER_H
#include "TagFactory.h"
#include "MyVector.hpp"

class HTMLManager
{
public:
	static HTMLManager& getInstance();

	void Menu();

	~HTMLManager();

private:
	HTMLManager() {} 
	HTMLManager(const HTMLManager&) {}
	void operator= (const HTMLManager&) {}

private:
	void Add();
	void Remove();
	void Print() const;
	void MoveTo();
	void Load();
	void Save() const;

private:
	void BegOfFile(std::ofstream&) const;
	void AddTagsToFile(std::ofstream&) const;
	void EndOfFile(std::ofstream&) const;
	void clean();

private:
	MyVector<Tags*> HTMLdata;

};

#endif //HTMLMANAGER_H

