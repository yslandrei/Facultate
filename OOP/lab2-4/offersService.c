#include <string.h>
#include <stdlib.h>
#include "offer.h"
#include "offersList.h"
#include "utils.h"
#include "offersRepository.h"
#pragma warning(disable : 4996)

int addOfferService(offersList* o, int id, char* type, int surface, char* adress, int price) {
	offer newOffer = createOffer(id, type, surface, adress, price);

	addOffer(o, newOffer);
	return 0;
}

int popOfferService(offersList* o, int oldId) {
	offer oldOffer = {0};
	for (int i = 0; i <= o->size; i++)
		if (o->List[i].id == oldId)
			oldOffer = o->List[i];

	popOffer(o, oldOffer);
	return 0;
}

int modOfferService(offersList* o, int oldId, int id, char* type, int surface, char* adress, int price) {
	offer oldOffer = { 0 };
	for (int i = 0; i <= o->size; i++)
		if (o->List[i].id == oldId)
			oldOffer = o->List[i];

	offer newOffer = createOffer(id, type, surface, adress, price);
	modOffer(o, oldOffer, newOffer);
	return 0;
}

int cmpDescByPrice(const void* o1, const void* o2) {
	offer* offer1 = (offer*) o1;
	offer* offer2 = (offer*) o2;

	return (*offer1).price < (*offer2).price;
}

int cmpAscBySurface(const void* o1, const void* o2) {
	offer* offer1 = (offer*)o1;
	offer* offer2 = (offer*)o2;

	return (*offer1).surface > (*offer2).surface;
}

int cmpAscByType(const void* o1, const void* o2) {
	offer* offer1 = (offer*)o1;
	offer* offer2 = (offer*)o2;

	return (strcmp((*offer1).type, (*offer2).type) > 0);
}

void sortListByCmp(offersList* o, offersList* sortedO, char cmp) {
	for (int i = 0; i < o->size; i++)
		addOffer(sortedO, o->List[i]);

	if (cmp == 'p')
		qsort(sortedO->List, sortedO->size, sizeof(offer), cmpDescByPrice);
	else if (cmp == 's')
		qsort(sortedO->List, sortedO->size, sizeof(offer), cmpAscBySurface);
	else if (cmp == 't')
		qsort(sortedO->List, sortedO->size, sizeof(offer), cmpAscByType);
}


int stringToNumber(char* string) {
	size_t stringLen = strlen(string);
	int number = 0;

	for (int i = 0; i < stringLen; i++)
		number = number * 10 + (int)(string[i] - '0');

	return number;
}


void filterListByCriteria(offersList* o, offersList* filteredO, char* criteria) {
	//TODO: Validation
	int correctOList[100] = {0};
	for (int i = 0; i < o->size; i++)
		correctOList[i] = 1;

	char* parser = strtok(criteria, " ");
	while (parser != NULL) {
		for (int i = 0; i < o->size; i ++) {
			if (strncmp(parser + 1, ">=", 2) == 0) {
				if (parser[0] == 's' && !(o->List[i].surface >= stringToNumber(parser + 3))) correctOList[i] = 0;
				else if (parser[0] == 'p' && !(o->List[i].price >= stringToNumber(parser + 3))) correctOList[i] = 0;
				else if (parser[0] == 't' && !(strcmp(o->List[i].type, parser + 3) >= 0)) correctOList[i] = 0;
			}
			
			else if (strncmp(parser + 1, "<=", 2) == 0) {
				if (parser[0] == 's' && !(o->List[i].surface <= stringToNumber(parser + 3))) correctOList[i] = 0;
				else if (parser[0] == 'p' && !(o->List[i].price <= stringToNumber(parser + 3))) correctOList[i] = 0;
				else if (parser[0] == 't' && !(strcmp(o->List[i].type, parser + 3) <= 0)) correctOList[i] = 0;
			}

			else if (parser[1] == '>') {
				if (parser[0] == 's' && !(o->List[i].surface > stringToNumber(parser + 2))) correctOList[i] = 0;
				else if (parser[0] == 'p' && !(o->List[i].price > stringToNumber(parser + 2))) correctOList[i] = 0;
				else if (parser[0] == 't' && !(strcmp(o->List[i].type, parser + 2) > 0)) correctOList[i] = 0;
			}

			else if (parser[1] == '<') {
				if (parser[0] == 's' && !(o->List[i].surface < stringToNumber(parser + 2))) correctOList[i] = 0;
				else if (parser[0] == 'p' && !(o->List[i].price < stringToNumber(parser + 2))) correctOList[i] = 0;
				else if (parser[0] == 't' && !(strcmp(o->List[i].type, parser + 2) < 0)) correctOList[i] = 0;
			}

			else if (parser[1] == '=') {
				if (parser[0] == 's' && !(o->List[i].surface == stringToNumber(parser + 2))) correctOList[i] = 0;
				else if (parser[0] == 'p' && !(o->List[i].price == stringToNumber(parser + 2))) correctOList[i] = 0;
				else if (parser[0] == 't' && !(strcmp(o->List[i].type, parser + 2) == 0)) correctOList[i] = 0;
			}
		}
		parser = strtok(NULL, " ");
	}

	for (int i = 0; i < o->size; i++)
		if (correctOList[i])
			addOffer(filteredO, o->List[i]);
}

