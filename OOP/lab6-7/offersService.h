#pragma once
#include <algorithm>
#include "offersRepository.h"
#include "validate.h"
#include "undo.h"
#pragma warning(disable : 4996)

using std::sort;
using std::unique_ptr;
using std::make_unique;

class offersService {
private:
	offersRepository& oRepo;
	vector<unique_ptr<undoAction>> undoActions;

public:
	offersService(offersRepository& oRepo) :
		oRepo{ oRepo }
	{}

	offersService(const offersService& ot) = delete;

	const vector<offer>& getAll() const;
	
	void addOffer(const int id, const string name, const string dest, const string type, const int price);

	void popOffer(const int id);
	
	void modOffer(const int oldId, const int id, const string name, const string dest, const string type, const int price);

	const offer findOffer(const string name) const;

	vector<offer> sortOffers(const char cmp) const;

	vector<offer> filterOffers(char* criteria) const;

	void doUndo();
};

