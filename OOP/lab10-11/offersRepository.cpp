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

offer offersRepository::popOffer(const int oldId) {
	int i = 0;
	offer oldOffer;
	for (const auto& Offer : oList) {
		if (Offer.getId() == oldId) {
			oldOffer = Offer;
			oList.erase(oList.begin() + i);
			return oldOffer;
		}
		i++;
	}

	throw repositoryException("ID inexistent!\n");
}

offer offersRepository::modOffer(const int oldId, const offer& newOffer) {
	offer oldOffer;
	for (auto& Offer : oList)
		if (Offer.getId() == oldId) {
			oldOffer = Offer;
			Offer = newOffer;
			return oldOffer;
		}

	throw repositoryException("ID inexistent!\n");
}
