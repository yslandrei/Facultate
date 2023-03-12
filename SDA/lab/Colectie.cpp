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

	vFreq[vFreqLen++] = TPair{
		.e = elem,
		.freq = 1
	};
}


bool Colectie::sterge(TElem elem) {
	for (int i = 0; i < vFreqLen; i++)
		if (vFreq[i].e == elem) {
			vFreq[i].freq--;

			if (vFreq[i].freq == 0) {
				vFreqLen--;
				for (int j = i; j < vFreqLen; j++)
					vFreq[i] = vFreq[i + 1];
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
		nrElem += vFreq[i].e;

	return nrElem;
}


bool Colectie::vida() const {
	return vFreqLen ? true : false;
}

IteratorColectie Colectie::iterator() const {
	return  IteratorColectie(*this);
}


Colectie::~Colectie() {
	free(vFreq);
}


