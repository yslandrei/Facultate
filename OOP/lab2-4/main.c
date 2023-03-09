#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "offer.h"
#include "offersRepository.h"
#include "offersService.h"
#pragma warning(disable:4996)

int main() {

	int oListLen = 0;
	offer oList[100];
	offer newOffer;
	newOffer.id = 1;
	strcpy(newOffer.type, "tipul");
	strcpy(newOffer.adress, "adresa");
	newOffer.price = 1000000;
	newOffer.surface = 500;
	offer newerOffer = newOffer;
	newerOffer.id = 3;
	newerOffer.price = 500;


	addOffer(oList, &oListLen, newOffer);
	modOffer(oList, &oListLen, newOffer, newerOffer);
	addOffer(oList, &oListLen, newOffer);

	strcpy(newerOffer.type, "tipul gay");
	newerOffer.id = 2;
	addOffer(oList, &oListLen, newerOffer);

	for (int i = 0; i < oListLen; i++) {
		printf("%d, %d, %s\n", oList[i].id, oList[i].price, oList[i].type);
	}
	
	//offer* sortedOList = getSortedListByPriceAndType(oList, oListLen);
	offer* sortedOList = getFilteredListByCriteria(oList, oListLen, "t=tipul gay");

	printf("\n");
	for (int i = 0; i < 1; i++) {
		printf("%d, %d, %s\n", sortedOList[i].id, sortedOList[i].price, sortedOList[i].type);
	}
	
	return 0;
}