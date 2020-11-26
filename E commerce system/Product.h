#ifndef __PRODUCT_H
#define __PRODUCT_H

#include <iostream>
#include <string>
using namespace std;
#pragma warning(disable: 4996)

class Product
{
public:
	enum eCategory {kids, electric, office, cloth };

private:
	//variables
	string productName;
	float price;
	int serialNum;
	eCategory category;
	bool isAvaliabe;
	string productSellerName;

public:
	//c'tor && d'tor
	Product();
	Product(const string& productName, float price, int serialNum, eCategory category, bool isAvaliabe, const string& productSellerName); // c'tor
	Product(const Product& other);
	Product(Product&& other);
	const Product& operator=(const Product& other); // operator= 

	//Setters
	bool setProductName(const string& productName);
	bool setPrice(const float price);
	bool setSerialNum(const int serialNum);
	bool setCategory(eCategory category);
	void setAvailability(bool availability);
	void setProductSellerName(const string& other);

	//Getters
	 const string& getName() const;
	 float getPrice() const;
	 int getSerialNum() const;
	 eCategory getCategory() const;
	 bool getAvailability() const;
	 const string& getProductSellerName() const;
};
#endif
