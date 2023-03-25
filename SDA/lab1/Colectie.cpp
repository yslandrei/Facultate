#include "Colectie.h"
#include "IteratorColectie.h"
#include <exception>
#include <iostream>

using namespace std;


Colectie::Colectie() {
	maxSize = 16;
	vFreq = new TPair[maxSize];
	vFreqLen = 0;
}


void Colectie::resize() {
	maxSize *= 2;
	TPair* resizedVFreq = new TPair[maxSize];

	for (int i = 0; i < vFreqLen; i++)
		resizedVFreq[i] = vFreq[i];

	free(vFreq);
	vFreq = resizedVFreq;
}


void Colectie::adauga(TElem elem) {
	if (vFreqLen == maxSize)
		resize();

	for (int i = 0; i < vFreqLen; i++)
		if (vFreq[i].e == elem) {
			vFreq[i].freq++;
			return;
		}
	
	vFreq[vFreqLen++] = TPair{ elem, 1 };
}


bool Colectie::sterge(TElem elem) {
	for (int i = 0; i < vFreqLen; i++)
		if (vFreq[i].e == elem) {
			vFreq[i].freq--;

			if (vFreq[i].freq == 0) {
				vFreqLen--;
				for (int j = i; j < vFreqLen; j++)
					vFreq[j] = vFreq[j + 1];
			}

			return true;
		}
	return false;
}


bool Colectie::cauta(TElem elem) const {
	for (int i = 0; i < vFreqLen; i++)
		if (vFreq[i].e == elem)
			return true;

	return false;
}

int Colectie::nrAparitii(TElem elem) const {
	for (int i = 0; i < vFreqLen; i++)
		if (vFreq[i].e == elem)
			return vFreq[i].freq;

	return 0;
}


int Colectie::dim() const {
	int nrElem = 0;

	for (int i = 0; i < vFreqLen; i++)
		nrElem += vFreq[i].freq;

	return nrElem;
}


bool Colectie::vida() const {
	return vFreqLen ? false : true;
}


/*
Subalgoritm eliminaAparitii(nr, elem)
{pre: c o colectie, nr este un numar pozitiv, elem este un TElement}
{post: c' = c - {(nr, elem)} - colectia din care s-a elimina nr aparitii ale TElementului elem}

Daca nr < 0
	{Aruncam exceptie}
SfDaca

Pentru i=0, c.lungime - 1
	Daca c.vFreq[i].elem = elem
		Daca c.vFreq[i].frecventa > nr
			c.vFreq[i].frecventa -= nr
			return nr
		SfDaca

		Altfel
			sterge(c[i].elem)
			return c[i].elem
		SfAltfel
	
	SfDaca
SfPentru
*/
int Colectie::eliminaAparitii(int nr, TElem elem) {
	if (nr < 0)
		throw std::invalid_argument("Numar negativ");

	for (int i = 0; i < vFreqLen; i++)
		if (vFreq[i].e == elem) {
			if (vFreq[i].freq > nr) {
				vFreq[i].freq -= nr;
				return nr;
			}
			else {
				int deletedFreq = vFreq[i].freq;
				sterge(vFreq[i].e);
				return deletedFreq;
			}
		}

	return 0;
}

IteratorColectie Colectie::iterator() const {
	return  IteratorColectie(*this);
}


Colectie::~Colectie() {
	free(vFreq);
}


