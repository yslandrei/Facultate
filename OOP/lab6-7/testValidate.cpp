#include "testValidate.h"
#include "exceptions.h"

void testValidate() {
	offer Offer(-1, "", "", "", -100);
	try {
		validate::offer(Offer); assert(false);
	}
	catch (validationException e) {
		assert(true);
	}
	try {
		validate::id(-1); assert(false);
	}
	catch (validationException e) {
		assert(true);
	}
	try {
		validate::name(""); assert(false);
	}
	catch (validationException e) {
		assert(true);
	}
	try {
		validate::dest(""); assert(false);
	}
	catch (validationException e) {
		assert(true);
	}
	try {
		validate::type(""); assert(false);
	}
	catch (validationException e) {
		assert(true);
	}
	try {
		validate::price(-1); assert(false);
	}
	catch (validationException e) {
		assert(true);
	}
}