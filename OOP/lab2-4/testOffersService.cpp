#include <assert.h>
#include <string.h>
#include "offer.h"
#include "offersRepository.h"
#include "offersService.h"
#pragma warning(disable:4996)

void testAddOfferService() {
	offersList o;
	std::string tip = "tip";
	std::string adresa = "adresa";

	assert(addOfferService(&o, 1, tip, 1000, adresa, 100) == 0);
	assert(o.List[0].id == 1);
	assert(o.List[0].type == "tip");
	assert(o.List[0].surface == 1000);
	assert(o.List[0].adress == "adresa");
	assert(o.List[0].price == 100);
}

void testPopOfferService() {
	offersList o;
	std::string tip = "tip";
	std::string adresa = "adresa";

	addOfferService(&o, 1, tip, 1000, adresa, 100);
	assert(popOfferService(&o, 1) == 0);
	assert(o.size == 0);
}

void testModOfferService() {
	offersList o;
	std::string tip = "tip";
	std::string adresa = "adresa";

	addOfferService(&o, 1, tip, 1000, adresa, 100);
	assert(modOfferService(&o, 1, 2, tip, 1000, adresa, 100) == 0);
	assert(o.List[0].id == 2);
}

void testGetSortedListByPriceAndType() {
	offersList o;
	std::string tip = "tip";
	std::string tipul = "tipul";
	std::string adresa = "adresa";

	addOfferService(&o, 1, tip, 1000, adresa, 100);
	addOfferService(&o, 2, tipul, 1000, adresa, 100);
	addOfferService(&o, 3, tip, 1000, adresa, 50);

	offersList sortedO;
	sortListByPriceAndType(&o, &sortedO);
	assert(sortedO.List[0].id == 3);
	assert(sortedO.List[1].id == 2);
	assert(sortedO.List[2].id == 1);
}

void testGetFilteredListByCriteria() {
	offersList o;
	std::string tip1 = "tip1";
	std::string tip2 = "tip2";
	std::string tip3 = "tip3";
	std::string adresa = "adresa";

	addOfferService(&o, 1, tip1, 1000, adresa, 100);
	addOfferService(&o, 2, tip2, 800, adresa, 150);
	addOfferService(&o, 3, tip3, 2000, adresa, 300);

	offersList filteredO1;
	std::string input1 = "p>=150 s<=2000 t>=tip";
	filterListByCriteria(&o, &filteredO1, input1);
	assert(filteredO1.size == 2);

	offersList filteredO2;
	std::string input2 = "p<300 s>900 t=tip1";
	filterListByCriteria(&o, &filteredO2, input2);
	assert(filteredO2.size == 1);
}