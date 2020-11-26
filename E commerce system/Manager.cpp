#include "Manager.h"

Manager::Manager(string nameFile) // c'tor
{
	this->serialNum = 0;

	ifstream inFile(nameFile);
	if (inFile.is_open())
	{
		string username, pass, country, city, street, type;
		while (inFile >> type >> username >> pass >> country >> city >> street)
		{
			Address address(country, city, street);

			if (type == "Buyer")
			{
				User* tBuyer = new Buyer(username, pass, address);
				this->users.push_back(tBuyer);
			}
			else if (type == "Seller")
			{
				User* tSeller = new Seller(username, pass, address);
				this->users.push_back(tSeller);
			}
			else
			{
				User* tBuyerSeller = new BuyerAndSeller(username, pass, address);
				this->users.push_back(tBuyerSeller);
			}
		}
	}
	inFile.close();
}

Manager::~Manager() // destructor 
{
	ofstream outFile;
	outFile.open("ShamitExpress.txt");

	vector<User*>::iterator itr = this->users.begin();
	vector<User*>::iterator itrEnd = this->users.end();

	for (; itr != itrEnd; ++itr)
	{
		string tempUser = typeid(**itr).name() + 6;

		outFile << typeid(**itr).name() + 6 << " "; // here it saves the name - buyer or seller or buyerseller
		outFile << **itr << " ";
	}
	outFile.close();


	while (!this->users.empty()) //not empty
	{
		delete this->users.back(); //delete last pointer data
		this->users.pop_back(); // take out last item
	}
}

void Manager::run()
{
	int indexForSwitch;
	bool flag = true;

	while (flag)
	{
		printMenu();

		cin >> indexForSwitch;
		cout << "\n";
		switch (indexForSwitch)
		{
		case 1:
			Manager::addBuyer();
			break;
		case 2:
			Manager::addSeller();
			break;
		case 3:
			Manager::addProduct();
			break;
		case 4:
			Manager::addFeedBack();
			break;
		case 5:
			Manager::addProductToCart();
			break;
		case 6:
			Manager::executeOrder();
			break;
		case 7:
			Manager::Payment();
			break;
		case 8:
			Manager::ShowAllBuyers();
			break;
		case 9:
			Manager::ShowAllSellers();
			break;
		case 10:
			Manager::ShowAllProductsByName();
			break;
		case 11:
			Manager::TesterOperatorPrintAddress();
			break;
		case 12:
			Manager::TesterOperatorPrintFeedBack();
			break;
		case 13:
			Manager::TesterOperatorPrintDate();
			break;	
		case 14:
			Manager::TesterOperatorCompareBuyers();
			break;
		case 15:
			Manager::addBuyerAndSeller();
			break;
		case 16: // exit
			flag = false;
			break;
		default:
			cout << "Please select number from menu\n";
			break;
		}
	}
}

void Manager::printMenu()
{
	cout << "------------------------------------------------\n";
	cout << "Menu - Please select option:\n"
		<< "1 - Add buyer\n"
		<< "2 - Add seller\n"
		<< "3 - Add product for seller\n"
		<< "4 - Add feedback\n"
		<< "5 - Add product to cart\n"
		<< "6 - Execute order\n"
		<< "7 - Payment\n"
		<< "8 - Show all buyers\n"
		<< "9 - Show all sellers\n" 
		<< "10 - Show product by name\n"
		<< "11 - Tester Operator <<  of Address class\n"
		<< "12 - Tester Operator <<  of FeedBack class\n" 
		<< "13 - Tester Operator <<  of Date class\n"
		<< "14 - Tester Operator >  compare buyers\n"
		<< "15 - Add BuyerAndSeller\n"
		<< "16 - Exit\n";
}

void Manager::cleanBuffer()
{
	int c;
	do
	{
		c = getchar();
	} while (c != EOF && c != '\n');
}

void Manager::readNewAddress(Address &address) // func reads new address from user
{
	bool flag1 = false, flag2 = false, flag3 = false;
	string tempCountry;
	string tempCity;
	string tempStreetAddress;

	while (!flag1)
	{
		cout << "Please enter country: (Max 20 characters)\n";
		getline(cin, tempCountry);
		flag1 = address.setCountry(tempCountry);
	}

	while (!flag2)
	{
		cout << "Please enter city: (Max 20 characters)\n";
		getline(cin, tempCity);
		flag2 = address.setCity(tempCity);
	}

	while (!flag3)
	{
		cout << "Please enter street address: (Max 20 characters)\n";
		getline(cin, tempStreetAddress);
		flag3 = address.setStreetAddress(tempStreetAddress);
	}
}

