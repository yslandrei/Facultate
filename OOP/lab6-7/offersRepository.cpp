#include "offersRepository.h"

const vector<offer>& offersRepository::getAll() const {
	return oList;
}

void offersRepository::addOffer(const offer& newOffer) {
	for (const auto& Offer : oList)
		if (Offer.getId() == newOffer.getId()) {
			throw repositoryException("ID deja existent!\n");
		}

	oList.push_back(newOffer);
}

void offersRepository::popOffer(const int oldId) {
	int i = 0;
	for (const auto& Offer : oList) {
		if (Offer.getId() == oldId) {
			oList.erase(oList.begin() + i);
			return;
		}
		i++;
	}

	throw repositoryException("ID inexistent!\n");
}

void offersRepository::modOffer(const int oldId, const offer& newOffer) {
	for (auto& Offer : oList)
		if (Offer.getId() == oldId) {
			Offer = newOffer;
			return;
		}

	throw repositoryException("ID inexistent!\n");
}
