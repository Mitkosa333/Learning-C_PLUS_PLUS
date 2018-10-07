#include "Transaction.h"

void DoubleTransactionArray(Transaction *& trans, unsigned size)
{
	Transaction* temp = new Transaction[size];

	for (int i = 0; i < size; i++)
	{
		temp[i] = trans[i];
	}

	delete[] trans;
	trans = nullptr;

	unsigned tempNum = size;
	size = size * 2;
	trans = new Transaction[size];

	for (int i = 0; i < tempNum; i++)
	{
		trans[i] = temp[i];
	}

	delete[] temp;
}

void AddTransaction(Transaction *& transactions, unsigned & size, Transaction& newTrans)
{
	if ((transactions != nullptr) && (ifPowerOf2(size)))
	{
		DoubleTransactionArray(transactions, size);
		size++;
	}
	else if (transactions == nullptr)
	{
		size++;
		transactions = new Transaction[size];
	}
	else
	{
		size++;
	}

	transactions[size - 1] = newTrans;
	AddOneTransactionToFile(transactions[size-1]);

}

void AddTransactionToFile(const Transaction * trans, const unsigned size)
{
	std::ofstream transFile("transactions.dat", std::ios::binary | std::ios::trunc);
	if (!transFile.good())
	{
		std::cerr << "Error writing on file (transactions.dat)" << std::endl;
		return;
	}

	for (int i = 0; i < size; i++)
	{
		transFile.write((char*)(&trans[i]), sizeof(Transaction));
	}


	transFile.close();
}

void AddOneTransactionToFile(const Transaction & trans)
{
	std::ofstream transFile("transactions.dat", std::ios::binary | std::ios::app);
	if (!transFile.good())
	{
		std::cerr << "Error writing on file (transactions.dat)" << std::endl;
		return;
	}

	transFile.write((char*)(&trans), sizeof(Transaction));

	transFile.close();
}

void LoadTransaction(Transaction *& trans, unsigned& size)
{
	std::ifstream transFile;
	transFile.open("transactions.dat", std::ios::binary);

	if (!transFile.good())
	{
		return;
	}

	transFile.seekg(0, std::ios::end);
	size = transFile.tellg() / (sizeof(Transaction));
	transFile.seekg(0, std::ios::beg);

	trans = new Transaction[size];

	for (int i = 0; i < size; i++)
	{
		transFile.read((char*)(&trans[i]), sizeof(Transaction));
	}

	transFile.close();
}

double CountCoins(const Transaction* trans, unsigned size, unsigned id)
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

	return (receiverCoins - senderCoins);
}

unsigned NumberOfTrans(const Transaction * trans, unsigned size, unsigned id)
{
	unsigned counter = 0;
	for (int i = 0; i < size; i++)
	{
		if ((trans[i].receiverId == id) || (trans[i].senderId == id))
		{
			counter++;
		}
	}
	return counter;
}

long long FirstTrans(const Transaction * trans, unsigned size, unsigned id)
{
	for (int i = 0; i < size; i++)
	{
		if ((id == trans[i].receiverId) || (id == trans[i].senderId))
		{
			return trans[i].time;
		}
	}
}

long long LastTrans(const Transaction * trans, unsigned size, unsigned id)
{
	unsigned j = 0;
	for (int i = 0; i < size; i++)
	{
		if ((id == trans[i].receiverId) || (id == trans[i].senderId))
		{
			j = i;
		}
	}
	return trans[j].time;
}
