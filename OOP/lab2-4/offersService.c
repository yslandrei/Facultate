#include <string.h>
#include <stdlib.h>
#include "offer.h"
#include "List.h"
#include "utils.h"
#include "offersRepository.h"
#pragma warning(disable : 4996)

int addOfferService(List* o, int id, char* type, int surface, char* adress, int price) {
	offer* newOffer = createOffer(id, type, surface, adress, price);

	return addOffer(o, newOffer);
}

int popOfferService(List* o, int oldId) {
	offer* oldOffer = NULL;
	for (int i = 0; i < o->size; i++)
		if ((*(offer*) o->arr[i]).id == oldId)
			oldOffer = (offer*) o->arr[i];

	return popOffer(o, oldOffer);
}

int modOfferService(List* o, int oldId, int id, char* type, int surface, char* adress, int price) {
	offer* oldOffer = NULL;
	for (int i = 0; i < o->size; i++)
		if ((*(offer*)o->arr[i]).id == oldId)
			oldOffer = (offer*) o->arr[i];

	offer* newOffer = createOffer(id, type, surface, adress, price);
	return modOffer(o, oldOffer, newOffer);
}

int cmpDescByPrice(const void* a, const void* b) {
	int price1 = (*(offer**) a)->price;
	int price2 = (*(offer**) b)->price;
	return price2 - price1;
}

int cmpAscBySurface(const void* a, const void* b) {
	int surface1 = (*(offer**) a)->surface;
	int surface2 = (*(offer**) b)->surface;
	return surface1 - surface2;
}

int cmpAscByType(const void* a, const void* b) {
	char type1[25] = { 0 };
	char type2[25] = { 0 };
	strcpy(type1, (*(offer**) a)->type);
	strcpy(type2, (*(offer**) b)->type);
	return (strcmp(type1, type2) > 0);
}

void sortListByCmp(List* o, List* sortedO, char cmp) {
	for (int i = 0; i < o->size; i++)
		addOffer(sortedO, (offer*) o->arr[i]);

	if (cmp == 'p')
		qsort(sortedO->arr, sortedO->size, sizeof(void*), cmpDescByPrice);
	else if (cmp == 's')
		qsort(sortedO->arr, sortedO->size, sizeof(void*), cmpAscBySurface);
	else if (cmp == 't')
		qsort(sortedO->arr, sortedO->size, sizeof(void*), cmpAscByType);
}


int stringToNumber(char* string) {
	size_t stringLen = strlen(string);
	int number = 0;

	for (int i = 0; i < stringLen; i++)
		number = number * 10 + (int)(string[i] - '0');

	return number;
}


void filterListByCriteria(List* o, List* filteredO, char* criteria) {
	int correctOList[100] = {0};
	for (int i = 0; i < o->size; i++)
		correctOList[i] = 1;

	char* parser = strtok(criteria, " ");
	while (parser != NULL) {
		for (int i = 0; i < o->size; i ++) {
			if (strncmp(parser + 1, ">=", 2) == 0) {
				if (parser[0] == 's' && !((*(offer*) o->arr[i]).surface >= stringToNumber(parser + 3))) correctOList[i] = 0;
				else if (parser[0] == 'p' && !((*(offer*) o->arr[i]).price >= stringToNumber(parser + 3))) correctOList[i] = 0;
				else if (parser[0] == 't' && !(strcmp((*(offer*) o->arr[i]).type, parser + 3) >= 0)) correctOList[i] = 0;
			}
			
			else if (strncmp(parser + 1, "<=", 2) == 0) {
				if (parser[0] == 's' && !((*(offer*) o->arr[i]).surface <= stringToNumber(parser + 3))) correctOList[i] = 0;
				else if (parser[0] == 'p' && !((*(offer*) o->arr[i]).price <= stringToNumber(parser + 3))) correctOList[i] = 0;
				else if (parser[0] == 't' && !(strcmp((*(offer*) o->arr[i]).type, parser + 3) <= 0)) correctOList[i] = 0;
			}

			else if (parser[1] == '>') {
				if (parser[0] == 's' && !((*(offer*) o->arr[i]).surface > stringToNumber(parser + 2))) correctOList[i] = 0;
				else if (parser[0] == 'p' && !((*(offer*) o->arr[i]).price > stringToNumber(parser + 2))) correctOList[i] = 0;
				else if (parser[0] == 't' && !(strcmp((*(offer*) o->arr[i]).type, parser + 2) > 0)) correctOList[i] = 0;
			}

			else if (parser[1] == '<') {
				if (parser[0] == 's' && !((*(offer*) o->arr[i]).surface < stringToNumber(parser + 2))) correctOList[i] = 0;
				else if (parser[0] == 'p' && !((*(offer*) o->arr[i]).price < stringToNumber(parser + 2))) correctOList[i] = 0;
				else if (parser[0] == 't' && !(strcmp((*(offer*) o->arr[i]).type, parser + 2) < 0)) correctOList[i] = 0;
			}

			else if (parser[1] == '=') {
				if (parser[0] == 's' && !((*(offer*) o->arr[i]).surface == stringToNumber(parser + 2))) correctOList[i] = 0;
				else if (parser[0] == 'p' && !((*(offer*) o->arr[i]).price == stringToNumber(parser + 2))) correctOList[i] = 0;
				else if (parser[0] == 't' && !(strcmp((*(offer*) o->arr[i]).type, parser + 2) == 0)) correctOList[i] = 0;
			}
		}
		parser = strtok(NULL, " ");
	}

	for (int i = 0; i < o->size; i++)
		if (correctOList[i])
			addOffer(filteredO, (offer*) o->arr[i]);
}

