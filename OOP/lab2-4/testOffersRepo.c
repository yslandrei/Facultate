#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "offer.h"
#include "offersList.h"
#include "utils.h"
#include "offersRepository.h"
#pragma warning(disable:4996)

void testAddOffer() {
	offersList o = createOList();
	offer newOffer = createOffer(1, "tip", 1000, "adresa", 100);
	offer sameNewOffer = createOffer(1, "tip", 1000, "adresa", 100);
	
	assert(addOffer(&o, newOffer) == 0);
	assert(o.List[0].id == newOffer.id);
	assert(strcmp(o.List[0].type, newOffer.type) == 0);
	assert(o.List[0].surface == newOffer.surface);
	assert(strcmp(o.List[0].adress, newOffer.adress) == 0);
	assert(o.List[0].price == newOffer.price);
	assert(addOffer(&o, sameNewOffer) == -1);

	freeOList(&o);
}

void testPopOffer() {
	offersList o = createOList();
	offer newOffer = createOffer(1, "tip", 1000, "adresa", 100);
	offer sameNewOffer = createOffer(1, "tip", 1000, "adresa", 100);
	offer otherOffer = createOffer(2, "tip", 1000, "adresa", 100);

	addOffer(&o, newOffer);
	addOffer(&o, otherOffer);
	assert(popOffer(&o, newOffer) == 0);
	assert(o.size == 1);
	assert(popOffer(&o, sameNewOffer) == -1);

	freeOffer(&sameNewOffer);
	freeOList(&o);
}

void testModOffer() {
	offersList o = createOList();
	offer newOffer = createOffer(1, "tip", 1000, "adresa", 100);
	offer sameNewOffer = createOffer(1, "tip", 1000, "adresa", 100);
	offer moddedOffer = createOffer(2, "tip", 1000, "adresa", 100);
	offer sameModdedOffer = createOffer(2, "tip", 1000, "adresa", 100);

	addOffer(&o, newOffer);
	assert(modOffer(&o, newOffer, moddedOffer) == 0);
	assert(o.List[0].id == 2);
	assert(modOffer(&o, sameNewOffer, sameModdedOffer) == -1);

	freeOffer(&sameNewOffer);
	freeOList(&o);
}
