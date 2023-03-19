#pragma once

int addOfferService(offersList* o, int id, char* type, int surface, char* adress, int price);

int popOfferService(offersList* o, int oId);

int modOfferService(offersList* o, int oldId, int id, char* type, int surface, char* adress, int price);

int cmpByPriceAndType(const void* o1, const void* o2);

void sortListByPriceAndType(offersList* o, offersList* sortedO);

int stringToNumber(char* string);

void filterListByCriteria(offersList* o, offersList* filteredO, char* criteria);