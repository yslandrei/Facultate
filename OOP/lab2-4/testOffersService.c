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
	char tip1[25] = "tip1";
	char tip2[25] = "tip2";
	char tip3[25] = "tip3";
	char tip4[25] = "tip4";
	char adresa[25] = "adresa";
	char p = 'p', s = 's', t = 't';

	addOfferService(&o, 1, tip1, 1000, adresa, 100);
	addOfferService(&o, 2, tip2, 2000, adresa, 200);
	addOfferService(&o, 3, tip3, 1500, adresa, 350);
	addOfferService(&o, 4, tip4, 500, adresa, 50);

	offersList sortedO1 = createOList();
	sortListByCmp(&o, &sortedO1, p);
	assert(sortedO1.List[0].id == 3);
	free(sortedO1.List);

	offersList sortedO2 = createOList();
	sortListByCmp(&o, &sortedO2, s);
	assert(sortedO2.List[0].id == 4);
	free(sortedO2.List);

	offersList sortedO3 = createOList();
	sortListByCmp(&o, &sortedO3, t);
	assert(sortedO3.List[0].id == 1);
	free(sortedO3.List);

	free(o.List);
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
