#ifndef ORDER_H
#define ORDER_H

#include "Wallet.h"

struct Order {
	enum Type { SELL, BUY } type;
	unsigned walletId;
	double fmiCoins;
};

void AddOrder(Order&, const char*, const unsigned, const double);
void AddOrderToFile(const Order*, const unsigned);
void AddOneOrderToFile(const Order&);
void DoubleOrderArray(Order *&, unsigned);
void LoadOrder(Order*&, unsigned&);
void AddNewOrder(Order*&, unsigned&,const char*,const unsigned,const double);

bool ExistingSellOrders(const Order*, const unsigned);
bool ExistingBuyOrders(const Order*, const unsigned);

#endif //ORDER_H
