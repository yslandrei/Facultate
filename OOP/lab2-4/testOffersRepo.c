#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "offer.h"
#include "List.h"
#include "utils.h"
#include "offersRepository.h"
#pragma warning(disable:4996)

void testAddOffer() {
	List o = createList();
	offer* newOffer = createOffer(1, "tip", 1000, "adresa", 100);
	offer* sameNewOffer = createOffer(1, "tip", 1000, "adresa", 100);
	
	assert(addOffer(&o, newOffer) == 0);
	assert((*(offer*) o.arr[0]).id == (*newOffer).id);
	assert(strcmp((*(offer*) o.arr[0]).type, (*newOffer).type) == 0);
	assert((*(offer*) o.arr[0]).surface == (*newOffer).surface);
	assert(strcmp((*(offer*) o.arr[0]).adress, (*newOffer).adress) == 0);
	assert((*(offer*) o.arr[0]).price == (*newOffer).price);
	assert(addOffer(&o, sameNewOffer) == -1);
	
	freeOList(&o);
}

void testPopOffer() {
	List o = createList();
	offer* newOffer = createOffer(1, "tip", 1000, "adresa", 100);
	offer* sameNewOffer = createOffer(1, "tip", 1000, "adresa", 100);
	offer* otherOffer = createOffer(2, "tip", 1000, "adresa", 100);

	addOffer(&o, newOffer);
	addOffer(&o, otherOffer);
	assert(popOffer(&o, newOffer) == 0);
	assert(o.size == 1);
	assert(popOffer(&o, sameNewOffer) == -1);

	freeOffer(sameNewOffer);
	freeOList(&o);
}

void testModOffer() {
	List o = createList();
	offer* newOffer = createOffer(1, "tip", 1000, "adresa", 100);
	offer* sameNewOffer = createOffer(1, "tip", 1000, "adresa", 100);
	offer* moddedOffer = createOffer(2, "tip", 1000, "adresa", 100);
	offer* sameModdedOffer = createOffer(2, "tip", 1000, "adresa", 100);

	addOffer(&o, newOffer);
	assert(modOffer(&o, newOffer, moddedOffer) == 0);
	assert((*(offer*) o.arr[0]).id == 2);
	assert(modOffer(&o, sameNewOffer, sameModdedOffer) == -1);

	freeOffer(sameNewOffer);
	freeOList(&o);
}