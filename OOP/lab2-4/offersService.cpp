#include <string.h>
#include <stdlib.h>
#include "offer.h"
#include "offersList.h"
#include "offersRepository.h"
#pragma warning(disable : 4996)

int addOfferService(offersList* o, int id, const std::string type, int surface, const std::string adress, int price) {
	//TODO: Validation
	offer newOffer = {
		.id = id,
		.type = type,
		.surface = surface,
		.adress = adress,
		.price = price
	};

	addOffer(o, newOffer);
	return 0;
}

int popOfferService(offersList* o, int oldId) {
	//TODO: Validation
	offer oldOffer;
	for (int i = 0; i <= o->size; i++)
		if (o->List[i].id == oldId)
			oldOffer = o->List[i];

	popOffer(o, oldOffer);
	return 0;
}

int modOfferService(offersList* o, int oldId, int id, std::string type, int surface, std::string adress, int price) {
	//TODO: Validation
	offer oldOffer;
	for (int i = 0; i <= o->size; i++)
		if (o->List[i].id == oldId)
			oldOffer = o->List[i];

	offer newOffer = {
		.id = id,
		.type = type,
		.surface = surface,
		.adress = adress,
		.price = price
	};

	modOffer(o, oldOffer, newOffer);
	return 0;
}

int cmpByPriceAndType(const void* o1, const void* o2) {
	offer* offer1 = (offer*)o1;
	offer* offer2 = (offer*) o2;

	if ((*offer1).price == (*offer2).price)
		return (*offer1).type < (*offer2).type;
	return (*offer1).price > (*offer2).price;
}

void sortListByPriceAndType(offersList* o, offersList* sortedO) {
	for (int i = 0; i < o->size; i++)
		addOffer(sortedO, o->List[i]);

	qsort(sortedO->List, sortedO->size, sizeof(offer), cmpByPriceAndType);
}

int stringToNumber(std::string str) {
	int number = 0;
	for (int i = 0; i < str.length(); i++)
		number = number * 10 + (int)(str[i] - '0');

	return number;
}

void filterListByCriteria(offersList* o, offersList* filteredO, std::string criteria) {
	//TODO: Validation
	int correctOList[100];
	for (int i = 0; i < o->size; i++)
		correctOList[i] = 1;

	char* criteriaCStr = strdup(criteria.c_str());
	char* parser = strtok(criteriaCStr, " ");
	while (parser != NULL) {
		for (int i = 0; i < o->size; i ++) {
			if (strncmp(parser + 1, ">=", 2) == 0) {
				if (parser[0] == 's' && !(o->List[i].surface >= stringToNumber(parser + 3))) correctOList[i] = 0;
				else if (parser[0] == 'p' && !(o->List[i].price >= stringToNumber(parser + 3))) correctOList[i] = 0;
				else if (parser[0] == 't' && !(o->List[i].type >= parser + 3)) correctOList[i] = 0;
			}
			
			else if (strncmp(parser + 1, "<=", 2) == 0) {
				if (parser[0] == 's' && !(o->List[i].surface <= stringToNumber(parser + 3))) correctOList[i] = 0;
				else if (parser[0] == 'p' && !(o->List[i].price <= stringToNumber(parser + 3))) correctOList[i] = 0;
				else if (parser[0] == 't' && !(o->List[i].type <= parser + 3)) correctOList[i] = 0;
			}

			else if (parser[1] == '>') {
				if (parser[0] == 's' && !(o->List[i].surface > stringToNumber(parser + 2))) correctOList[i] = 0;
				else if (parser[0] == 'p' && !(o->List[i].price > stringToNumber(parser + 2))) correctOList[i] = 0;
				else if (parser[0] == 't' && !(o->List[i].type > parser + 2)) correctOList[i] = 0;
			}

			else if (parser[1] == '<') {
				if (parser[0] == 's' && !(o->List[i].surface < stringToNumber(parser + 2))) correctOList[i] = 0;
				else if (parser[0] == 'p' && !(o->List[i].price < stringToNumber(parser + 2))) correctOList[i] = 0;
				else if (parser[0] == 't' && !(o->List[i].type < parser)) correctOList[i] = 0;
			}

			else if (parser[1] == '=') {
				if (parser[0] == 's' && !(o->List[i].surface == stringToNumber(parser + 2))) correctOList[i] = 0;
				else if (parser[0] == 'p' && !(o->List[i].price == stringToNumber(parser + 2))) correctOList[i] = 0;
				else if (parser[0] == 't' && (o->List[i].type != parser + 2)) correctOList[i] = 0;
			}
		}
		parser = strtok(NULL, " ");
	}

	for (int i = 0; i < o->size; i++)
		if (correctOList[i])
			addOffer(filteredO, o->List[i]);
}

