#ifndef __CART_H
#define __CART_H

#include "Product.h"
#include <vector>

class Cart
{
private:
	//variables
	vector<Product*> myCart;
	float totalCartPrice;

public:
	//c'tor && d'tor
	Cart();
	Cart(const Cart& other);
	const Cart& operator=(const Cart& other);// operator= 
	~Cart();

	//getters
	float getTotalCartPrice() const;
	vector<Product*> getCartProducts() const;

	//setters
	void setTotalCartPrice(const float num);

	friend class Buyer;
};


#endif
