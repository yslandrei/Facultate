#pragma once
#include <fstream>
#include "offersRepository.h"
#include "exceptions.h"

class cartRepository {
private:
	vector<offer> cList;

public:
	cartRepository() = default;

	cartRepository(const cartRepository& ot) = delete;

	const vector<offer>& getAll() const;

	void addOffer(const offer& newOffer);

	void emptyCart();

	void exportCart(const string& fileName) const;
};

