#pragma once
#include "vector.h"
//#include <vector>
#include <iterator>
#include "offer.h"

using std::exception;
//using std::vector;
using std::iterator;

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

