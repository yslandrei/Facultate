#include "testValidate.h"

void testValidate() {
	offer Offer(-1, "", "", "", -100);
	try {
		validate::offer(Offer); assert(false);
	}
	catch (exception e) {
		assert(strcmp(e.what(), "ID invalid!\nNume invalid!\nDestinaie invalida!\nTip invalid!\nPret invalid!\n") == 0);
	}
	try {
		validate::id(-1); assert(false);
	}
	catch (exception e) {
		assert(strcmp(e.what(), "ID invalid!\n") == 0);
	}
	try {
		validate::name(""); assert(false);
	}
	catch (exception e) {
		assert(strcmp(e.what(), "Nume invalid!\n") == 0);
	}
	try {
		validate::dest(""); assert(false);
	}
	catch (exception e) {
		assert(strcmp(e.what(), "Destinatie invalida!\n") == 0);
	}
	try {
		validate::type(""); assert(false);
	}
	catch (exception e) {
		assert(strcmp(e.what(), "Tip invalid!\n") == 0);
	}
	try {
		validate::price(-1); assert(false);
	}
	catch (exception e) {
		assert(strcmp(e.what(), "Pret invalid!\n") == 0);
	}
}