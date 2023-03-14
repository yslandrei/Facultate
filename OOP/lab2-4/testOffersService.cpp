#include <assert.h>
#include <string.h>
#include "offer.h"
#include "offersRepository.h"
#include "offersService.h"
#pragma warning(disable:4996)

void testAddOfferService() {
	int oListLen = 0;
	offer oList[100];
	std::string tip = "tip";
	std::string adresa = "adresa";

	assert(addOfferService(oList, &oListLen, 1, tip, 1000, adresa, 100) == 0);

	assert(oList[0].id == 1);
	assert(oList[0].type == "tip");
	assert(oList[0].surface == 1000);
	assert(oList[0].adress == "adresa");
	assert(oList[0].price == 100);
}

void testPopOfferService() {
	int oListLen = 0;
	offer oList[100];
	std::string tip = "tip";
	std::string adresa = "adresa";

	addOfferService(oList, &oListLen, 1, tip, 1000, adresa, 100);
	assert(popOfferService(oList, &oListLen, 1) == 0);
	assert(oListLen == 0);
}

void testModOfferService() {
	int oListLen = 0;
	offer oList[100];
	std::string tip = "tip";
	std::string adresa = "adresa";

	addOfferService(oList, &oListLen, 1, tip, 1000, adresa, 100);
	assert(modOfferService(oList, &oListLen, 1, 2, tip, 1000, adresa, 100) == 0);
	assert(oList[0].id == 2);
}

void testGetSortedListByPriceAndType() {
	int oListLen = 0;
	offer oList[100];
	std::string tip = "tip";
	std::string tipul = "tipul";
	std::string adresa = "adresa";

	addOfferService(oList, &oListLen, 1, tip, 1000, adresa, 100);
	addOfferService(oList, &oListLen, 2, tipul, 1000, adresa, 100);
	addOfferService(oList, &oListLen, 3, tip, 1000, adresa, 50);

	offer sortedOList[100];	
	sortListByPriceAndType(oList, oListLen, sortedOList);
	assert(sortedOList[0].id == 3);
	assert(sortedOList[1].id == 2);
	assert(sortedOList[2].id == 1);

}

void testGetFilteredListByCriteria() {
	int oListLen = 0;
	offer oList[100];
	int filteredOListLen = 0;
	offer filteredOList[100];

	std::string tip1 = "tip1";
	std::string tip2 = "tip2";
	std::string tip3 = "tip3";
	std::string adresa = "adresa";

	addOfferService(oList, &oListLen, 1, tip1, 1000, adresa, 100);
	addOfferService(oList, &oListLen, 2, tip2, 800, adresa, 150);
	addOfferService(oList, &oListLen, 3, tip3, 2000, adresa, 300);

	std::string input1 = "p>=150 s<=2000 t>=tip";
	filteredOListLen = 0;
	filterListByCriteria(oList, oListLen, input1, filteredOList, &filteredOListLen);
	assert(filteredOListLen == 2);

	std::string input2 = "p<300 s>900 t=tip1";
	filteredOListLen = 0;
	filterListByCriteria(oList, oListLen, input2, filteredOList, &filteredOListLen);
	assert(filteredOListLen == 1);
}

