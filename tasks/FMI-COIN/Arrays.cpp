#include "Arrays.h"

void Constructor(Arrays & data)
{
	data.wallets = nullptr;
	data.sizeWallets = 0;
	data.transactions = nullptr;
	data.sizeTransactions = 0;
	data.orders = nullptr;
	data.sizeOrders = 0;
}

void LoadFiles(Arrays& data)
{
	LoadWallets(data.wallets, data.sizeWallets);
	LoadTransaction(data.transactions, data.sizeTransactions);
	LoadOrder(data.orders, data.sizeOrders);
}

void AddToFile(Arrays & data)
{
	AddWalletToFile(data.wallets, data.sizeWallets);
	AddTransactionToFile(data.transactions, data.sizeTransactions);
	AddOrderToFile(data.orders, data.sizeOrders);
}

void AddNewUser(Transaction *& trans, unsigned & sizeTrans, Wallet *& wallets, unsigned & sizeWallets)
{
	Transaction check = AddWallet(wallets, sizeWallets);
	if (check.time == 0)
	{
		return;
	}

	if (sizeTrans == 0)
	{
		sizeTrans++;
		trans = new Transaction[sizeTrans];
	}
	else if (ifPowerOf2(sizeTrans))
	{
		DoubleTransactionArray(trans, sizeTrans);
		sizeTrans++;
	}
	else
	{
		sizeTrans++;
	}

	trans[sizeTrans - 1] = check;
	AddOneTransactionToFile(trans[sizeTrans - 1]);
}

