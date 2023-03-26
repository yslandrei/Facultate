#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "offer.h"
#include "List.h"
#include "utils.h"
#include "offersRepository.h"
#include "offersService.h"
#pragma warning(disable:4996)

void testAddOfferService() {
	List o = createList();
	char tip[25] = "tip";
	char adresa[25] = "adresa";

	assert(addOfferService(&o, 1, tip, 1000, adresa, 100) == 0);
	assert((*(offer*) o.arr[0]).id == 1);
	assert(strcmp((*(offer*) o.arr[0]).type, "tip") == 0);
	assert((*(offer*) o.arr[0]).surface == 1000);
	assert(strcmp((*(offer*) o.arr[0]).adress, "adresa") == 0);
	assert((*(offer*) o.arr[0]).price == 100);

	freeOList(&o);
}

void testPopOfferService() {
	List o = createList();
	char tip[25] = "tip";
	char adresa[25] = "adresa";

	addOfferService(&o, 1, tip, 1000, adresa, 100);
	assert(popOfferService(&o, 1) == 0);
	assert(o.size == 0);

	freeOList(&o);
}

void testModOfferService() {
	List o = createList();
	char tip[25] = "tip";
	char adresa[25] = "adresa";

	addOfferService(&o, 1, tip, 1000, adresa, 100);
	assert(modOfferService(&o, 1, 2, tip, 1000, adresa, 100) == 0);
	assert((*(offer*) o.arr[0]).id == 2);

	freeOList(&o);
}

void testGetSortedListByPriceAndType() {
	List o = createList();
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

	List sortedO1 = createList();
	sortListByCmp(&o, &sortedO1, p);
	assert((*(offer*) sortedO1.arr[0]).id == 3);
	free(sortedO1.arr);

	List sortedO2 = createList();
	sortListByCmp(&o, &sortedO2, s);
	assert((*(offer*)sortedO2.arr[0]).id == 4);
	free(sortedO2.arr);

	List sortedO3 = createList();
	sortListByCmp(&o, &sortedO3, t);
	assert((*(offer*)sortedO3.arr[0]).id == 1);
	free(sortedO3.arr);

	freeOList(&o);
}

void testGetFilteredListByCriteria() {
	List o = createList();
	char tip1[25] = "tip1";
	char tip2[25] = "tip2";
	char tip3[25] = "tip3";
	char adresa[25] = "adresa";

	addOfferService(&o, 1, tip1, 1000, adresa, 100);
	addOfferService(&o, 2, tip2, 800, adresa, 150);
	addOfferService(&o, 3, tip3, 2000, adresa, 300);

	List filteredO1 = createList();
	char input1[25] = "s<=2000 p>=150 t>=tip";
	filterListByCriteria(&o, &filteredO1, input1);
	assert(filteredO1.size == 2);
	free(filteredO1.arr);


	List filteredO2 = createList();
	char input2[25] = "s>900 p<300 t=tip1";
	filterListByCriteria(&o, &filteredO2, input2);
	assert(filteredO2.size == 1);
	free(filteredO2.arr);

	freeOList(&o);
}
