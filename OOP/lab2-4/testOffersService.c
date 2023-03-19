#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "offer.h"
#include "offersList.h"
#include "offersRepository.h"
#include "offersService.h"
#pragma warning(disable:4996)

void testAddOfferService() {
	offersList o = createOList();
	char tip[25] = "tip";
	char adresa[25] = "adresa";

	assert(addOfferService(&o, 1, tip, 1000, adresa, 100) == 0);
	assert(o.List[0].id == 1);
	assert(strcmp(o.List[0].type, "tip") == 0);
	assert(o.List[0].surface == 1000);
	assert(strcmp(o.List[0].adress, "adresa") == 0);
	assert(o.List[0].price == 100);
	free(o.List);
}

void testPopOfferService() {
	offersList o = createOList();
	char tip[25] = "tip";
	char adresa[25] = "adresa";

	addOfferService(&o, 1, tip, 1000, adresa, 100);
	assert(popOfferService(&o, 1) == 0);
	assert(o.size == 0);
	free(o.List);
}

void testModOfferService() {
	offersList o = createOList();
	char tip[25] = "tip";
	char adresa[25] = "adresa";

	addOfferService(&o, 1, tip, 1000, adresa, 100);
	assert(modOfferService(&o, 1, 2, tip, 1000, adresa, 100) == 0);
	assert(o.List[0].id == 2);
	free(o.List);
}

void testGetSortedListByPriceAndType() {
	offersList o = createOList();
	char tip[25] = "tip";
	char tipul[25] = "tipul";
	char adresa[25] = "adresa";

	addOfferService(&o, 1, tip, 1000, adresa, 100);
	addOfferService(&o, 2, tipul, 1000, adresa, 100);
	addOfferService(&o, 3, tip, 1000, adresa, 50);

	offersList sortedO = createOList();
	sortListByPriceAndType(&o, &sortedO);
	assert(sortedO.List[0].id == 3);
	assert(sortedO.List[1].id == 2);
	assert(sortedO.List[2].id == 1);
	free(o.List);
	free(sortedO.List);
}

void testGetFilteredListByCriteria() {
	offersList o = createOList();
	char tip1[25] = "tip1";
	char tip2[25] = "tip2";
	char tip3[25] = "tip3";
	char adresa[25] = "adresa";

	addOfferService(&o, 1, tip1, 1000, adresa, 100);
	addOfferService(&o, 2, tip2, 800, adresa, 150);
	addOfferService(&o, 3, tip3, 2000, adresa, 300);

	offersList filteredO1 = createOList();
	char input1[25] = "s<=2000 p>=150 t>=tip";
	filterListByCriteria(&o, &filteredO1, input1);
	assert(filteredO1.size == 2);

	offersList filteredO2 = createOList();
	char input2[25] = "s>900 p<300 t=tip1";
	filterListByCriteria(&o, &filteredO2, input2);
	assert(filteredO2.size == 1);
	free(o.List);
	free(filteredO1.List);
	free(filteredO2.List);
}
