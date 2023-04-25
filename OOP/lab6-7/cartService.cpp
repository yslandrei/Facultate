#include "cartService.h"

const vector<offer>& cartService::getAll() const {
	return cRepo.getAll();
}

void cartService::addOffer(const string name) {
	validate::name(name);
	const vector<offer>& oList = oRepo.getAll();
	const auto& found = std::find_if(oList.begin(), oList.end(), [&](const offer& Offer) {
		return Offer.getName() == name;
	});
	
	if (found != oList.end()) {
		cRepo.addOffer(*found);
		return; } throw exception("Nume inexistent!\n"); }

void cartService::emptyCart() {
	cRepo.emptyCart();
}

void cartService::exportCart(const string& fileName) const {
	cRepo.exportCart(fileName);
}

void cartService::generateCart(const int n) {
	const vector<offer>& oList = oRepo.getAll();
	vector<offer> tempList(oList.begin(), oList.end());
	cRepo.emptyCart();

	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(tempList.begin(), tempList.end(), g);

	int i = 0;
	for (const auto& Offer : tempList) {
		if (i == n)
			break;
		cRepo.addOffer(Offer);
		i += 1;
	}
}

const int cartService::typeOfCart(const string type) const {
	validate::type(type);
	map<string, int> typeMap;
	const vector<offer>& cList = cRepo.getAll();
	for (const auto& Offer : cList) {
		typeMap[Offer.getType()]++;
	}
	return typeMap[type];
}


