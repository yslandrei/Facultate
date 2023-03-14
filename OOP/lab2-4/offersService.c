#include <string.h>
#include <stdlib.h>
#include "offer.h"
#include "offersRepository.h"
#pragma warning(disable : 4996)

int addOfferService(offer* oList, int* oListLen, int id, char* type, int surface, char* adress, int price) {
	//TODO: Validation
	offer newOffer = {
		.id = id,
		.surface = surface,
		.price = price
	};
	strcpy(newOffer.type, type);
	strcpy(newOffer.adress, adress);

	addOffer(oList, oListLen, newOffer);
	return 0;
}

int popOfferService(offer* oList, int* oListLen, int oldId) {
	//TODO: Validation
	offer oldOffer;
	for (int i = 0; i <= *oListLen; i++)
		if (oList[i].id == oldId)
			oldOffer = oList[i];

	popOffer(oList, oListLen, oldOffer);
	return 0;
}

int modOfferService(offer* oList, int* oListLen, int oldId, int id, char* type, int surface, char* adress, int price) {
	//TODO: Validation
	offer oldOffer;
	for (int i = 0; i <= *oListLen; i++)
		if (oList[i].id == oldId)
			oldOffer = oList[i];

	offer newOffer = {
		.id = id,
		.surface = surface,
		.price = price
	};
	strcpy(newOffer.type, type);
	strcpy(newOffer.adress, adress);

	modOffer(oList, oListLen, oldOffer, newOffer);
	return 0;
}

int cmpByPriceAndType(const offer* offer1, const offer* offer2) {
	if ((*offer1).price == (*offer2).price)
		return strcmp((*offer1).type, (*offer2).type) < 0;
	
	return (*offer1).price > (*offer2).price;
}

offer* getSortedListByPriceAndType(offer* oList, int oListLen) {
	offer sortedOList[100];
	for (int i = 0; i < oListLen; i++) {
		sortedOList[i] = oList[i];
	}

	qsort(sortedOList, oListLen, sizeof(offer), cmpByPriceAndType);
	return sortedOList;
}

int stringToNumber(char* string) {
	int stringLen = strlen(string);
	int number = 0;

	for (int i = 0; i < stringLen; i++)
		number = number * 10 + (int)(string[i] - '0');

	return number;
}

offer* getFilteredListByCriteria(offer* oList, int oListLen, char* criteria, int* filteredOListLen) {
	//TODO: Validation
	offer filteredOList[100];
	int correctOList[100];
	for (int i = 0; i < oListLen; i++)
		correctOList[i] = 1;

	char* parser = strtok(criteria, " ");
	while (parser != NULL) {
		for (int i = 0; i < oListLen; i ++) {
			if (strncmp(parser + 1, ">=", 2) == 0) {
				if (parser[0] == 's' && !(oList[i].surface >= stringToNumber(parser + 3))) correctOList[i] = 0;
				else if (parser[0] == 'p' && !(oList[i].price >= stringToNumber(parser + 3))) correctOList[i] = 0;
				else if (parser[0] == 't' && !(strcmp(oList[i].type, parser + 3) >= 0)) correctOList[i] = 0;
			}
			
			else if (strncmp(parser + 1, "<=", 2) == 0) {
				if (parser[0] == 's' && !(oList[i].surface <= stringToNumber(parser + 3))) correctOList[i] = 0;
				else if (parser[0] == 'p' && !(oList[i].price <= stringToNumber(parser + 3))) correctOList[i] = 0;
				else if (parser[0] == 't' && !(strcmp(oList[i].type, parser + 3) <= 0)) correctOList[i] = 0;
			}

			else if (parser[1] == '>') {
				if (parser[0] == 's' && !(oList[i].surface > stringToNumber(parser + 2))) correctOList[i] = 0;
				else if (parser[0] == 'p' && !(oList[i].price > stringToNumber(parser + 2))) correctOList[i] = 0;
				else if (parser[0] == 't' && !(strcmp(oList[i].type, parser + 2) > 0)) correctOList[i] = 0;
			}

			else if (parser[1] == '<') {
				if (parser[0] == 's' && !(oList[i].surface < stringToNumber(parser + 2))) correctOList[i] = 0;
				else if (parser[0] == 'p' && !(oList[i].price < stringToNumber(parser + 2))) correctOList[i] = 0;
				else if (parser[0] == 't' && !(strcmp(oList[i].type, parser + 2) < 0)) correctOList[i] = 0;
			}

			else if (parser[1] == '=') {
				if (parser[0] == 's' && !(oList[i].surface == stringToNumber(parser + 2))) correctOList[i] = 0;
				else if (parser[0] == 'p' && !(oList[i].price == stringToNumber(parser + 2))) correctOList[i] = 0;
				else if (parser[0] == 't' && !(strcmp(oList[i].type, parser + 2) == 0)) correctOList[i] = 0;
			}
		}
		parser = strtok(NULL, " ");
	}

	for (int i = 0; i < oListLen; i++)
		if (correctOList[i])
			filteredOList[(*filteredOListLen)++] = oList[i];

	return filteredOList;
}

