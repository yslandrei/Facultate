#include "IteratorMultime.h"
#include "Multime.h"
#include <iostream>

IteratorMultime::IteratorMultime(const Multime& m) : multime(m) {
	curent = 0;
	deplasare();
}

//complexitate O(m)
void IteratorMultime::deplasare()
{
	while (multime.e[curent] == NULL_TELEM or multime.e[curent] == STERS)curent++;
}
//complexitate O(m)
void IteratorMultime::prim() {
	curent = 0;
	deplasare();
}

//caz favorabil: theta(1)-iterator invalid
//caz defavorabil: theta(m)
//caz mediu: theta(m)
//complexitate generala: O(m)
void IteratorMultime::urmator() {
	if (!valid())throw std::exception("iterator invalid");
	curent++;
	deplasare();

}

//complexitate theta(1)
TElem IteratorMultime::element() const {
	if (!valid())throw std::exception("iterator invalid");
	return multime.e[curent];
}

//complexitate theta(1)
bool IteratorMultime::valid() const {

	return curent < multime.m;
}