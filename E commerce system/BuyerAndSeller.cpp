#include "BuyerAndSeller.h"

BuyerAndSeller::BuyerAndSeller() : User(), Buyer(), Seller()
{

}

BuyerAndSeller::BuyerAndSeller(const string& userName, const string& pass, Address& address) : User(userName, pass, address), Buyer(userName, pass, address), Seller(userName, pass, address)
{

}

BuyerAndSeller::BuyerAndSeller(const BuyerAndSeller& other) : User(other), Buyer(other), Seller(other)
{
	 
}
