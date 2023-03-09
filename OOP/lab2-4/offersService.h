int addOfferService(offer* oList, int* oListLen, int id, char* type, int surface, char* adress, int price);

int popOfferService(offer* oList, int* oListLen, int id, char* type, int surface, char* adress, int price);

int modOfferService(offer* oList, int* oListLen, int oldId, char* oldType, int oldSurface, char* oldAdress, int oldPrice, int newId, char* newType, int newSurface, char* newAdress, int newPrice);

int cmpByPriceAndType(const offer offer1, const offer offer2);

offer* getSortedListByPriceAndType(offer* oList, int* oListLen);

offer* getFilteredListByCriteria(offer* oList, int oListLen, char* input);