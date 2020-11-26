#ifndef __ARRAY_H
#define __ARRAY_H

#include <iostream>
#include <string>
using namespace std;
#pragma warning(disable: 4996)

template<class T>
class Array
{
private:
	int phySize, logSize;
	char delimiter;
	T* arr;

public:
	Array(int phySize = 1, int logSize = 0, char delimiter = ' '); // c'tor
	Array(const Array& other); // copy c'tor
	~Array(); // d'tor

	const Array& operator=(const Array& other);  //operator=
	const Array& operator=(const Array&& other); //move operator=
	const Array& operator+=(const T& newVal); //operator +=  -----> also doing resize

	friend ostream& operator<<(ostream& os, const Array& arr) // operator<< (print)
	{
		for (int i = 0; i < this->arr.logSize; i++)
			os << this->arr[i] << this->arr.delimiter;
		return os;
	}

};

template<class T>
Array<T>::Array(int phySize, int logSize, char delimiter) // c'tor
{
	this->phySize = phySize;
	this->logSize = logSize;
	this->delimiter = delimiter;
	arr = new T[phySize];
}

template<class T>
Array<T>::Array(const Array& other) //copy c'tor
{
	*this = other;
}

template<class T>
const Array<T>& Array<T>::operator=(const Array&& other) // move c'tor
{
	if (this != &other)
	{
		delete[] this->arr;
		this->arr = other.arr;
		other.arr = nullptr;
	}
	return *this;
}

template<class T>
Array<T>::~Array() //d'tor
{
	int i;

	for (i = 0; i < this->logSize; i++)
	{
		delete arr[i];
		this->arr[i] = nullptr;
	}
	delete[] this->arr;
}

template<class T>
const Array<T>& Array<T>::operator=(const Array& other) // operator=
{
	if (this != &other)
	{
		delete[] arr;
		this->logSize = other.logSize;
		this->phySize = other.phySize;
		this->delimiter = other.delimiter;

		this->arr = new T[this->phySize];
		for (int i = 0; i < this->logSize; i++)
			this->arr[i] = other.arr[i];
	}
	return *this;
}

//must have operator= for class T in his class
template<class T>
const Array<T>& Array<T>::operator+=(const T& newVal) //operator += also doing resize
{
	if (this->logSize >= this->phySize) // need space?
	{
		int newsize = this->phySize * 2;
		int i;
		T* resArr = new T[newsize];

		for (i = 0; i < this->logSize; i++) // copy all data to temp arr
			resArr[i] = this->arr[i];

		delete[] this->arr;
		this->phySize = newsize; // update size
		this->arr = resArr; //set the new arr with the new size as this->arr
	}

	this->arr[this->logSize++] = newVal; //put the value in the arr
	return *this;
}
#endif
