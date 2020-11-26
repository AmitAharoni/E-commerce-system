#include "Buyer.h"

Buyer::Buyer() : User() // c'tor
{
	this->cart = new Cart;
}

Buyer::Buyer(const string& userName, const string& pass, Address& address) : User(userName, pass, address) // c'tor
{
	this->cart = new Cart;

}

Buyer::Buyer(const Buyer& other) : User(other) // copy c'tor
{
	*this = other;
}

const Buyer& Buyer::operator=(const Buyer& other) // operator= 
{
	if (this != &other)
	{
		this->cart = other.cart;
		this->oldOrdersCarts = other.oldOrdersCarts;
	}
	return *this;

}

bool Buyer::operator>(const Buyer& other) // operator> (compare totalCartPrice)
{
	if (this->cart->getTotalCartPrice() > other.cart->getTotalCartPrice())
		return true; // buyer1 cart's price is bigger
	else
		return false;// buyer2 cart's price is bigger or equal
}

Buyer::~Buyer() // destructor
{
	while (!this->oldOrdersCarts.empty()) //not empty
	{
		delete this->oldOrdersCarts.back(); //delete last pointer data
		this->oldOrdersCarts.pop_back(); // take out last item
	}

	delete cart;
}

void Buyer::setCart(Cart& other)
{
	*this->cart = other;
}

void Buyer::BuyeraddProductToCart(Product* productToAdd)
{
	this->cart->myCart.push_back(productToAdd);
	this->cart->setTotalCartPrice(productToAdd->getPrice()); // add product price to cart total price
}

void Buyer::BuyerAddCartToOldOrders(Cart& cartToAdd)
{
	this->oldOrdersCarts.push_back(&cartToAdd);
}

vector<Cart*> Buyer::getOldOrdersCarts() const
{
	return this->oldOrdersCarts;
}