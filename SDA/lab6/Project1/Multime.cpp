#include "Multime.h"
#include "IteratorMultime.h"
#include <iostream>

//complexitate theta(1)
int Multime::hash(TElem e, int i) const {
	return (abs(e) % m + i * (1 + abs(e) % m)) % m;
}

//complexitate theta(m)
Multime::Multime() {
	this->m = 1000000;
	e = new TElem[m];
	this->DIM = 0;
	for (int i = 0; i < m; i++)
		this->e[i] = NULL_TELEM;
}

//complexitate O(m)
bool Multime::adauga(TElem elem) {
	int i = 0;
	//if (m == DIM)redispersare();

	while (i < m) {
		int j = hash(elem, i);
		if (e[j] == elem)
			return false;
		if (e[j] == NULL_TELEM or e[j] == STERS) {
			DIM++;
			e[j] = elem;
			return true;
		}
		i++;
	}
}

//complexitate O(m)
bool Multime::sterge(TElem elem) {
	int i = 0;

	while (i < m) {
		int j = hash(elem, i);
		if (e[j] == elem) {
			DIM--;
			e[j] = STERS;
			return true;
		}
		if (e[j] == NULL_TELEM)return false;
		i++;
	}
}

//complexitate O(m)
bool Multime::cauta(TElem elem) const {
	int i = 0;
	while (i < m) {
		int j = hash(elem, i);
		if (e[j] == elem)
			return true;
		if (e[j] == NULL_TELEM)
			return false;
		i++;
	}
	return false;
}

//complexitate theta(1)
int Multime::dim() const {
	return DIM;
}
//complexitate theta(1)
bool Multime::vida() const {
	return DIM == 0;
}

//complexitate theta(m)
/*
{pre: m, b - Multimi}
{post: m' = m - b, stergem din m elementele ce nu apar in b
si returnam numarul de elemente eliminate}

im <- IteratorMultime(b)
prim(im)
sterse <- 0

cat timp(valid(im)):
	daca sterge(element(im)) = adevarat:
		sterse <- sterse + 1
	urmator(im)

return sterse
*/
int Multime::diferenta(Multime& b) {
	IteratorMultime im(b);
	im.prim();

	int sterse = 0;
	while (im.valid()) {
		if (sterge(im.element()) == true)
			sterse++;

		im.urmator();
	}
	return sterse;
}

//complexitate theta(1)
Multime::~Multime() {
	delete[] e;
}

//complexitate theta(1)
IteratorMultime Multime::iterator() const {
	return IteratorMultime(*this);
}