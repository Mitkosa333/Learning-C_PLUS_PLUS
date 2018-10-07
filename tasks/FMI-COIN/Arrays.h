#ifndef ARRAYS_H
#define ARRAYS_H

#include "Basic.h"
#include "Wallet.h"
#include "Transaction.h"
#include "Order.h"


struct Arrays 
{
	Wallet* wallets;
	unsigned sizeWallets;
	Transaction* transactions;
	unsigned sizeTransactions;
	Order* orders;
	unsigned sizeOrders;
};

void Constructor(Arrays &);
void LoadFiles(Arrays &);
void AddToFile(Arrays &);

void AddNewUser(Transaction *&, unsigned &, Wallet *&, unsigned &);

bool EnoughCoins(const Transaction*, const unsigned, const unsigned, const double);
bool EnoughMoney(const Wallet*, const unsigned, const unsigned, const double);

void WalletInfo(const Arrays&);

void AttractInvestors(Arrays&);
void FindTop10IDs(Arrays&, unsigned*, const int);

void ProcessOrder(Arrays &);
void ForwardBuyOrder(Arrays &);
void ForwardSellOrder(Arrays &);

void Destructor(Arrays &);

#endif //ARRAYS_H