bool Manager::checkValidUserName(const string& name)
{
	vector<User*>::iterator itrStart = this->users.begin();
	vector<User*>::iterator itrEnd = this->users.end();
	
	User* currUser = nullptr;
	for (; itrStart != itrEnd; ++itrStart)
	{
		currUser = *itrStart;
		if (*currUser == name)
			return false;
	}
	return true;
}

void Manager::readNewUser(User &user, Address &address)
{
	bool flag1 = false, flag2 = false;
	string tempName;
	string tempPass;

	cleanBuffer();
	while (!flag1)
	{
		cout << "Please enter username: (Max 20 characters)\n";
		getline(cin, tempName);
		if (checkValidUserName(tempName))
			flag1 = user.setName(tempName);
		else
			cout << "user name '" << tempName << "' is already exist\n";
	}

	while (!flag2)
	{
		cout << "Please enter password: (Max 20 characters)\n";
		getline(cin, tempPass);
		flag2 = user.setPass(tempPass);
	}

	readNewAddress(address);
	user.setAddress(address);
}

bool Manager::LogIn(int& userIndex)
{
	int userNameindex = -1;
	bool flag1 = false;

	string tempName;
	string tempPass;

	cleanBuffer();
	cout << "Log in\n" << "Please enter username\n";
	getline(cin, tempName);

	userNameindex = LogInFindIndex(tempName);
	if (userNameindex != -1)
	{
		cout << "Please enter password\n";
		getline(cin, tempPass);
		if (this->users[userNameindex]->getPass() == tempPass)
		{
			userIndex = userNameindex;
			return true;
		}
	}
	return false; // login failed
}

int Manager::LogInFindIndex(const string& name)
{
	vector<User*>::iterator itrStart = this->users.begin();
	vector<User*>::iterator itrEnd = this->users.end();

	User* currUser = nullptr;
	int i = 0;
	for (; itrStart != itrEnd; ++itrStart)
	{
		currUser = *itrStart;
		if (*currUser == name)
			return i;
		i++;
	}
	return -1;
}

//option 1
void Manager::addBuyer()
{
	User* buyerToAdd = new Buyer();
	Address* address = new Address;
	readNewUser(*buyerToAdd, *address);
	this->users.push_back(buyerToAdd);

	delete address;
	cout << "Thanks. new buyer:" << buyerToAdd->getName() << " successfully added to Shamit Express system.\n";
}

//option 2
void Manager::addSeller()
{
	User* sellerToAdd = new Seller();
	Address* address = new Address;
	readNewUser(*sellerToAdd, *address);
	this->users.push_back(sellerToAdd);

	delete address;
	cout << "Thanks. new seller:" << sellerToAdd->getName() << " successfully added to Shamit Express system.\n";
}

//option 3
void Manager::addProduct()
{
	bool islogInOK = false;
	int sellerIndex;

	islogInOK = LogIn(sellerIndex);
	if (islogInOK) // log in for any type of user
	{
		Seller* isSeller = dynamic_cast<Seller*>(this->users[sellerIndex]);
		if (isSeller) // check if seller
		{
			cout << "Log in succeeded.\n";
			isSeller->SellerAddProduct(this->serialNum);
			cout << "Thanks. Product successfully added.\n";
		}
		else
			cout << "No access! your not seller.\n";
	}
	else
		cout << "Log in failed!\n";
}

