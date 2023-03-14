int addOfferService(offer* oList, int* oListLen, int id, std::string type, int surface, std::string adress, int price);

int popOfferService(offer* oList, int* oListLen, int oId);

int modOfferService(offer* oList, int* oListLen, int oldId, int id, std::string type, int surface, std::string adress, int price);

int cmpByPriceAndType(const offer offer1, const offer offer2);

void sortListByPriceAndType(offer* oList, int oListLen, offer* sortedOList);

int stringToNumber(std::string string);

void filterListByCriteria(offer* oList, int oListLen, std::string criteria, offer* filteredOList, int* filteredOListLen);