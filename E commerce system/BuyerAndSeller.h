#ifndef __BuyerAndSeller_H
#define __BuyerAndSeller_H

#include "User.h"
#include "Buyer.h"
#include "Seller.h"
#include <iostream>


class BuyerAndSeller : public Buyer, public Seller
{

public:
	//c'tor && d'tor
	BuyerAndSeller();
	BuyerAndSeller(const string& userName, const string& pass, Address& address);
	BuyerAndSeller(const BuyerAndSeller& other);
	BuyerAndSeller(BuyerAndSeller&&) = delete;

	//Functions
	virtual User* clone() const override { return new BuyerAndSeller(*this); }

	friend class Manager;
};
#endif