#include "offer.h"

int offer::getId() const {
	return id;
}

string offer::getName() const {
	return name;
}

string offer::getDest() const {
	return dest;
}

string offer::getType() const {
	return type;
}

int offer::getPrice() const {
	return price;
}