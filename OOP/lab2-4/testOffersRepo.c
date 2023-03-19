#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "offer.h"
#include "offersList.h"
#include "offersRepository.h"
#pragma warning(disable:4996)

void testAddOffer() {
	offersList o = createOList();

	offer newOffer;
	newOffer.id = 1;
	strcpy(newOffer.type, "tip");
	newOffer.surface = 1000;
	strcpy(newOffer.adress, "adresa");
	newOffer.price = 100;
	
	assert(addOffer(&o, newOffer) == 0);
	assert(o.List[0].id == newOffer.id);
	assert(strcmp(o.List[0].type, newOffer.type) == 0);
	assert(o.List[0].surface == newOffer.surface);
	assert(strcmp(o.List[0].adress, newOffer.adress) == 0);
	assert(o.List[0].price == newOffer.price);
	assert(addOffer(&o, newOffer) == -1);
	free(o.List);
}

void testPopOffer() {
	offersList o = createOList();

	offer newOffer;
	newOffer.id = 1;
	strcpy(newOffer.type, "tip");
	newOffer.surface = 1000;
	strcpy(newOffer.adress, "adresa");
	newOffer.price = 100;

	addOffer(&o, newOffer);
	newOffer.id = 2;
	addOffer(&o, newOffer);
	newOffer.id = 1;
	assert(popOffer(&o, newOffer) == 0);
	assert(o.size == 1);
	assert(popOffer(&o, newOffer) == -1);
	free(o.List);
}

void testModOffer() {
	offersList o = createOList();

	offer newOffer;
	newOffer.id = 1;
	strcpy(newOffer.type, "tip");
	newOffer.surface = 1000;
	strcpy(newOffer.adress, "adresa");
	newOffer.price = 100;

	offer moddedOffer = newOffer;
	moddedOffer.id = 2;

	addOffer(&o, newOffer);
	assert(modOffer(&o, newOffer, moddedOffer) == 0);
	assert(o.List[0].id == 2);
	assert(modOffer(&o, newOffer, moddedOffer) == -1);
	free(o.List);
}
