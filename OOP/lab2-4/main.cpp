#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "offer.h"
#include "offersRepository.h"
#include "offersService.h"
#include "ui.h"
#include "testOffersRepo.h"
#include "testOffersService.h"
#pragma warning(disable:4996)

void runTests() {
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
	runTests();
	
	int oListLen = 0;
	offer oList[100];
	ui(oList, oListLen);
	return 0;
}