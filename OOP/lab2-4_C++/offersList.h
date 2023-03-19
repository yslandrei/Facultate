#include <stdio.h>
#include "offer.h"
#pragma once

typedef struct temp{
	int size = 0;
	int maxSize = 2;
	offer* List = new offer[maxSize];
	//offer List[100];
	//o.List = (offer*) calloc(o.maxSize, sizeof(offer));
}offersList;
