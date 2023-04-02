#include "offersService.h"

const vector<offer>& offersService::getAll() const {
	return oRepo.getAll();
}

void offersService::addOffer(const int id, const string name, const string dest, const string type, const int price) {
	offer newOffer(id, name, dest, type, price);
	validate::offer(newOffer);
	oRepo.addOffer(newOffer);
}

void offersService::popOffer(const int oldId) {
	validate::id(oldId);
	oRepo.popOffer(oldId);
}

void offersService::modOffer(const int oldId, const int id, const string name, const string dest, const string type, const int price) {
	validate::id(oldId);
	offer newOffer(id, name, dest, type, price);
	validate::offer(newOffer);
	oRepo.modOffer(oldId, newOffer);
}

const bool offersService::findOffer(const string name) const {
	validate::name(name);
	for (const auto& Offer : oRepo.getAll())
		if (Offer.getName() == name)
			return true;

	return false;
}

bool cmpByName(const offer& a, const offer& b)  {
	return a.getName() < b.getName();
}

bool cmpByDest(const offer& a, const offer& b)  {
	return a.getDest() < b.getDest();
}

bool cmpByPriceAndType(const offer& a, const offer& b)  {
	if (a.getPrice() == b.getPrice())
		return a.getType() < b.getType();
	return a.getPrice() > b.getPrice();
}

vector<offer> offersService::sortOffers(const char cmp) const {
	const vector<offer> oList = oRepo.getAll();
	vector<offer> oSortedList;
	for (const auto& Offer : oList)
		oSortedList.push_back(Offer);

	if (cmp == 'n')
		sort(oSortedList.begin(), oSortedList.end(), cmpByName);
	else if (cmp == 'd')
		sort(oSortedList.begin(), oSortedList.end(), cmpByDest);
	else if (cmp == 'p')
		sort(oSortedList.begin(), oSortedList.end(), cmpByPriceAndType);

	return oSortedList;
}

vector<offer> offersService::filterOffers(char* criteria) const {
	const vector<offer> oList = oRepo.getAll();
	bool correctOList[100] = {0};
	for (int i = 0; i < oList.size(); i++)
		correctOList[i] = 1;

	char* parser = strtok(criteria, " ");
	while (parser != NULL) {
		for (int i = 0; i < oList.size(); i++) {
			if (strncmp(parser + 1, ">=", 2) == 0) {
				if (parser[0] == 'p' && !(oList[i].getPrice() >= atoi(parser + 3))) correctOList[i] = 0;
				else if (parser[0] == 'n' && !(strcmp(oList[i].getName().c_str(), parser + 3) >= 0)) correctOList[i] = 0;
				else if (parser[0] == 'd' && !(strcmp(oList[i].getDest().c_str(), parser + 3) >= 0)) correctOList[i] = 0;
				else if (parser[0] == 't' && !(strcmp(oList[i].getType().c_str(), parser + 3) >= 0)) correctOList[i] = 0;
			}

			else if (strncmp(parser + 1, "<=", 2) == 0) {
				if (parser[0] == 'p' && !(oList[i].getPrice() <= atoi(parser + 3))) correctOList[i] = 0;
				else if (parser[0] == 'n' && !(strcmp(oList[i].getName().c_str(), parser + 3) <= 0)) correctOList[i] = 0;
				else if (parser[0] == 'd' && !(strcmp(oList[i].getDest().c_str(), parser + 3) <= 0)) correctOList[i] = 0;
				else if (parser[0] == 't' && !(strcmp(oList[i].getType().c_str(), parser + 3) <= 0)) correctOList[i] = 0;
			}

			else if (parser[1] == '>') {
				if (parser[0] == 'p' && !(oList[i].getPrice() > atoi(parser + 2))) correctOList[i] = 0;
				else if (parser[0] == 'n' && !(strcmp(oList[i].getName().c_str(), parser + 2) > 0)) correctOList[i] = 0;
				else if (parser[0] == 'd' && !(strcmp(oList[i].getDest().c_str(), parser + 2) > 0)) correctOList[i] = 0;
				else if (parser[0] == 't' && !(strcmp(oList[i].getType().c_str(), parser + 2) > 0)) correctOList[i] = 0;
			}

			else if (parser[1] == '<') {
				if (parser[0] == 'p' && !(oList[i].getPrice() < atoi(parser + 2))) correctOList[i] = 0;
				else if (parser[0] == 'n' && !(strcmp(oList[i].getName().c_str(), parser + 2) < 0)) correctOList[i] = 0;
				else if (parser[0] == 'd' && !(strcmp(oList[i].getDest().c_str(), parser + 2) < 0)) correctOList[i] = 0;
				else if (parser[0] == 't' && !(strcmp(oList[i].getType().c_str(), parser + 2) < 0)) correctOList[i] = 0;
			}

			else if (parser[1] == '=') {
				if (parser[0] == 'p' && !(oList[i].getPrice() == atoi(parser + 2))) correctOList[i] = 0;
				else if (parser[0] == 'n' && !(strcmp(oList[i].getName().c_str(), parser + 2) == 0)) correctOList[i] = 0;
				else if (parser[0] == 'd' && !(strcmp(oList[i].getDest().c_str(), parser + 2) == 0)) correctOList[i] = 0;
				else if (parser[0] == 't' && !(strcmp(oList[i].getType().c_str(), parser + 2) == 0)) correctOList[i] = 0;
			}
		}
		parser = strtok(NULL, " ");

	}

	vector<offer> oListFiltered;
	for (int i = 0; i < oList.size(); i++)
		if (correctOList[i])
			oListFiltered.push_back(oList[i]);

	return oListFiltered;
}

