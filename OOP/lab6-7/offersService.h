#pragma once
#include <algorithm>
#include "offersRepository.h"
#include "validate.h"
#pragma warning(disable : 4996)

using std::sort;

class offersService {
private:
	offersRepository& oRepo;

public:
	offersService(offersRepository& oRepo) :
		oRepo{ oRepo }
	{}

	offersService(const offersService& ot) = delete;

	const vector<offer>& getAll() const;

	void addOffer(const int id, const string name, const string dest, const string type, const int price);

	void popOffer(const int id);
	
	void modOffer(const int oldId, const int id, const string name, const string dest, const string type, const int price);

	const offer& findOffer(const string name) const;

	vector<offer> sortOffers(const char cmp) const;

	vector<offer> filterOffers(char* criteria) const;
};

