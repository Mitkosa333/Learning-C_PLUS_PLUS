#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <iostream>
#include <fstream>

#include "Basic.h"

struct Transaction {
	long long time;
	unsigned senderId;
	unsigned receiverId;
	double fmiCoins;
};

void DoubleTransactionArray(Transaction *&, unsigned);
void AddTransaction(Transaction*&, unsigned&, Transaction&);
void AddTransactionToFile(const Transaction*, const unsigned);
void AddOneTransactionToFile(const Transaction&);

void LoadTransaction(Transaction*&, unsigned&);

double CountCoins(const Transaction*, unsigned, unsigned);
unsigned NumberOfTrans(const Transaction*, unsigned, unsigned);

long long FirstTrans(const Transaction*, unsigned, unsigned);
long long LastTrans(const Transaction*, unsigned, unsigned);

#endif //TRANSACTION_H
