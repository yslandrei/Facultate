#include <string.h>
#include <stdlib.h>
#include "offer.h"
#include "offersRepository.h"
#pragma warning(disable : 4996)

int addOfferService(offer* oList, int* oListLen, int id, std::string type, int surface, std::string adress, int price) {
	//TODO: Validation
	offer newOffer = {
		.id = id,
		.type = type,
		.surface = surface,
		.adress = adress,
		.price = price
	};

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

int modOfferService(offer* oList, int* oListLen, int oldId, int id, std::string type, int surface, std::string adress, int price) {
	//TODO: Validation
	offer oldOffer;
	for (int i = 0; i <= *oListLen; i++)
		if (oList[i].id == oldId)
			oldOffer = oList[i];

	offer newOffer = {
		.id = id,
		.type = type,
		.surface = surface,
		.adress = adress,
		.price = price
	};

	modOffer(oList, oListLen, oldOffer, newOffer);
	return 0;
}

int cmpByPriceAndType(const void* o1, const void* o2) {
	offer* offer1 = (offer*)o1;
	offer* offer2 = (offer*) o2;

	if ((*offer1).price == (*offer2).price)
		return (*offer1).type < (*offer2).type;
	return (*offer1).price > (*offer2).price;
}

void sortListByPriceAndType(offer* oList, int oListLen, offer* sortedOList) {
	for (int i = 0; i < oListLen; i++) {
		sortedOList[i] = oList[i];
	}

	qsort(sortedOList, oListLen, sizeof(offer), cmpByPriceAndType);
}

int stringToNumber(std::string str) {
	int number = 0;
	for (int i = 0; i < str.length(); i++)
		number = number * 10 + (int)(str[i] - '0');

	return number;
}

void filterListByCriteria(offer* oList, int oListLen, std::string criteria, offer* filteredOList, int* filteredOListLen) {
	//TODO: Validation
	int correctOList[100];

	for (int i = 0; i < oListLen; i++)
		correctOList[i] = 1;

	char* criteriaCStr = strdup(criteria.c_str());
	char* parser = strtok(criteriaCStr, " ");
	while (parser != NULL) {
		for (int i = 0; i < oListLen; i ++) {
			if (strncmp(parser + 1, ">=", 2) == 0) {
				if (parser[0] == 's' && !(oList[i].surface >= stringToNumber(parser + 3))) correctOList[i] = 0;
				else if (parser[0] == 'p' && !(oList[i].price >= stringToNumber(parser + 3))) correctOList[i] = 0;
				else if (parser[0] == 't' && !(oList[i].type >= parser + 3)) correctOList[i] = 0;
			}
			
			else if (strncmp(parser + 1, "<=", 2) == 0) {
				if (parser[0] == 's' && !(oList[i].surface <= stringToNumber(parser + 3))) correctOList[i] = 0;
				else if (parser[0] == 'p' && !(oList[i].price <= stringToNumber(parser + 3))) correctOList[i] = 0;
				else if (parser[0] == 't' && !(oList[i].type <= parser + 3)) correctOList[i] = 0;
			}

			else if (parser[1] == '>') {
				if (parser[0] == 's' && !(oList[i].surface > stringToNumber(parser + 2))) correctOList[i] = 0;
				else if (parser[0] == 'p' && !(oList[i].price > stringToNumber(parser + 2))) correctOList[i] = 0;
				else if (parser[0] == 't' && !(oList[i].type > parser + 2)) correctOList[i] = 0;
			}

			else if (parser[1] == '<') {
				if (parser[0] == 's' && !(oList[i].surface < stringToNumber(parser + 2))) correctOList[i] = 0;
				else if (parser[0] == 'p' && !(oList[i].price < stringToNumber(parser + 2))) correctOList[i] = 0;
				else if (parser[0] == 't' && !(oList[i].type < parser)) correctOList[i] = 0;
			}

			else if (parser[1] == '=') {
				if (parser[0] == 's' && !(oList[i].surface == stringToNumber(parser + 2))) correctOList[i] = 0;
				else if (parser[0] == 'p' && !(oList[i].price == stringToNumber(parser + 2))) correctOList[i] = 0;
				else if (parser[0] == 't' && (oList[i].type != parser + 2)) correctOList[i] = 0;
			}
		}
		parser = strtok(NULL, " ");
	}

	for (int i = 0; i < oListLen; i++)
		if (correctOList[i])
			filteredOList[(*filteredOListLen)++] = oList[i];
}

