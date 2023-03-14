#include <assert.h>
#include <string.h>
#include "offer.h"
#include "offersRepository.h"
#pragma warning(disable:4996)

void testAddOffer() {
	int oListLen = 0;
	offer oList[100];

	offer newOffer;
	newOffer.id = 1;
	newOffer.type = "tip";
	newOffer.surface = 1000;
	newOffer.adress = "adresa";
	newOffer.price = 100;
	
	assert(addOffer(oList, &oListLen, newOffer) == 0);

	assert(oList[0].id == newOffer.id);
	assert(oList[0].type == newOffer.type);
	assert(oList[0].surface == newOffer.surface);
	assert(oList[0].adress == newOffer.adress);
	assert(oList[0].price == newOffer.price);

	assert(addOffer(oList, &oListLen, newOffer) == -1);
}

void testPopOffer() {
	int oListLen = 0;
	offer oList[100];

	offer newOffer;
	newOffer.id = 1;
	newOffer.type = "tip";
	newOffer.surface = 1000;
	newOffer.adress = "adresa";
	newOffer.price = 100;

	addOffer(oList, &oListLen, newOffer);
	newOffer.id = 2;
	addOffer(oList, &oListLen, newOffer);
	newOffer.id = 1;
	assert(popOffer(oList, &oListLen, newOffer) == 0);
	assert(oListLen == 1);
	assert(popOffer(oList, &oListLen, newOffer) == -1);
}

void testModOffer() {
	int oListLen = 0;
	offer oList[100];

	offer newOffer;
	newOffer.id = 1;
	newOffer.type = "tip";
	newOffer.surface = 1000;
	newOffer.adress = "adresa";
	newOffer.price = 100;

	offer moddedOffer = newOffer;
	moddedOffer.id = 2;

	addOffer(oList, &oListLen, newOffer);
	assert(modOffer(oList, &oListLen, newOffer, moddedOffer) == 0);
	assert(oList[0].id == 2);
	assert(modOffer(oList, &oListLen, newOffer, moddedOffer) == -1);
}
