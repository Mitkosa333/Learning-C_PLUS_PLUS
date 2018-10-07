
#include <iostream>
#include "HTMLManager.h"

int main()
{
	HTMLManager* instance = &HTMLManager::getInstance();
	instance->Menu();
	return 0;
}
