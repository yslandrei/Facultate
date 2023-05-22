#include "Iterator.h"
#include "LO.h"
#include <iostream>
#include <exception>

Iterator::Iterator(const LO& lo) : lo(lo) {
	it = &lo.nodes[lo.first];
}

void Iterator::prim() {
	it = &lo.nodes[lo.first];
}

void Iterator::urmator() {
	if (valid() == false)
		throw std::exception();
	it = &lo.nodes[it->next];
}

bool Iterator::valid() const {
	return it != &lo.nodes[NULL_TELEMENT];
}

TElement Iterator::element() const {
	return it->elem;
}


