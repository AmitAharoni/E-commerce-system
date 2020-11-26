#include "Date.h"

Date::Date() // c'tor
{
	this->day = 00;
	this->month = 00;
	this->year = 0000;
}

Date::Date(int day, int month, int year) // c'tor
{
	setDay(day);
	setMonth(month);
	setMonth(year);
}

bool Date::setDay(const int day)
{
	if (day < 1 || day > 31)
		return false;
	else
	{
		this->day = day;
		return true;
	}
}

bool Date::setMonth(const int month)
{
	if (month < 1 || month > 12)
		return false;
	else
	{
		this->month = month;
		return true;
	}
}

bool Date::setYear(const int year)
{
	if (year < 2000)
		return false;
	else
	{
		this->year = year;
		return true;
	}
}

int Date::getDay() const
{
	return this->day;
}

int Date::getMonth() const
{
	return this->month;
}

int Date::getYear() const
{
	return this->year;
}

ostream& operator<<(ostream& os, const Date& date) // operator <<
{
	os  << date.getDay() << "/" << date.getMonth() << "/" << date.getYear() << "\n";
	return os;
}