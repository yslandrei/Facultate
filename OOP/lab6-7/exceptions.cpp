#include "exceptions.h"

ostream& operator<<(ostream& out, const repositoryException& ex) {
	out << ex.msg;
	return out;
}

ostream& operator<<(ostream& out, const validationException& ex) {
	out << ex.msg;
	return out;
}
