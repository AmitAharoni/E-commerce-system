#ifndef __ADDRESS_H
#define __ADDRESS_H

#include <iostream>
#include <string>
#include <fstream>
using namespace std;
#pragma warning(disable: 4996)

class Address
{
private:
	//variables
	string country;
	string city;
	string streetAddress; 

public:
	//c'tor
	Address(); 
	Address(const string& country, const string& city, const string& streetAddress);
	Address(const Address& other);
	Address(Address&& other);
	const Address& operator=(const Address& other);

	//Setters
	bool setCountry(const string& country);
	bool setCity(const string& city);
	bool setStreetAddress(const string& streetAddress);

	//Getters
	const string& getCountry() const;
	const string& getCity() const;
	const string& getStreetAddress() const;

	friend ostream& operator<<(ostream& os, const Address& address) // operator <<
	{
		if (typeid(os) == typeid(ofstream)) //if we wtite to file
		{
			os << address.country << " " << address.city << " " << address.streetAddress; // write country city and street
		}
		else // if we need to print to console
		{
			os << "country:" << address.country << "\n" << "city:" << address.city << "\n"
				<< "street address:" << address.streetAddress << "\n";
		}

		return os;
	}

};
#endif