#include <stdio.h>
#include "offer.h"
#pragma once

typedef struct {
	int size;
	int maxSize;
	offer* List;
	//offer* List = (offer*)malloc(o.maxSize, sizeof(offer))
	//offer* List = new offer[maxSize];
	//offer List[100];

}offersList;