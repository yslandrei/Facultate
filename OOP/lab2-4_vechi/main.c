#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "offer.h"
#include "offersList.h"
#include "offersRepository.h"
#include "offersService.h"
#include "ui.h"
#include "testOffersRepo.h"
#include "testOffersService.h"
#pragma warning(disable:4996)

void testAll() {
	testAddOffer();
	testPopOffer();
	testModOffer();
	testAddOfferService();
	testPopOfferService();
	testModOfferService();
	testGetSortedListByPriceAndType();
	testGetFilteredListByCriteria();
}

offersList createOList() {
	offersList o;
	o.size = 0;
	o.maxSize = 2;
	//o.List = (offer*)malloc(o.maxSize, sizeof(offer));
	return o;
}

int main() {
	//testAll();

	offersList o = createOList();
	ui(&o);

	_CrtDumpMemoryLeaks();
	return 0;
}