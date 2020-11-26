#include "Manager.h"

/*
E-commerce system: Supports buyers and sellers
operations. also include mini payment system.
Implemented with C++ using OOP principles & STL.
*/

int main()
{
	string nameFile = "E-commerce-system.txt";
	Manager m(nameFile);
	m.run();
}