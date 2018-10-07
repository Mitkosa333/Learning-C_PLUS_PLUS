#ifndef WALLET_H
#define WALLET_H

#include <iostream>
#include <fstream>
#include <random>

#include "Basic.h"
#include "Transaction.h"

const unsigned randGenNum = 375;
const unsigned programId = 4294967295;

struct Wallet {
	char owner[256];
	unsigned id;
	double fiatMoney;
};


unsigned GenerateID(const Wallet *, const unsigned);

Transaction AddWallet(Wallet *&, unsigned&);
void AddWalletToFile(const Wallet*, const unsigned);
void AddOneWalletToFile(const Wallet&);

void LoadWallets(Wallet *&, unsigned&);

bool ifNameExist(Wallet*, const unsigned,const char*);
bool ifIdExist(const Wallet*, const unsigned, const unsigned);

void DoubleWalletArray(Wallet *&, unsigned);
void RemoveMoneyFromWallet(Wallet *, const unsigned, const unsigned, const double);
void AddMoneyToWallet(Wallet *, const unsigned, const unsigned, const double);


#endif //WALLET_H