//option 4
void Manager::addFeedBack()
{
	int buyerIndex, sellerIndex;
	bool islogInOK, didPurchase = false;
	string buyerUserName;
	string sellerUserName;

	islogInOK = LogIn(buyerIndex);

	if (islogInOK) // log in for any type of user
	{
		Buyer* isBuyer = dynamic_cast<Buyer*>(this->users[buyerIndex]);
		if (isBuyer) // check if buyer
		{
			buyerUserName = isBuyer->getName();
			cout << "Please fill feedback form:\n" << "seller user name\n";
			getline(cin, sellerUserName);
			didPurchase = checkOldOrders(isBuyer, sellerUserName);

			if (didPurchase) //buyer did buy from seller.
			{
				sellerIndex = LogInFindIndex(sellerUserName); // find seller index in sellers arr

				Seller* isSeller = dynamic_cast<Seller*>(this->users[sellerIndex]);
				if (isSeller)  // if seller
				{
					if (isBuyer->getName() != isSeller->getName()) // buyer cant feedback himself!
					{
						Feedback* feedBackToAdd = new Feedback;
						Date* dateToAdd = new Date;
						readNewFeedback(*feedBackToAdd, *dateToAdd, buyerUserName); //update feedback info
						isSeller->feedbacks += feedBackToAdd; // add feedback to template Array
						delete dateToAdd;
						cout << "Thanks. Feedback successfully added.\n";
					}
					else
						cout << "Sorry. you can't feedback yourself.\n";
				}
			}
			else
				cout << "Sorry. no orders from this seller found.\n";
		}
		else
			cout << "No access! your not buyer.\n";
	}
	else
		cout << "Log in failed\n";
}

bool Manager::checkOldOrders(Buyer* currBuyer, const string& sellerUserName)
{
	vector<Cart*> currOldOrdersCart = currBuyer->getOldOrdersCarts();
	vector<Cart*>::iterator itrStart = currOldOrdersCart.begin();
	vector<Cart*>::iterator itrEnd = currOldOrdersCart.end();

	for ( ; itrStart != itrEnd; ++itrStart)
	{
		vector<Product*> currOldCartProducts = (*itrStart)->getCartProducts();
		vector<Product*>::iterator productItrStart = currOldCartProducts.begin();
		vector<Product*>::iterator productItrEnd = currOldCartProducts.end();

		for( ; productItrStart != productItrEnd; ++productItrStart)
		{
			if (sellerUserName == (*productItrStart)->getProductSellerName())

			if (*productItrStart != nullptr)
			{
				if(sellerUserName == (*productItrStart)->getProductSellerName())
					return true;
			}
		}
	}
	return false;
}

void Manager::readNewFeedback(Feedback& feedBackToAdd, Date &dateToAdd, const string& buyerUserName)
{
	bool flag1 = false;
	string theFeedBack;

	feedBackToAdd.setName(buyerUserName);

	readNewDate(&dateToAdd);
	feedBackToAdd.setDate(dateToAdd);

	cleanBuffer();
	while (!flag1)
	{
		cout << "Please enter your feedback text (MAX 200 CHARS)\n";
		getline(cin, theFeedBack); // read the feedback
		flag1 = feedBackToAdd.setFeedback(theFeedBack);
	}

}

void Manager::readNewDate(Date* theDate)
{
	bool flag1 = false, flag2 = false, flag3 = false;
	int day, month, year;

	while (!flag1)
	{
		cout << "Please enter day(1-31)\n";
		cin >> day;
		flag1 = theDate->setDay(day);
	}

	while (!flag2)
	{
		cout << "Please enter month (1-12)\n";
		cin >> month;
		flag2 = theDate->setMonth(month);
	}

	while (!flag3)
	{
		cout << "Please enter year (2000+)\n";
		cin >> year;
		flag3 = theDate->setYear(year);
	}
}

//option 5
void Manager::addProductToCart()
{
	Product* productToAdd = nullptr;
	bool islogInOK = false;
	bool buyerWantMoreProducts = true, flag2 = true;
	int nextProductSerialNum = 1, numOfProductsInSystem = 1, buyerIndex;
	char userSelectForPayment;

	islogInOK = LogIn(buyerIndex);

	if (islogInOK) // log in for any type of user
	{
		Buyer* isBuyer = dynamic_cast<Buyer*>(this->users[buyerIndex]);
		if (isBuyer) // check if buyer
		{
			while (numOfProductsInSystem > 0 && buyerWantMoreProducts && nextProductSerialNum != 0 )
			{
				numOfProductsInSystem = printAllAvaliabeProductsInSystem();

				while (numOfProductsInSystem > 0 && buyerWantMoreProducts && nextProductSerialNum != 0)
				{
					cout << "please choose proudct to add (Pick serial number, 0 to exit)\n";
					cin >> nextProductSerialNum;
					if (nextProductSerialNum != 0)
						productToAdd = findProductBySerialNum(nextProductSerialNum, &buyerWantMoreProducts); // updates productToAdd and buyerWantMoreProducts 
					else
						buyerWantMoreProducts = false;
				}

				if (numOfProductsInSystem > 0 && nextProductSerialNum != 0)
				{
					vector <Product*> myCart = isBuyer->cart->getCartProducts();
					if (!checkIfProductInCart(nextProductSerialNum, myCart)) // if product is not in my cart 
					{
						isBuyer->BuyeraddProductToCart(productToAdd);
						cout << "Thanks. Product successfully added to cart.\n";
						while (flag2)
						{
							cout << "Would you like to add another one ? (Y / N)";
							cin >> userSelectForPayment;
							buyerWantMoreProducts = checkValidInputForChar(userSelectForPayment);
							flag2 = !(buyerWantMoreProducts);
							if (userSelectForPayment == 'N' || userSelectForPayment == 'n')
								buyerWantMoreProducts = false;
						}
						flag2 = true;
					}
					else if (nextProductSerialNum == 0)
						break;
					else
					{
						cout << "Dear " << isBuyer->getName() << ", Product already in your cart\n";
						buyerWantMoreProducts = false;
						nextProductSerialNum = 0;
					}
				}
			}
		}
		else
			cout << "No access! your not buyer.\n";
	}
	else
		cout << "Log in failed\n";
}

