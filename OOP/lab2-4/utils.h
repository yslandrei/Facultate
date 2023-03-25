#include "offersList.h"
#pragma warning(disable:4996)

offer createOffer(int id, char* type, int surface, char* adress, int price);

offersList createOList();

void freeOffer(offer* Offer);

void freeOList(offersList* o);