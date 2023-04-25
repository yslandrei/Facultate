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

const offer offersService::findOffer(const string name) const {
	validate::name(name);
	const vector<offer>& oList = oRepo.getAll();
	const auto& found = std::find_if(oList.begin(), oList.end(), [&](const offer& Offer) {
		return Offer.getName() == name;
	});
	
	if (found != oList.end())
		return *found; throw exception("Nume inexistent!\n"); }

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
	const vector<offer>& oList = oRepo.getAll();
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
	const vector<offer>& oList = oRepo.getAll();
	bool correctOList[100] = {0};
	for (int i = 0; i < oList.size(); i++)
		correctOList[i] = 1;

	int i;
	char* parser = strtok(criteria, " ");
	while (parser != NULL) {
		i = 0;
		for (const auto& Offer : oList) {
			if (strncmp(parser + 1, ">=", 2) == 0) {
				if (parser[0] == 'p' && !(Offer.getPrice() >= atoi(parser + 3))) correctOList[i] = 0;
				else if (parser[0] == 'n' && !(strcmp(Offer.getName().c_str(), parser + 3) >= 0)) correctOList[i] = 0;
				else if (parser[0] == 'd' && !(strcmp(Offer.getDest().c_str(), parser + 3) >= 0)) correctOList[i] = 0;
				else if (parser[0] == 't' && !(strcmp(Offer.getType().c_str(), parser + 3) >= 0)) correctOList[i] = 0;
			}

			else if (strncmp(parser + 1, "<=", 2) == 0) {
				if (parser[0] == 'p' && !(Offer.getPrice() <= atoi(parser + 3))) correctOList[i] = 0;
				else if (parser[0] == 'n' && !(strcmp(Offer.getName().c_str(), parser + 3) <= 0)) correctOList[i] = 0;
				else if (parser[0] == 'd' && !(strcmp(Offer.getDest().c_str(), parser + 3) <= 0)) correctOList[i] = 0;
				else if (parser[0] == 't' && !(strcmp(Offer.getType().c_str(), parser + 3) <= 0)) correctOList[i] = 0;
			}

			else if (parser[1] == '>') {
				if (parser[0] == 'p' && !(Offer.getPrice() > atoi(parser + 2))) correctOList[i] = 0;
				else if (parser[0] == 'n' && !(strcmp(Offer.getName().c_str(), parser + 2) > 0)) correctOList[i] = 0;
				else if (parser[0] == 'd' && !(strcmp(Offer.getDest().c_str(), parser + 2) > 0)) correctOList[i] = 0;
				else if (parser[0] == 't' && !(strcmp(Offer.getType().c_str(), parser + 2) > 0)) correctOList[i] = 0;
			}

			else if (parser[1] == '<') {
				if (parser[0] == 'p' && !(Offer.getPrice() < atoi(parser + 2))) correctOList[i] = 0;
				else if (parser[0] == 'n' && !(strcmp(Offer.getName().c_str(), parser + 2) < 0)) correctOList[i] = 0;
				else if (parser[0] == 'd' && !(strcmp(Offer.getDest().c_str(), parser + 2) < 0)) correctOList[i] = 0;
				else if (parser[0] == 't' && !(strcmp(Offer.getType().c_str(), parser + 2) < 0)) correctOList[i] = 0;
			}

			else if (parser[1] == '=') {
				if (parser[0] == 'p' && !(Offer.getPrice() == atoi(parser + 2))) correctOList[i] = 0;
				else if (parser[0] == 'n' && !(strcmp(Offer.getName().c_str(), parser + 2) == 0)) correctOList[i] = 0;
				else if (parser[0] == 'd' && !(strcmp(Offer.getDest().c_str(), parser + 2) == 0)) correctOList[i] = 0;
				else if (parser[0] == 't' && !(strcmp(Offer.getType().c_str(), parser + 2) == 0)) correctOList[i] = 0;
			}

			i++;
		}
		
		parser = strtok(NULL, " ");
	}

	i = 0;
	vector<offer> oListFiltered;
	
	for (const auto& Offer : oList) {
		if (correctOList[i]) {
			oListFiltered.push_back(Offer);
		}
		i++;
	}

	return oListFiltered;
}

