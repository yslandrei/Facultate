#include "List.h"
#pragma warning(disable:4996)

offer* createOffer(int id, char* type, int surface, char* adress, int price);

List createList();

void freeOffer(offer* Offer);

void freeOList(List* o);