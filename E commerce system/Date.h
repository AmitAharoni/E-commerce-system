#ifndef __DATE_H
#define __DATE_H

#include <iostream>
#include <string.h>
using namespace std;
#pragma warning(disable: 4996)

class Date
{
private:
	//variables
	int day;
	int month;
	int year;

public:
	//c'tor && d'tor
	Date(); // 00:00:0000
	Date(int day, int month, int year); 
	~Date() = default;

	//Setters
	bool setDay(const int day);
	bool setMonth(const int month);
	bool setYear(const int year);

	//Getters
	int getDay() const;
	int getMonth() const;
	int getYear() const;

	//functions
	friend ostream& operator<<(ostream& os, const Date& date); // operator <<
};
#endif