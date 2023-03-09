#include "offer.h"

int addOffer(offer* oList, int* oListLen, offer newOffer) {
	for (int i = 0; i < *oListLen; i++)
		if (oList[i].id == newOffer.id)
			return -1; // Offer already exists

	oList[(*oListLen)++] = newOffer;
	return 0;
}

int popOffer(offer* oList, int* oListLen, offer oldOffer) {
	for (int i = 0; i < *oListLen; i++)
		if (oList[i].id == oldOffer.id) {
			for (int j = i; j < *oListLen - 1; j++)
				oList[j] = oList[j + 1];
			(*oListLen)--;
			return 0;
		}
	
	return -1; // Offer doesn't exist
	
}

int modOffer(offer* oList, int* oListLen, offer oldOffer, offer newOffer) {
	for (int i = 0; i < *oListLen; i++)
		if (oList[i].id == oldOffer.id) {
			oList[i] = newOffer;
			return 0;
		}

	return -1; // Offer doesn't exist
	
}
