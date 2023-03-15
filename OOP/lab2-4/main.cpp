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

int main() {
	testAll();

	//offersList o;
	//ui(&o);
	return 0;
}