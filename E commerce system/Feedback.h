#ifndef __FEEDBACK_H
#define __FEEDBACK_H

#include <iostream>
#include <string>
using namespace std;
#pragma warning(disable: 4996)

#include "Date.h"

class Feedback
{
private:
	//variables
	string userName; //who gives the feedback
	Date date;
	string theFeedback; // max 200 chars

public:
	//c'tor && d'tor
	Feedback();
	Feedback(const string userName, Date& date, const string theFeedback);
	Feedback(const Feedback& other);
	Feedback(Feedback&& other); 
	const Feedback& operator=(const Feedback& other); // operator=
	const Feedback& operator=(Feedback&& other);
	friend ostream& operator<<(ostream& os, const Feedback& feedBack); // operator <<

	//setters
	bool setName(const string& userName);
	bool setDate(const Date& date);
	bool setFeedback(const string& feedback);

	//getters
	 const string& getName() const;
	 Date getDate() const;
	 const string& getFeedback() const;	 
};
#endif
