#include <stdlib.h>
#include "offer.h"
#include "List.h"
#include "utils.h"

int addOffer(List* o, offer* newOffer) {
	for (int i = 0; i < o->size; i++)
		if ((*(offer*) o->arr[i]).id == (*newOffer).id) {
			freeOffer(newOffer);
			return -1; // Offer already exists
		}
	
	if (o->size == o->maxSize) { // Resizing dynamic array
		o->maxSize = o->maxSize * 2;
		void** auxO = malloc(o->maxSize * sizeof(void*));

		for (int i = 0; i < o->size; i++)
			auxO[i] = o->arr[i];

		free(o->arr);
		o->arr = auxO;
	}
	
	o->arr[o->size] = newOffer;
	o->size++;
	return 0;
}

int popOffer(List* o, offer* oldOffer) {
	for (int i = 0; i < o->size; i++)
		if ((*(offer*) o->arr[i]).id == (*oldOffer).id) {
			for (int j = i; j < o->size - 1; j++)
				o->arr[j] = o->arr[j + 1];
			o->size--;
			freeOffer(oldOffer);
			return 0;
		}

	return -1; // Offer doesn't exist
}

int modOffer(List* o, offer* oldOffer, offer* newOffer) {
	for (int i = 0; i < o->size; i++)
		if ((*(offer*) o->arr[i]).id == (*oldOffer).id) {
			o->arr[i] = newOffer;
			freeOffer(oldOffer);
			return 0;
		}

	freeOffer(newOffer);
	return -1; // Offer doesn't exist
}
