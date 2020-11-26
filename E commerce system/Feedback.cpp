#include "Feedback.h"

Feedback::Feedback()
{
}

Feedback::Feedback(const string userName, Date& date, const string theFeedback) // c'tor
{
	setName(userName);
	setDate(date);
	setFeedback(theFeedback);
}

Feedback::Feedback(const Feedback& other) : userName(nullptr), theFeedback(nullptr) // copy c'tor
{
	*this = other;
}

Feedback::Feedback(Feedback&& other)
{
	if (this != &other)
	{
		this->userName = other.userName;
		this->theFeedback = other.theFeedback;
	}
}

const Feedback& Feedback::operator=(const Feedback& other) // operator= 
{
	if (this != &other)
	{
		setName(other.userName);
		setDate(other.date);
		setFeedback(other.theFeedback);
	}
	return *this;
}

const Feedback& Feedback::operator=(Feedback&& other) // move operator= 
{
	if (this != &other)
	{
		this->userName = other.userName;
		this->theFeedback = other.theFeedback;
	}
	return *this;
}

bool Feedback::setName(const string& userName)
{
	if ((userName.length() == 0) || (userName.length() > 19))   // if input problem
		return false;
	else
	{
		this->userName = userName;
		return true;
	}
}

bool Feedback::setDate(const Date& date)
{
	if (date.getDay() < 1 || date.getDay() > 31 || date.getMonth() < 1 || date.getMonth() > 12 || date.getYear() < 2000) // input problem
		return false;
	else
	{
		this->date.setDay(date.getDay());
		this->date.setMonth(date.getMonth());
		this->date.setYear(date.getYear());
		return true;
	}
}

bool Feedback::setFeedback(const string& feedback)
{
	if ((feedback.length() == 0) || (feedback.length() > 199))   // if input problem
		return false;
	else
	{
		this->theFeedback = feedback;
		return true;
	}
}

const string& Feedback::getName() const
{
	return this->userName;
}

Date Feedback::getDate() const
{
	return this->date;
}

const string& Feedback::getFeedback() const
{
	return this->theFeedback;
}

 ostream& operator<<(ostream& os, const Feedback& feedBack) // operator <<
{
	os << "\nUser name: " << feedBack.getName() << "\n\n"
	   << "Date: " << feedBack.getDate() << "\n"
		<< "The feedback: " << feedBack.getFeedback() << "\n";

	return os;
}
