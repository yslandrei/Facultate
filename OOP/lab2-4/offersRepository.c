#include <stdlib.h>
#include "offer.h"
#include "offersList.h"
#include "utils.h"

int addOffer(offersList* o, offer newOffer) {
	for (int i = 0; i < o->size; i++)
		if (o->List[i].id == newOffer.id) {
			freeOffer(&newOffer);
			return -1; // Offer already exists
		}
	
	if (o->size == o->maxSize) { // Resizing dynamic array
		o->maxSize = o->maxSize * 2;
		offer* auxO = malloc(o->maxSize * sizeof(offer));

		for (int i = 0; i < o->size; i++)
			auxO[i] = o->List[i];

		free(o->List);
		o->List = auxO;
	}
	
	o->List[o->size] = newOffer;
	o->size++;
	return 0;
}

int popOffer(offersList* o, offer oldOffer) {
	for (int i = 0; i < o->size; i++)
		if (o->List[i].id == oldOffer.id) {
			for (int j = i; j < o->size - 1; j++)
				o->List[j] = o->List[j + 1];
			o->size--;
			freeOffer(&oldOffer);
			return 0;
		}

	return -1; // Offer doesn't exist
}

int modOffer(offersList* o, offer oldOffer, offer newOffer) {
	for (int i = 0; i < o->size; i++)
		if (o->List[i].id == oldOffer.id) {
			o->List[i] = newOffer;
			freeOffer(&oldOffer);
			return 0;
		}

	freeOffer(&newOffer);
	return -1; // Offer doesn't exist
}
