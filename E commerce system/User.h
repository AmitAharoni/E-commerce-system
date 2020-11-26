#ifndef __User_H
#define __User_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#pragma warning(disable: 4996)

#include <vector>
#include "Address.h"

class User
{
	protected:
	//variables
	string userName;
	string pass;
	Address address;

	//Protected functions (abstract class)
	User(); // c'tor
	User(const string& userName, const string& pass, Address& address); // c'tor
	User(const User& other); // copy c'tor
	const User& operator=(const User& other); //operator=
	bool operator==(const string& other); //operator== (for string)
	bool operator==(const User& other); //operator==

	public:
	virtual ~User(); // virtual d'tor (polymorphism)
	
	//Setters
	bool setName(const string& username);
	bool setPass(const string& pass);
	void setAddress(const Address& address);

	//Getters
	const string& getName() const;
	const string& getPass() const;
	Address getAddress() const;

	//Functions
	virtual User* clone() const = 0;

	friend ostream& operator<<(ostream& os, const User& user) // operator <<
	{
		if (typeid(os) == typeid(ofstream)) //print to file only
		{
			os << user.userName << " " << user.pass << " " << user.address; // here its print to the file the username and pass and then go to oprator<< in address
		}
		else // print to console if necessery
		{
			os << "usermame:" << user.userName << "\n" << "city:" << user.pass << "\n"
				<< "street address:" << user.address << "\n";
		}

		return os;
	}

	friend class Manager;
};

#endif