bool Manager::checkIfProductInCart(int serialNum, vector <Product*>& myCart)
{
	vector<Product*>::iterator ItrStart = myCart.begin();
	vector<Product*>::iterator ItrEnd = myCart.end();
	Product* currProduct = nullptr;
	
	for (; ItrStart != ItrEnd; ++ItrStart)
	{
		currProduct = *ItrStart;

		if (ItrStart != ItrEnd)
		{
			if (serialNum == currProduct->getSerialNum())
				return true;
		}
	}
	return false;
}

Product* Manager::findProductBySerialNum(int serialNum, bool* flag2)
{
	vector<User*>::iterator usersItrStart = this->users.begin();
	vector<User*>::iterator usersItrEnd = this->users.end();

	for (; usersItrStart != usersItrEnd; ++usersItrStart)
	{
		Seller* isSeller = dynamic_cast<Seller*>(*usersItrStart);
		if (isSeller) // check if seller
		{
			vector<Product*>::iterator productsItrStart = isSeller->products.begin();
			vector<Product*>::iterator productsItrEnd = isSeller->products.end();

			for (; productsItrStart != productsItrEnd; ++productsItrStart)
			{
				Product* currProduct = *productsItrStart;
				if (currProduct->getSerialNum() == serialNum) // find serial num
				{
					if (currProduct->getAvailability()) // product is availabe
					{
						*flag2 = false; //  availabe
						return currProduct;
					}
					*flag2 = true; // not availabe
					return nullptr;
				}
			}
		}
	}
	return nullptr; // not found
}

bool Manager::checkValidInputForChar(char userSelectForPayment)
{
	if (userSelectForPayment != 'Y' && userSelectForPayment != 'y'
		&& userSelectForPayment != 'N' && userSelectForPayment != 'n') // invalid input
		return false;
	return true;
}

int Manager::printAllAvaliabeProductsInSystem()
{
	int counter = 0;
	vector<User*>::iterator usersItrStart = this->users.begin();
	vector<User*>::iterator usersItrEnd = this->users.end();

	for (; usersItrStart != usersItrEnd; ++usersItrStart)
	{
		Seller* isSeller = dynamic_cast<Seller*>(*usersItrStart);
		if (isSeller) // check if seller
		{
			vector<Product*>::iterator productsItrStart = isSeller->products.begin();
			vector<Product*>::iterator productsItrEnd = isSeller->products.end();

			for (; productsItrStart != productsItrEnd; ++productsItrStart)
			{
				Product* currProduct = *productsItrStart;
				if (currProduct->getAvailability())
				{
					counter++;
					printProductInfo(isSeller, *currProduct, counter);
				}
			}
		}
	}
	cout << "------------------------------------------------\n";
	cout << counter << " Avaliabe products in system\n";
	return counter;
}

