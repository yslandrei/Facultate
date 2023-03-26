#include <stdlib.h>
#include <string.h>
#include "List.h"
#pragma warning(disable:4996)

offer* createOffer(int id, char* type, int surface, char* adress, int price) {
	offer* Offer = malloc(sizeof(offer));

	(*Offer).id = id;
	(*Offer).type = (char*) malloc((strlen(type) + 1) * sizeof(char));
	(*Offer).surface = surface;
	(*Offer).adress = (char*) malloc((strlen(adress) + 1) * sizeof(char));
	(*Offer).price = price;
	strcpy((*Offer).type, type);
	strcpy((*Offer).adress, adress);

	return Offer;
}

List createList() {
	List o = {
		.size = 0,
		.maxSize = 2,
		.arr = malloc(sizeof(void*) * o.maxSize)
	};
	return o;
}

void freeOffer(offer* Offer) {
	free(Offer->type);
	free(Offer->adress);
	free(Offer);
}

void freeOList(List* o) {
	for (int i = 0; i < o->size; i++)
		freeOffer((offer*) o->arr[i]);
	free(o->arr);
}