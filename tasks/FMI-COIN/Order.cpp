#include "Order.h"

void AddOrder(Order & order, const char * type, const unsigned walletId, const double fmiCoins)
{
	if (stricmp(type, "sell") == 0)
	{
		order.type = Order::SELL;
	}
	else if (stricmp(type, "buy") == 0)
	{
		order.type = Order::BUY;
	}

	order.walletId = walletId;
	order.fmiCoins = fmiCoins;
}

void AddOrderToFile(const Order * order, const unsigned size)
{
	std::ofstream orderFile("orders.dat", std::ios::binary | std::ios::trunc);
	if (!orderFile.good())
	{
		std::cerr << "Error writing on file (orders.dat)" << std::endl;
		return;
	}

	for (int i = 0; i < size; i++)
	{
		if (order[i].fmiCoins != 0)
		{
			orderFile.write((char*)(&order[i]), sizeof(Order));
		}
	}

	orderFile.close();
}

void AddOneOrderToFile(const Order & order)
{
	std::ofstream orderFile("orders.dat", std::ios::binary | std::ios::app);
	if (!orderFile.good())
	{
		std::cerr << "Error writing on file (orders.dat)" << std::endl;
		return;
	}

	if (order.fmiCoins != 0)
	{
		orderFile.write((char*)(&order), sizeof(Order));
	}

	orderFile.close();
}

void DoubleOrderArray(Order *& order, unsigned size)
{
	Order* temp = new Order[size];

	for (int i = 0; i < size; i++)
	{
		temp[i] = order[i];
	}

	delete[] order;
	order = nullptr;

	unsigned tempSize = size;
	size = size * 2;
	order = new Order[size];

	for (int i = 0; i < tempSize; i++)
	{
		order[i] = temp[i];
	}

	delete[] temp;
}

void LoadOrder(Order *& orders, unsigned& size)
{
	std::ifstream orderFile;
	orderFile.open("orders.dat", std::ios::binary);

	if (!orderFile.good())
	{
		return;
	}

	orderFile.seekg(0, std::ios::end);
	size = orderFile.tellg() / (sizeof(Order));
	orderFile.seekg(0, std::ios::beg);

	orders = new Order[size];

	for (int i = 0; i < size; i++)
	{
		orderFile.read((char*)(&orders[i]), sizeof(Order));
	}

	orderFile.close();
}

void AddNewOrder(Order *& orders, unsigned& size, const char * bufferType, const unsigned walletId, const double fmiCoins)
{
	if (size == 0)
	{
		size++;
		orders = new Order[size];
	}
	else if (ifPowerOf2(size))
	{
		DoubleOrderArray(orders, size);
		size++;
	}
	else
	{
		size++;
	}

	AddOrder(orders[size - 1], bufferType, walletId, fmiCoins);
	AddOneOrderToFile(orders[size - 1]);
}

bool ExistingSellOrders(const Order * orders, const unsigned size)
{
	for (int i = 0; i < size; i++)
	{
		if ((orders[i].type == Order::SELL) && (orders[i].fmiCoins > 0))
		{
			return true;
		}
	}
	return false;
}

bool ExistingBuyOrders(const Order * orders, const unsigned size)
{
	for (int i = 0; i < size; i++)
	{
		if ((orders[i].type == Order::BUY) && (orders[i].fmiCoins > 0))
		{
			return true;
		}
	}
	return false;
}
