#pragma once

int addOfferService(offersList* o, int id, const std::string type, int surface, const std::string adress, int price);

int popOfferService(offersList* o, int oId);

int modOfferService(offersList* o, int oldId, int id, std::string type, int surface, std::string adress, int price);

int cmpByPriceAndType(const void* o1, const void* o2);

void sortListByPriceAndType(offersList* o, offersList* sortedO);

int stringToNumber(std::string string);

void filterListByCriteria(offersList* o, offersList* filteredO, std::string criteria);