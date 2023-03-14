#include <assert.h>
#include <string.h>
#include "offer.h"
#include "offersRepository.h"
#include "offersService.h"
#pragma warning(disable:4996)

void testAddOfferService() {
	int oListLen = 0;
	offer oList[100];

	assert(addOfferService(oList, &oListLen, 1, "tip", 1000, "adresa", 100) == 0);

	assert(oList[0].id == 1);
	assert(strcmp(oList[0].type, "tip") == 0);
	assert(oList[0].surface == 1000);
	assert(strcmp(oList[0].adress, "adresa") == 0);
	assert(oList[0].price == 100);
}

void testPopOfferService() {
	int oListLen = 0;
	offer oList[100];

	addOfferService(oList, &oListLen, 1, "tip", 1000, "adresa", 100);
	assert(popOfferService(oList, &oListLen, 1) == 0);
	assert(oListLen == 0);
}

void testModOfferService() {
	int oListLen = 0;
	offer oList[100];

	offer newOffer;
	newOffer.id = 1;
	strcpy(newOffer.type, "tip");
	newOffer.surface = 1000;
	strcpy(newOffer.adress, "adresa");
	newOffer.price = 100;

	offer moddedOffer = newOffer;
	moddedOffer.id = 2;

	addOfferService(oList, &oListLen, 1, "tip", 1000, "adresa", 100);
	assert(modOfferService(oList, &oListLen, 1, 2, "tip", 1000, "adresa", 100) == 0);
	assert(oList[0].id == 2);
}

void testGetSortedListByPriceAndType() {
	int oListLen = 0;
	offer oList[100];

	addOfferService(oList, &oListLen, 1, "tip", 1000, "adresa", 100);
	addOfferService(oList, &oListLen, 2, "tipul", 1000, "adresa", 100);
	addOfferService(oList, &oListLen, 3, "tip", 1000, "adresa", 50);

	offer* sortedOList;
	sortedOList = getSortedListByPriceAndType(oList, oListLen);
	assert(sortedOList[0].id == 3);
	assert(sortedOList[1].id == 2);
	assert(sortedOList[2].id == 1);

}

void testGetFilteredListByCriteria() {
	int oListLen = 0;
	offer oList[100];
	int filteredOListLen = 0;
	offer* filteredOList;

	addOfferService(oList, &oListLen, 1, "tip1", 1000, "adresa", 100);
	addOfferService(oList, &oListLen, 2, "tip2", 800, "adresa", 150);
	addOfferService(oList, &oListLen, 3, "tip3", 2000, "adresa", 300);

	char input1[25] = "p>=150 s<=2000 t>=tip";
	filteredOListLen = 0;
	filteredOList = getFilteredListByCriteria(oList, oListLen, input1, &filteredOListLen);
	assert(filteredOListLen == 2);

	char input2[25] = "p<300 s>900 t=tip1";
	filteredOListLen = 0;
	filteredOList = getFilteredListByCriteria(oList, oListLen, input2, &filteredOListLen);
	assert(filteredOListLen == 1);
}

