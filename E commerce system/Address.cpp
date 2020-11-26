#include "Address.h"

Address::Address() // c'tor
{
}

Address::Address(const string& country, const string& city, const string& streetAddress) // c'tor
{
	setCountry(country);
	setCity(city);
	setStreetAddress(streetAddress);
}

Address::Address(const Address& other) : country(nullptr), city(nullptr), streetAddress(nullptr) // copy c'tor
{
	*this = other;
}

Address::Address(Address&& other) // move c'tor
{
	if (this != &other)
	{
		this->country = other.country;
		this->city = other.city;
		this->streetAddress = other.streetAddress;
		other.country = nullptr;
		other.city = nullptr;
		other.streetAddress = nullptr;
	}
}

const Address& Address::operator=(const Address& other) // operator=
{
	if (this != &other)
	{
		setCountry(other.country);
		setCity(other.city);
		setStreetAddress(other.streetAddress);
	}
	return *(this);
}

bool Address::setCountry(const string& country)
{
	if ((country.length() == 0)  || (country.length() > 19))   // if input problem
		return false;
	else
	{
		this->country = country;
		return true;
	}
}

bool Address::setCity(const string& city)
{
	if ((city.length() == 0) || (city.length() > 19))   // if input problem
		return false;
	else
	{
		this->city = city;
		return true;
	}
}

bool Address::setStreetAddress(const string& streetAddress)
{
	if ((streetAddress.length() == 0) || (streetAddress.length() > 19))   // if input problem
		return false;
	else
	{
		this->streetAddress = streetAddress;
		return true;
	}
}

const string& Address::getCountry() const
{
	return this->country;
}

const string& Address::getCity() const
{
	return this->city;
}

const string& Address::getStreetAddress() const
{
	return this->streetAddress;
}