bool EnoughCoins(const Transaction * trans, const unsigned size, const unsigned id, const double fmiCoins)
{
	double senderCoins = 0;
	double receiverCoins = 0;

	for (int i = 0; i < size; i++)
	{
		if (trans[i].receiverId == id)
		{
			receiverCoins += trans[i].fmiCoins;
		}
		if (trans[i].senderId == id)
		{
			senderCoins += trans[i].fmiCoins;
		}
	}

	if ((receiverCoins - senderCoins) >= fmiCoins)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool EnoughMoney(const Wallet * wallets, const unsigned size, const unsigned id, const double Money)
{
	int i = 0;
	while (i < size)
	{
		if (wallets[i].id == id)
		{
			break;
		}
		i++;
	}
	if (wallets[i].fiatMoney >= (Money*randGenNum))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void WalletInfo(const Arrays & data)
{
	unsigned walletId = 0;
	std::cin >> walletId;

	if (!ifIdExist(data.wallets, data.sizeWallets, walletId))
	{
		std::cout << "User Does Not Exist!"<<std::endl;
		return;
	}

	int i = 0;
	while (i < data.sizeWallets)
	{
		if (walletId == data.wallets[i].id)
		{
			break;
		}
		i++;
	}

	std::cout << data.wallets[i].owner << " has:" << std::endl;
	std::cout << "Money: " << data.wallets[i].fiatMoney << std::endl;
	
	double senderCoins = 0;
	double receiverCoins = 0;

	for (int j = 0; j < data.sizeTransactions; j++)
	{
		if (data.transactions[j].receiverId == data.wallets[i].id)
		{
			receiverCoins += data.transactions[j].fmiCoins;
		}
		if (data.transactions[j].senderId == data.wallets[i].id)
		{
			senderCoins += data.transactions[j].fmiCoins;
		}
	}
	
	std::cout << "Coins: " << receiverCoins - senderCoins << std::endl;

}

void AttractInvestors(Arrays & data)
{
	std::cout << "Top users:";
	const int top10Size = 10;
	unsigned top10IDs[top10Size];
	FindTop10IDs(data, top10IDs, top10Size);
	for (int i = 0; (i < data.sizeWallets) || (i < top10Size); i++)
	{
		for (int j = 0; j < data.sizeWallets; j++)
		{
			if (top10IDs[i] == data.wallets[j].id)
			{
				std::cout << std::endl;
				std::cout << i+1 << ". ";
				std::cout << data.wallets[j].owner << " with id " << data.wallets[j].id << " has info:" << std::endl;
				std::cout << "Coins: " << CountCoins(data.transactions, data.sizeTransactions, data.wallets[j].id) << std::endl;
				std::cout << "Number of Transactions: " << NumberOfTrans(data.transactions, data.sizeTransactions, data.wallets[j].id) << std::endl;;
				std::cout << "Time of First Transaction: " << FirstTrans(data.transactions, data.sizeTransactions, data.wallets[j].id) << std::endl;
				std::cout << "Time of Last Transaction: " << LastTrans(data.transactions, data.sizeTransactions, data.wallets[j].id) << std::endl;
				break;
			}
		}
	}
}

void FindTop10IDs(Arrays & data, unsigned* top10IDs, const int size)
{
	unsigned* IDs = new unsigned[data.sizeWallets];
	for (int i = 0; i < data.sizeWallets; i++)
	{
		IDs[i] = data.wallets[i].id;
	}

	int max = 0;
	for (int i = 0; i < data.sizeWallets - 1; i++)
	{
		max = i;
		for (int j = i + 1; j < data.sizeWallets; j++)
		{
			if (CountCoins(data.transactions, data.sizeTransactions, IDs[j]) > CountCoins(data.transactions, data.sizeTransactions, IDs[max]))
			{
				max = j;
			}
		}
		std::swap(IDs[max], IDs[i]);
	}

	for (int i = 0; (i < data.sizeWallets) && (i < size); i++)
	{
		top10IDs[i] = IDs[i];
	}

	delete[] IDs;
}

void ProcessOrder(Arrays & data)
{	
	char bufferType[256] = { 0 };
	double fmiCoins = 0;
 	unsigned walletId = 0;
	std::cin >> bufferType >> fmiCoins >> walletId;

	if (!((stricmp(bufferType, "sell") == 0) || (stricmp(bufferType, "buy") == 0)))
	{
		std::cout << "Wrong command type!" << std::endl;
		return;
	}

	if (!ifIdExist(data.wallets, data.sizeWallets, walletId))
	{
		std::cout << "User doesn't exist!" << std::endl;
		return;
	}


	if ((stricmp(bufferType, "sell") == 0) && !EnoughCoins(data.transactions, data.sizeTransactions, walletId, fmiCoins))
	{
		std::cout << "Not enough coins!" << std::endl;
		return;
	}

	if ((stricmp(bufferType, "buy") == 0) && !EnoughMoney(data.wallets, data.sizeWallets, walletId, fmiCoins))
	{
		std::cout << "Not enough real money!" << std::endl;
		return;
	}

	AddNewOrder(data.orders, data.sizeOrders, bufferType, walletId, fmiCoins);

	if (stricmp(bufferType, "buy") == 0)
	{
		ForwardBuyOrder(data);
	}
	else if (stricmp(bufferType, "sell") == 0)
	{
		ForwardSellOrder(data);
	}
}

void ForwardBuyOrder(Arrays & data)
{
	if (ExistingSellOrders(data.orders, data.sizeOrders))
	{
		char name[64] = { 0 };
		ParseIdAndCurTimeIntoChar(name, data.orders[data.sizeOrders - 1].walletId);

		std::ofstream textFile(name);
		int counter = 0;
		double money = 0;
		for (int i = 0; i < (data.sizeOrders - 1); i++)
		{
			if ((data.orders[i].type == Order::SELL) && (data.orders[i].fmiCoins != 0))
			{
				if (data.orders[i].fmiCoins < data.orders[data.sizeOrders - 1].fmiCoins)
				{
					Transaction newTrans;
					newTrans.fmiCoins = data.orders[i].fmiCoins;
					newTrans.receiverId = data.orders[data.sizeOrders - 1].walletId;
					newTrans.senderId = data.orders[i].walletId;
					newTrans.time = SecondsPassed();

					textFile << "Receiver: " << newTrans.receiverId << " Sender: " << newTrans.senderId << " Coins: " << newTrans.fmiCoins << std::endl;
					AddTransaction(data.transactions, data.sizeTransactions, newTrans);

					AddMoneyToWallet(data.wallets, data.sizeWallets, data.orders[i].walletId, data.orders[i].fmiCoins*randGenNum);
					RemoveMoneyFromWallet(data.wallets, data.sizeWallets, data.orders[data.sizeOrders - 1].walletId, data.orders[i].fmiCoins*randGenNum);

					data.orders[data.sizeOrders - 1].fmiCoins -= data.orders[i].fmiCoins;
					data.orders[i].fmiCoins = 0;

					money += newTrans.fmiCoins;
					counter++;
				}
				else
				{
					Transaction newTrans;
					newTrans.fmiCoins = data.orders[data.sizeOrders - 1].fmiCoins;
					newTrans.receiverId = data.orders[data.sizeOrders - 1].walletId;
					newTrans.senderId = data.orders[i].walletId;
					newTrans.time = SecondsPassed();

					textFile << "Receiver: " << newTrans.receiverId << " Sender: " << newTrans.senderId << " Coins: " << newTrans.fmiCoins << std::endl;
					AddTransaction(data.transactions, data.sizeTransactions, newTrans);

					AddMoneyToWallet(data.wallets, data.sizeWallets, data.orders[i].walletId, data.orders[data.sizeOrders - 1].fmiCoins*randGenNum);
					RemoveMoneyFromWallet(data.wallets, data.sizeWallets, data.orders[data.sizeOrders - 1].walletId, data.orders[data.sizeOrders - 1].fmiCoins*randGenNum);

					data.orders[i].fmiCoins -= data.orders[data.sizeOrders - 1].fmiCoins;
					data.orders[data.sizeOrders - 1].fmiCoins = 0;

					money += newTrans.fmiCoins;
					counter++;

					textFile << std::endl;
					textFile << "Num of Transactions: " << counter << "      Real Word Worth Send: " << money * randGenNum;

					textFile.close();
					
					return;
				}
			}
		}
		textFile.close();
	}
}

void ForwardSellOrder(Arrays & data)
{
	if (ExistingBuyOrders(data.orders, data.sizeOrders))
	{
		char name[64] = { 0 };
		ParseIdAndCurTimeIntoChar(name, data.orders[data.sizeOrders - 1].walletId);

		std::ofstream textFile(name);
		int counter = 0;
		double money = 0;
		for (int i = 0; i < (data.sizeOrders - 1); i++)
		{
			if ((data.orders[i].type == Order::BUY) && (data.orders[i].fmiCoins != 0))
			{
				if (data.orders[i].fmiCoins < data.orders[data.sizeOrders - 1].fmiCoins)
				{
					Transaction newTrans;
					newTrans.fmiCoins = data.orders[i].fmiCoins;
					newTrans.receiverId = data.orders[i].walletId;
					newTrans.senderId = data.orders[data.sizeOrders - 1].walletId;
					newTrans.time = SecondsPassed();

					textFile << "Receiver: " << newTrans.receiverId << " Sender: " << newTrans.senderId << " Coins: " << newTrans.fmiCoins << std::endl;
					AddTransaction(data.transactions, data.sizeTransactions, newTrans);

					AddMoneyToWallet(data.wallets, data.sizeWallets, data.orders[data.sizeOrders - 1].walletId, data.orders[i].fmiCoins*randGenNum);
					RemoveMoneyFromWallet(data.wallets, data.sizeWallets, data.orders[i].walletId, data.orders[i].fmiCoins*randGenNum);

					data.orders[data.sizeOrders - 1].fmiCoins -= data.orders[i].fmiCoins;
					data.orders[i].fmiCoins -= data.orders[i].fmiCoins;

					money += newTrans.fmiCoins;
					counter++;
				}
				else
				{
					Transaction newTrans;
					newTrans.fmiCoins = data.orders[data.sizeOrders - 1].fmiCoins;
					newTrans.receiverId = data.orders[i].walletId;
					newTrans.senderId = data.orders[data.sizeOrders - 1].walletId;
					newTrans.time = SecondsPassed();

					textFile << "Receiver: " << newTrans.receiverId << " Sender: " << newTrans.senderId << " Coins: " << newTrans.fmiCoins << std::endl;
					AddTransaction(data.transactions, data.sizeTransactions, newTrans);

					AddMoneyToWallet(data.wallets, data.sizeWallets, data.orders[data.sizeOrders - 1].walletId, data.orders[data.sizeOrders - 1].fmiCoins*randGenNum);
					RemoveMoneyFromWallet(data.wallets, data.sizeWallets, data.orders[i].walletId, data.orders[data.sizeOrders - 1].fmiCoins*randGenNum);

					data.orders[i].fmiCoins -= data.orders[data.sizeOrders - 1].fmiCoins;
					data.orders[data.sizeOrders - 1].fmiCoins = data.orders[data.sizeOrders - 1].fmiCoins;

					money += newTrans.fmiCoins;
					counter++;

					textFile << std::endl;
					textFile << "Num of Transactions: " << counter << "      Real World Worth Send: " << money * randGenNum;

					textFile.close();
					return;
				}
			}
		}
		textFile.close();
	}
}

void Destructor(Arrays & data)
{
	delete[] data.wallets;
	data.wallets = nullptr;
	data.sizeWallets = 0;
	delete[] data.transactions;
	data.transactions = nullptr;
	data.sizeTransactions = 0;
	delete[] data.orders;
	data.orders = nullptr;
	data.sizeOrders = 0;
}
