#pragma once
#include <vector>
#include "offer.h"

using std::vector;
using std::exception;

class offersRepository {
private:
	vector<offer> oList;

public:
	offersRepository() = default;

	offersRepository(const offersRepository& ot) = delete;

	const vector<offer>& getAll() const;
	
	void addOffer(const offer& newOffer);
	
	void popOffer(const int oldId);

	void modOffer(const int oldId, const offer& newOffer);
};

