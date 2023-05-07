#pragma once
#include "offer.h"
#include <vector>
#include <string>
#include <ostream>

using std::vector;
using std::string;
using std::ostream;

class repositoryException {
private:
	string msg;
public:
	string what() {
		return msg;
	}
	repositoryException(string m) :msg{ m } {}
	friend ostream& operator<<(ostream& out, const repositoryException& ex);
};

ostream& operator<<(ostream& out, const repositoryException& ex);

class validationException {
private:
	string msg;
public:
	string what() {
		return msg;
	}
	validationException(string m) :msg{ m } {}
	friend ostream& operator<<(ostream& out, const validationException& ex);
};

ostream& operator<<(ostream& out, const validationException& ex);
