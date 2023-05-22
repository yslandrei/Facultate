
//#include "TestExtins.h"
//#include "TestScurt.h"
#include <iostream>
#include "Multime.h"
using namespace std;

int main() {
	//testAll();
	//testAllExtins();
	//cout << "That's all!" << endl;
	Multime m;
	m.adauga(3);
	m.adauga(1);
	m.adauga(1);
	m.adauga(1);
	m.adauga(4);
	m.adauga(4);
	m.adauga(4);
	m.adauga(6);
	m.adauga(0);
	m.adauga(0);
	m.adauga(0);
	m.adauga(0);
	m.adauga(3);
	m.adauga(6);
	m.adauga(3);
	m.adauga(6);
	m.adauga(7);
	m.afisare();
}
