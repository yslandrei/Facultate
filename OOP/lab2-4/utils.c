#include <stdlib.h>
#include <string.h>
#include "offersList.h"
#pragma warning(disable:4996)

offer createOffer(int id, char* type, int surface, char* adress, int price) {
	offer Offer = {
		.id = id,
		.type = malloc((strlen(type) + 1) * sizeof(char)),
		.surface = surface,
		.adress = malloc((strlen(adress) + 1) * sizeof(char)),
		.price = price
	};
	strcpy(Offer.type, type);
	strcpy(Offer.adress, adress);

	return Offer;
}

offersList createOList() {
	offersList o = {
		.size = 0,
		.maxSize = 2,
		.List = malloc(sizeof(offer) * o.maxSize) 
	};

	return o;
}

void freeOffer(offer* Offer) {
	free(Offer->type);
	free(Offer->adress);
}

void freeOList(offersList* o) {
	for (int i = 0; i < o->size; i++)
		freeOffer(&(o->List[i]));
	free(o->List);
}