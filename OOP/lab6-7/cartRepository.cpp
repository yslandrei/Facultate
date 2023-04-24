#include "cartRepository.h"
#include <fstream>

const vector<offer>& cartRepository::getAll() const {
	return cList;
}

void cartRepository::addOffer(const offer& newOffer) {
	for (const auto& Offer : cList)
		if (Offer.getId() == newOffer.getId()) {
			throw exception("ID deja existent!\n");
		}

	cList.push_back(newOffer);
}

void cartRepository::emptyCart() {
	cList.clear();
}

void cartRepository::exportCart(const string& fileName) const {
	const string fileNameCsv = fileName + ".csv";
	std::ofstream csvout(fileNameCsv);
	
	for (const auto& Offer : cList)
		csvout << "id: " << Offer.getId() << ", nume: " << Offer.getName() << ", destinatie: " << Offer.getDest() << ", tip: " << Offer.getType() << ", pret: " << Offer.getPrice() << "\n";

	csvout.close();
}