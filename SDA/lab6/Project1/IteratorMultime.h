#pragma once

#include "Multime.h"

class IteratorMultime
{
	friend class Multime;
private:
	int index;

	IteratorMultime(const Multime& m);

public:
	void prim() {
		index = 0;
	}

	void urmator() {
		if (!valid())
			throw std::exception("Iterator invalid!");

		index++;
	}

	bool valid() const {
		return index < 0;
	}

	/*TElem element() const;*/
		/*if (!valid())
			throw std::exception("Iterator invalid!");

		int currentIndex = index;
		while (currentIndex < multime.capacitate && (!multime.tabela[currentIndex].ocupat || multime.tabela[currentIndex].sters))
			currentIndex++;

		if (currentIndex < multime.capacitate)
			return multime.tabela[currentIndex].element;
		else
			throw std::exception("Iterator invalid!");*/
	/*}*/
};