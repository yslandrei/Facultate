#include "offersList.h"

offersList createOList() {
	 offersList o;
	 o.size = 0;
	 o.maxSize = 2;
	 o.List = malloc(o.maxSize * sizeof(offer));
	 return o;
}