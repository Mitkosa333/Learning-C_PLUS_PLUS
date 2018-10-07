#include "Wallet.h"

unsigned GenerateID(const Wallet * wallets, const unsigned size)
{
	unsigned id = 100;
	if (size != 0)
	{
		id = wallets[size-1].id + 1;
	}

	return id;
}


Transaction AddWallet(Wallet *& wallets, unsigned & size)
{
	double fiatMoney = 0;
	char name[256] = { 0 };
	std::cin >> fiatMoney;
	std::cin >> name;
	
	if (ifNameExist(wallets, size, name))
	{
		std::cout << "Name already Exists, choose another one!" << std::endl;
		Transaction failed;
		failed.receiverId = 0;
		failed.senderId = 0;
		failed.fmiCoins = 0;
		failed.time = 0;
		return failed;
	}

	if ((wallets != nullptr) && (ifPowerOf2(size)))
	{
		DoubleWalletArray(wallets, size);
		size++;
	}
	else if (wallets == nullptr)
	{
		size++;
		wallets = new Wallet[size];
	}
	else
	{
		size++;
	}

	wallets[size - 1].fiatMoney = fiatMoney;
	wallets[size - 1].id = GenerateID(wallets, size - 1);
	strncpy(wallets[size - 1].owner, name, 256);
	std::cout << wallets[size - 1].owner << "'s ID is " << wallets[size - 1].id << std::endl;
	AddOneWalletToFile(wallets[size - 1]);

	Transaction trans;
	trans.time = SecondsPassed();
	trans.receiverId = wallets[size - 1].id;
	trans.senderId = programId;
	trans.fmiCoins = wallets[size - 1].fiatMoney / randGenNum;

	return trans;
}

void AddWalletToFile(const Wallet * wallet, const unsigned size)
{
	std::ofstream walletFile("wallets.dat", std::ios::binary | std::ios::trunc);
	if (!walletFile.good())
	{
		std::cerr << "Error writing on file (wallets.dat)" << std::endl;
		return;
	}

	for (int i = 0; i < size; i++)
	{
		walletFile.write((char*)(&wallet[i]), sizeof(Wallet));
	}

	walletFile.close();
}

void AddOneWalletToFile(const Wallet & wallet)
{
	std::ofstream walletFile("wallets.dat", std::ios::binary | std::ios::app);
	if (!walletFile.good())
	{
		std::cerr << "Error writing on file (wallets.dat)" << std::endl;
		return;
	}

	walletFile.write((char*)(&wallet), sizeof(Wallet));

	walletFile.close();
}

void LoadWallets(Wallet *& wallets, unsigned & size)
{
	std::ifstream walletFile;
	walletFile.open("wallets.dat", std::ios::binary);

	if (!walletFile.good())
	{
		return;
	}

	walletFile.seekg(0, std::ios::end);
	size = walletFile.tellg() / (sizeof(Wallet));
	walletFile.seekg(0, std::ios::beg);

	wallets = new Wallet[size];

	for (int i = 0; i < size; i++)
	{
		walletFile.read((char*)(&wallets[i]), sizeof(Wallet));
	}

	walletFile.close();
}

bool ifNameExist(Wallet * wallet, const unsigned size, const char * name)
{
	for (int i = 0; i < size; i++)
	{
		if (strcmp(wallet[i].owner, name) == 0)
		{
			return true;
		}
	}
	return false;
}

bool ifIdExist(const Wallet * wallets, const unsigned size, const unsigned newId)
{
	for (int i = 0; i < size; i++)
	{
		if (wallets[i].id == newId)
		{
			return true;
		}
	}
	return false;
}

void DoubleWalletArray(Wallet *& wallets, unsigned numOfWallets)
{
	Wallet* temp = new Wallet[numOfWallets];

	for (int i = 0; i < numOfWallets; i++)
	{
		temp[i] = wallets[i];
	}

	delete[] wallets;
	wallets = nullptr;

	unsigned tempNum = numOfWallets;
	numOfWallets = numOfWallets * 2;
	wallets = new Wallet[numOfWallets];

	for (int i = 0; i < tempNum; i++)
	{
		wallets[i] = temp[i];
	}

	delete[] temp;
}

void RemoveMoneyFromWallet(Wallet * wallets, const unsigned size, const unsigned walletId, const double money)
{
	for (int i = 0; i < size; i++)
	{
		if (wallets[i].id == walletId)
		{
			wallets[i].fiatMoney -= money;
			break;
		}
	}
}

void AddMoneyToWallet(Wallet * wallets, const unsigned size, const unsigned walletId, const double money)
{
	for (int i = 0; i < size; i++)
	{
		if (wallets[i].id == walletId)
		{
			wallets[i].fiatMoney += money;
			break;
		}
	}
}
