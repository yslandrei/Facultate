#include "Iterator.h"
#include "LO.h"
#include <iostream>
#include <exception>

Iterator::Iterator(const LO& lo) : lo(lo) {
	it = lo.head;
}

void Iterator::prim() {
	it = lo.head;
}

void Iterator::urmator() {
	if (valid() == false)
		throw std::exception();
	it = it->next;
}

bool Iterator::valid() const {
	return it != NULL;
}

TElement Iterator::element() const {
	if (valid() == false)
		throw std::exception();
	return it->elem;
}


