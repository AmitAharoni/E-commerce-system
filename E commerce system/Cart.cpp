#include "Cart.h"

Cart::Cart() // c'tor
{
	this->totalCartPrice = 0;
}

Cart::Cart(const Cart& other) // copy c'tor
{
	*this = other;
}

const Cart& Cart::operator=(const Cart& other) // operator= 
{
	if (this != &other)
	{
		this->myCart = other.myCart;
		this->totalCartPrice = other.totalCartPrice;
	}

	return *this;
}

Cart::~Cart() // destructor 
{
	while (!this->myCart.empty()) //not empty
	{
		//delete this->myCart.back(); //delete last pointer data
		this->myCart.pop_back(); // take out last item
	}
}

float Cart::getTotalCartPrice() const
{
	return this->totalCartPrice;
}

void Cart::setTotalCartPrice(const float num)
{
	this->totalCartPrice += num;
}

vector<Product*> Cart::getCartProducts() const
{
	return this->myCart;
}



