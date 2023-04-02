#pragma once
#include "testDomain.h"

void testOffer() {
	offer newOffer(0, "nume", "dest", "tip", 100);
	
	assert(newOffer.getId() == 0);
	assert(newOffer.getName() == "nume");
	assert(newOffer.getDest() == "dest");
	assert(newOffer.getType() == "tip");
	assert(newOffer.getPrice() == 100);
}