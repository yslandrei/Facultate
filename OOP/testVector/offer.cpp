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

offer& offer::operator=(const offer& other) {
	if (this != &other) {
		this->id = other.getId();
		this->name = other.getName();
		this->dest = other.getDest();
		this->type = other.getType();
		this->price = other.getPrice();
	}
	return *this;
}

bool offer::operator==(const offer& other) const {
	return id == other.id &&
		name == other.name &&
		dest == other.dest &&
		type == other.type &&
		price == other.price;
}

bool offer::operator!=(const offer& other) const {
	return !(id == other.id &&
		name == other.name &&
		dest == other.dest &&
		type == other.type &&
		price == other.price);
}


ostream& operator<<(ostream& os, const offer& Offer) {
	os << "id: " << Offer.getId() << ", nume: " << Offer.getName() << ", destinatie: " << Offer.getDest() << ", tip: " << Offer.getType() << ", pret: " << Offer.getPrice();
	return os;
}

