int addOfferService(offer* oList, int* oListLen, int id, char* type, int surface, char* adress, int price);

int popOfferService(offer* oList, int* oListLen, int oId);

int modOfferService(offer* oList, int* oListLen, int oldId, int id, char* type, int surface, char* adress, int price);

int cmpByPriceAndType(const offer offer1, const offer offer2);

offer* getSortedListByPriceAndType(offer* oList, int oListLen);

int stringToNumber(char* string);

offer* getFilteredListByCriteria(offer* oList, int oListLen, char* input, int* filteredOListLen);