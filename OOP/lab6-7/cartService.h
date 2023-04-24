#pragma once
#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
#include "cartRepository.h"
#include "validate.h"


class cartService {
private:
	offersRepository& oRepo;
	cartRepository& cRepo;

public:
	cartService(offersRepository& oRepo, cartRepository& cRepo) :
		oRepo{ oRepo },
		cRepo{ cRepo }
	{}

	cartService(const cartService& ot) = delete;

	const vector<offer>& getAll() const;

	void addOffer(const string name);

	void emptyCart();

	void exportCart(const string& fileName) const;

	void generateCart(const int n);
};