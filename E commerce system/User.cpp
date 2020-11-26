#include "User.h"

User::User() // c'tor
{
}

User::User(const string& userName, const string& pass, Address& address) // c'tor
{
	setName(userName);
	setPass(pass);
	setAddress(address);
}

User::User(const User& other) : userName(nullptr), pass(nullptr) // copy c'tor
{
	*this = other;
}

const User& User::operator=(const User& other) // operator= 
{
	if (this != &other)
	{
		this->address = other.address;
		setName(other.userName);
		setPass(other.pass);
	}
	return *(this);
}

bool User::operator==(const string& other) //operator== (for string)
{
	return (this->getName() == other);
}

bool User::operator==(const User& other) //operator== (for User)
{
	return (this->getName() == other.getName());
}

User::~User() // destructor
{
}

bool User::setName(const string& username)
{
	if ((username.length() == 0) || (username.length() > 19))   // if input problem
		return false;
	else
	{
		this->userName = username;
		return true;
	}
}

bool User::setPass(const string& pass)
{
	if ((pass.length() == 0) || (pass.length() > 19))   // if input problem
		return false;
	else
	{
		this->pass = pass; 
			return true;
	}
}

void User::setAddress(const Address& address)
{
	this->address.setCountry(address.getCountry());
	this->address.setCity(address.getCity());
	this->address.setStreetAddress(address.getStreetAddress());
}

const string& User::getName() const
{
	return this->userName;
}

const string& User::getPass() const
{
	return this->pass;
}

Address User::getAddress() const
{
	return this->address;
}