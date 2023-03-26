#pragma once

int addOfferService(List* o, int id, char* type, int surface, char* adress, int price);

int popOfferService(List* o, int oId);

int modOfferService(List* o, int oldId, int id, char* type, int surface, char* adress, int price);

int cmpDescByPrice(const void* o1, const void* o2);

int cmpAscBySurface(const void* o1, const void* o2);

int cmpAscByType(const void* o1, const void* o2);

void sortListByCmp(List* o, List* sortedO, char cmp);

int stringToNumber(char* string);

void filterListByCriteria(List* o, List* filteredO, char* criteria);