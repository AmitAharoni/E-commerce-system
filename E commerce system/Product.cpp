#include "Product.h"

Product::Product() // c'tor
{
	this->price = -1;
	this->serialNum = -1;
	this->category = (eCategory)-1;
	this->isAvaliabe = false;
}

Product::Product(const string& productName, float price, int serialNum, eCategory category, bool isAvaliabe, const string& productSellerName) // c'tor
{
	setProductName(productName);
	setPrice(price);
	setSerialNum(serialNum);
	setCategory(category);
	setAvailability(isAvaliabe);
	setProductSellerName(productName);
}

Product::Product(const Product& other) : productName(nullptr), productSellerName(nullptr) // copy c'tor
{
	*this = other;
}

const Product& Product::operator=(const Product& other) // operator= 
{
	if (this != &other)
	{
		setProductName(other.productName);
		setPrice(other.price);
		setSerialNum(other.serialNum);
		setCategory(other.category);
		this->isAvaliabe = other.isAvaliabe;
		setProductSellerName(other.productSellerName);
	}
	return *this;
}

Product::Product(Product&& other)
{
	if (this != &other)
	{
		this->productName = other.productName;
		other.productName = nullptr;
	}
}

void Product::setProductSellerName(const string& other)
{
	this->productSellerName = other;
}

bool Product::setProductName(const string& productName)
{
	if ((productName.length() == 0) || (productName.length() > 19))   // if input problem
		return false;
	else
	{
		this->productName = productName;
		return true;
	}
}

void Product::setAvailability(bool availability)
{
	this->isAvaliabe = availability;
}

bool Product::setPrice(const float price)
{
	if (price <= 0)   // input problem
		return false;
	else
	{
		this->price = price;
		return true;
	}
}

bool Product::setSerialNum(const int serialNum)
{
	if (serialNum < 1)   // input problem
		return false;
	else
	{
		this->serialNum = serialNum;
		return true;
	}
}

bool Product::setCategory(Product::eCategory category)
{
	if (category < 0 || category > 3)   // input problem
		return false;
	else
	{
		this->category = category;
		return true;
	}
}

bool Product::getAvailability() const
{
	return this->isAvaliabe;
}

 const string& Product::getName() const
{
	return this->productName;
}

 const string& Product::getProductSellerName() const
 {
	 return this->productSellerName;
 }

 float Product::getPrice() const
{
	return this->price;
}

 int Product::getSerialNum() const
{
	return this->serialNum;
}

 Product::eCategory Product::getCategory() const
 {
	 return this->category;
 }

