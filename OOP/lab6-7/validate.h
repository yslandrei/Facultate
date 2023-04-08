#pragma once
#include <exception>
#include "offer.h"

using std::exception;

class validate {
public:
	static const void offer(const offer& Offer) {
		char msg[100] = "";
		if (Offer.getId() < 0)
			strcat_s(msg, "ID invalid!\n");
		if (Offer.getName().size() == 0)
			strcat_s(msg, "Nume invalid!\n");
		if (Offer.getDest().size() == 0)
			strcat_s(msg, "Destinaie invalida!\n");
		if (Offer.getType().size() == 0)
			strcat_s(msg, "Tip invalid!\n");
		if (Offer.getPrice() < 0)
			strcat_s(msg, "Pret invalid!\n");

		if(strlen(msg))
			throw exception(msg);
	}

	static const void id(const int& id) {
		if (id < 0)
			throw exception("ID invalid!\n"); }

	static const void name(const string& name) {
		if (name.size() == 0)
			throw exception("Nume invalid!\n"); }

	static const void dest(const string& dest) {
		if (dest.size() == 0)
			throw exception("Destinatie invalida!\n"); }

	static const void type(const string& type) {
		if (type.size() == 0)
			throw exception("Tip invalid!\n"); }

	static const void price(const int& price) {
		if (price < 0)
			throw exception("Pret invalid!\n"); }
};