//option 6
void Manager::executeOrder()
{
	int buyerIndex;
	char userSelectForPayment;
	bool flag = false;
	bool islogInOK = false;

	islogInOK = LogIn(buyerIndex);

	if (islogInOK) // log in for any type of user
	{
		Buyer* isBuyer = dynamic_cast<Buyer*>(this->users[buyerIndex]);
		if (isBuyer) // check if buyer
		{
			vector<Product*> products = isBuyer->cart->getCartProducts();
			vector<Product*>::iterator itrStart = products.begin();
			vector<Product*>::iterator itrEnd = products.end();
			
			if (products.empty())
				cout << "EMPTY CART - Please add products.\n";

			for (; itrStart != itrEnd; ++itrStart)
			{
				if (*itrStart != nullptr) //exist product
				{
					if ((*itrStart)->getAvailability()) //product availabile
					{
						while (!flag) // want this product?
						{
							cout << "Would you like to purchse this product? (Press 'Y' or  'N') \n";
							cout << "Product: " << (*itrStart)->getName() << "\nPrice: " << (*itrStart)->getPrice() << "\n";
							cin >> userSelectForPayment;
							flag = checkValidInputForChar(userSelectForPayment);
						}

						if (userSelectForPayment == 'N' || userSelectForPayment == 'n')
						{
							isBuyer->cart->setTotalCartPrice(-((*itrStart)->getPrice())); //decrease cart total price
							(*itrStart) = nullptr; // dont want this product
						}

						flag = false; // for while loop
					}

					else //product is not availabile
					{
						(*itrStart) = nullptr;
						cout << "EMPTY CART - Please add products.\n";
					}
				}
			}
		}
		else
			cout << "No access! your not buyer.\n";
	}
	else
		cout << "Log in failed\n";
}

//option 7
void Manager::Payment()
{
	int buyerIndex;
	float totalPrice = 0;
	bool isPurchase = false;;
	bool islogInOK = false;

	islogInOK = LogIn(buyerIndex);
	if (islogInOK) // log in for any type of user
	{
		Buyer* isBuyer = dynamic_cast<Buyer*>(this->users[buyerIndex]);
		if (isBuyer) // check if buyer
		{
			vector<Product*> products = isBuyer->cart->getCartProducts();
			vector<Product*>::iterator itrStart = products.begin();
			vector<Product*>::iterator itrEnd = products.end();

			for (; itrStart != itrEnd; ++itrStart)
			{				
				if (*itrStart != nullptr) //exist product
				{
					if ((*itrStart)->getAvailability()) //product availabile
					{
						(*itrStart)->setAvailability(false);
						totalPrice += (*itrStart)->getPrice();
						isPurchase = true;
					}
				}
			}

			if (isPurchase)
			{
				Cart* newCart = new Cart;
				isBuyer->BuyerAddCartToOldOrders(*isBuyer->cart); // save currCart as Oldorder
				isBuyer->cart = newCart;  //make cart new clean cart 
				cout << "Purchase completed.\ntotal price: " << totalPrice << "\nThanks for buying.\n ShamitExpress Crew.\n";
			}
			else
				cout << "No items in cart\n";
		}
		else
			cout << "No access! your not buyer.\n";
	}
	else
		cout << "Log in failed\n";
}

//option 8
void Manager::ShowAllBuyers()
{
	int buyersCounter = 0;

	vector<User*>::iterator itrStart = this->users.begin();
	vector<User*>::iterator itrEnd = this->users.end();

	for (; itrStart != itrEnd; ++itrStart)
	{
		Buyer *isBuyer = dynamic_cast<Buyer*>(*itrStart);
		if (isBuyer) // check if buyer
			cout << "Buyer #" << (++buyersCounter) << " - " << isBuyer->getName() << "\n";
	}

	if (buyersCounter == 0)
		cout << "No buyers in system\n";
}

//option 9
void Manager::ShowAllSellers()
{
	int sellersCounter = 0;

		vector<User*>::iterator itrStart = this->users.begin();
		vector<User*>::iterator itrEnd = this->users.end();

	for (; itrStart != itrEnd; ++itrStart)
	{
		Seller *isSeller = dynamic_cast<Seller*>(*itrStart);
		if (isSeller) // check if seller
			cout << "Seller #" << (++sellersCounter) << " - " << isSeller->getName() << "\n";
	}

	if (sellersCounter == 0)
		cout << "No sellers in system\n";
}

