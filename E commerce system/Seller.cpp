#include "Seller.h"

Seller::Seller() : User() // c'tor
{

}

Seller::Seller(const string& userName, const string& pass, Address& address) : User(userName, pass, address) // c'tor
{

}

Seller::Seller(const Seller& other) : User(other) // copy c'tor
{
	*this = other;
}

Seller::Seller(Seller&& other) //move c'tor
{
	if (this != &other)
	{
		this->feedbacks = other.feedbacks;
		this->products = other.products;
	}
}

const Seller& Seller::operator=(const Seller& other) // operator= 
{
	if (this != &other)
	{
		this->feedbacks = other.feedbacks; // going to operator= in Array.h
		this->products = other.products; 
	}
	return *this;
}

Seller::~Seller() // destructor
{
	while (!this->products.empty()) //not empty
	{
		delete this->products.back(); //delete last pointer data
		this->products.pop_back(); // take out last item
	}
}

 void Seller::SellerAddProduct(int& serialNum)
 {
	 Product* productToAdd = new Product;

	 readNewProduct(*productToAdd, serialNum, this->getName());
	 products.push_back(productToAdd);
 }

 void Seller::readNewProduct(Product &product, int& serialNum, const string& sellerUserName)
 {
	 bool flag1 = false, flag2 = false, flag3 = false;
	 string productName;
	 float price;
	 int productCategory;
	 while (!flag1) // product name
	 {
		 cout << "Please enter product name: (Max 20 characters)\n";
		 getline(cin, productName);
		 flag1 = product.setProductName(productName);
	 }

	 while (!flag2) // price
	 {
		 cout << "Please enter product price: (positive number)\n";
		 cin >> price;
		 flag2 = product.setPrice(price);
	 }

	 while (!flag3) // category
	 {
		 cout << "Please enter product category: (0-kids, 1-electric, 2-office, 3-cloth)\n";
		 cin >> productCategory;
		 flag3 = product.setCategory((Product::eCategory)productCategory);
	 }

	 product.setSerialNum(++serialNum); // serial num
	 product.setAvailability(true);
	 product.setProductSellerName(sellerUserName);
 }