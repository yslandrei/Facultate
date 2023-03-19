#include <assert.h>
#include <string.h>
#include "offer.h"
#include "offersRepository.h"
#pragma warning(disable:4996)

void testAddOffer() {
	offersList o;

	offer newOffer;
	newOffer.id = 1;
	newOffer.type = "tip";
	newOffer.surface = 1000;
	newOffer.adress = "adresa";
	newOffer.price = 100;
	
	assert(addOffer(&o, newOffer) == 0);
	assert(o.List[0].id == newOffer.id);
	assert(o.List[0].type == newOffer.type);
	assert(o.List[0].surface == newOffer.surface);
	assert(o.List[0].adress == newOffer.adress);
	assert(o.List[0].price == newOffer.price);
	assert(addOffer(&o, newOffer) == -1);
}

void testPopOffer() {
	offersList o;

	offer newOffer;
	newOffer.id = 1;
	newOffer.type = "tip";
	newOffer.surface = 1000;
	newOffer.adress = "adresa";
	newOffer.price = 100;

	addOffer(&o, newOffer);
	newOffer.id = 2;
	addOffer(&o, newOffer);
	newOffer.id = 1;
	assert(popOffer(&o, newOffer) == 0);
	assert(o.size == 1);
	assert(popOffer(&o, newOffer) == -1);
}

void testModOffer() {
	offersList o;

	offer newOffer;
	newOffer.id = 1;
	newOffer.type = "tip";
	newOffer.surface = 1000;
	newOffer.adress = "adresa";
	newOffer.price = 100;

	offer moddedOffer = newOffer;
	moddedOffer.id = 2;

	addOffer(&o, newOffer);
	assert(modOffer(&o, newOffer, moddedOffer) == 0);
	assert(o.List[0].id == 2);
	assert(modOffer(&o, newOffer, moddedOffer) == -1);
}