//option 10
void Manager::ShowAllProductsByName()
{
	bool flag = false;
	int counter = 0;
	string productName;

	while (!flag)
	{
		cout << "Please enter product name: (Max 20 characters)\n";
		cleanBuffer();
		getline(cin, productName);
		flag = checkValidProductName(productName);
	}

	vector<User*>::iterator usersItrStart = this->users.begin();
	vector<User*>::iterator usersItrEnd = this->users.end();
		for (; usersItrStart != usersItrEnd; ++usersItrStart)
		{
			Seller *isSeller = dynamic_cast<Seller*>(*usersItrStart);
			if (isSeller) // check if seller
			{
				vector<Product*>::iterator productsItrStart = isSeller->products.begin();
				vector<Product*>::iterator productsItrEnd = isSeller->products.end();

				for (; productsItrStart != productsItrEnd; ++productsItrStart)
				{
					Product* currProduct = *productsItrStart;
					if (productName == currProduct->getName() && (currProduct->getAvailability())) // same name and available
					{
						counter++;
						printProductInfo(isSeller, *currProduct, counter);
					}
				}
			}
		}
	cout << counter << " Product named - '" << productName << "' have been found.\n";
}

bool Manager::checkValidProductName(const string& productName)
{
	if ((productName.length() == 0) || productName.length() > 19)
		return false;

	return true;
}

void Manager::printProductInfo(Seller* seller, Product& curr, int counter)
{
	const string categories[4] = { "kids", "electric", "office", "cloth" };
	cout << "------------------------------------------------\n";
	cout << "#" << counter << "\n";
	cout << "Seller Name: " << seller->getName() << "\n";
	cout << "Product Name: " << curr.getName() << "\n";
	cout << "Price: " << curr.getPrice() << "\n";
	cout << "Serial Number: " << curr.getSerialNum() << "\n";
	cout << "Category: " << categories[(Product::eCategory)(curr.getCategory())] << "\n";
}

//option 11
void Manager::TesterOperatorPrintAddress()
{
	cout << "Hey, thats Tester for Operator<< Address class\n";
	Address* address = new Address;
	cleanBuffer();
	readNewAddress(*address);
	cout << *address;  // the use of the operator

	delete address;
}

//option 12
void Manager::TesterOperatorPrintFeedBack()
{
	cout << "Hey, thats Tester for Operator<< FeedBack class\n";

	Feedback feedBack;
	Date d1;
	string username = " lebron james"; //example

	cleanBuffer();
	readNewFeedback(feedBack, d1, username);

	cout << feedBack;  // the use of the operator
}

//option 13
void Manager::TesterOperatorPrintDate()
{
	cout << "Hey, thats Tester for Operator<< Date class\n";
	Date* date = new Date;
	cleanBuffer();
	readNewDate(date);
	cout << *date;  // the use of the operator

	delete date;
}

//option 14
void Manager::TesterOperatorCompareBuyers()
{
	cout << "Hey, thats Tester for Operator > compare buyer carts\n";
	float price1, price2;
	cout << "please enter price for buyer1 product\n";
	cin >> price1;
	cout << "please enter price for buyer2 product\n";
	cin >> price2;

	Buyer buyer1;
	string sellerName = " seller12"; //example
	string productName = "ballon"; //example
	Product::eCategory e = Product::eCategory::office; //example
	Product* product1 = new Product;
	product1->setCategory(e);
	product1->setPrice(price1);
	product1->setProductName(productName);
	product1->setProductSellerName(sellerName);
	buyer1.BuyeraddProductToCart(product1); // add product1 to buyer1 cart

	Buyer buyer2;
	string sellerName2 = " seller"; //example
	string productName2 = "ball"; //example
	Product::eCategory e2 = Product::eCategory::kids; //example
	Product* product2 = new Product;
	product2->setCategory(e2);
	product2->setPrice(price2);
	product2->setProductName(productName2);
	product2->setProductSellerName(sellerName2);
	buyer2.BuyeraddProductToCart(product2);// add product2 to buyer2 cart

	if (buyer1 > buyer2)  // the use of the operator
		cout << "buyer1 cart is bigger than buyer2 cart\n";
	else
		cout << "buyer1 cart is not(!!!!) bigger than buyer2 cart\n";

	delete product1;
	delete product2;
}

//option 15
void Manager::addBuyerAndSeller()
{
	User* buyerAndSellerToAdd = new BuyerAndSeller();
	Address* address = new Address;
	readNewUser(*buyerAndSellerToAdd, *address);
	this->users.push_back(buyerAndSellerToAdd);

	delete address;
	cout << "Thanks. new buyerAndSeller:" << buyerAndSellerToAdd->getName() << " successfully added to Shamit Express system.\n";
}


