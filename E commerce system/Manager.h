#ifndef __MANAGER_H
#define __MANAGER_H

#include <iostream>
#include <string>
using namespace std;
#pragma warning(disable: 4996)

#include "User.h"
#include "Buyer.h"
#include "Seller.h"
#include "BuyerAndSeller.h"
#include "Array.h"
#include <vector>
#include <fstream>

class Manager
{
private:
	//variables
	string system_name = "Shamit Express";
	vector<User*> users;
	int serialNum;

public:
	//c'tor && d'tor
	Manager(string nameFile);
	~Manager();

	//functions
	void run();
	void printMenu();
	void cleanBuffer();
	void readNewAddress(Address &address); // to put somewhere else. not here up because it might be problmatic because char[]
	bool checkValidUserName(const string& name);
	void readNewUser(User &user, Address &address);
	bool LogIn(int& userIndex); // log in for any type of user
	int LogInFindIndex(const string& name); // log in for any type of user

	//option 1
	void addBuyer();

	//option 2
	void addSeller();

	//option 3
	void addProduct();

	//option 4
	void addFeedBack();
	bool checkOldOrders(Buyer* currBuyer, const string& sellerUserName);
	void readNewDate(Date* theDate); 

	//option 5
	void addProductToCart();
	int printAllAvaliabeProductsInSystem();
	Product* findProductBySerialNum(int serialNum, bool* flag2);
	bool checkValidInputForChar(char userSelectForPayment);
	bool checkIfProductInCart(int serialNum, vector <Product*>& myCart);

	//option 6
	void executeOrder();

	//option 7
	void Payment();

	//option 8
	void ShowAllBuyers(); //prints also buyerAndSeller

	//option 9
	void ShowAllSellers(); //prints also buyerAndSeller

	//option 10
	void ShowAllProductsByName();
	bool checkValidProductName(const string& productName);
	void printProductInfo(Seller* seller, Product& curr, int counter);
	void readNewFeedback(Feedback& feedBackToAdd, Date &dateToAdd, const string& buyerUserName);

	//option 11
	void TesterOperatorPrintAddress();

	//option 12
	void TesterOperatorPrintFeedBack();

	//option 13
	void TesterOperatorPrintDate();

	//option 14
	void TesterOperatorCompareBuyers();

	//option 15
	void addBuyerAndSeller();
};
#endif