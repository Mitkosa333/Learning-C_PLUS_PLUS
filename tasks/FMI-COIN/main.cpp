#include <iostream>

#include "Arrays.h"

const int MAX_COMMAND = 256;

void Program(Arrays&);

int main()
{
	Arrays data;
	Constructor(data);

	LoadFiles(data);

	Program(data);

	Destructor(data);
}

void Program(Arrays& data)
{
	char command[MAX_COMMAND];

	for (;;)
	{
		std::cout << "Enter Command: ";
		std::cin >> command;

		if (stricmp(command, "add-wallet") == 0)
		{
			AddNewUser(data.transactions, data.sizeTransactions, data.wallets, data.sizeWallets);
		}
		else if (stricmp(command, "make-order") == 0)
		{
			ProcessOrder(data);
		}
		else if (stricmp(command, "wallet-info") == 0)
		{
			WalletInfo(data);
		}
		else if (stricmp(command, "attract-investors") == 0)
		{
			AttractInvestors(data);
		}
		else if (stricmp(command, "quit") == 0)
		{
			AddToFile(data);
			break;
		}
		else
		{
			std::cout << "WRONG COMMAND!" << std::endl;
		}
	}
}