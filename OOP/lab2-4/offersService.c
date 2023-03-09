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
	if ((*offer1).price == (*offer2).price) {
		if (strcmp((*offer1).type, (*offer2).type) > 0)
			return 0;
		return 1;
	}
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

offer* getFilteredListByCriteria(offer* oList, int oListLen, char* input, int* filteredOListLen) {
	//TODO: Validation
	offer filteredOList[100];

	char criteria = input[0];
	char sign = input[1];

	//Filter by Surface
	if (criteria == 's') {
		int number = stringToNumber(input + 2);
		for (int i = 0; i < oListLen; i++) {
			if (sign == '>' && oList[i].surface > number) 
				filteredOList[(*filteredOListLen)++] = oList[i];

			else if (sign == '<' && oList[i].surface < number)
				filteredOList[(*filteredOListLen)++] = oList[i];
		}
	}

	//Filter by Price
	else if (criteria == 'p') {
		int number = stringToNumber(input + 2);
		for (int i = 0; i < oListLen; i++) {
			if (sign == '>' && oList[i].price > number)
				filteredOList[(*filteredOListLen)++] = oList[i];

			else if (sign == '<' && oList[i].price < number)
				filteredOList[(*filteredOListLen)++] = oList[i];
		}
	}

	//Filter by Type
	else if (criteria == 't') {
		char* type = input + 2;
		for (int i = 0; i < oListLen; i++) {
			if (sign == '=' && strcmp(type, oList[i].type) == 0)
				filteredOList[(*filteredOListLen)++] = oList[i];
		}
	}

	return filteredOList;
}

