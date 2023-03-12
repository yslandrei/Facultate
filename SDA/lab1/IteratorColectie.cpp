#include "IteratorColectie.h"
#include "Colectie.h"


IteratorColectie::IteratorColectie(const Colectie& c) : col(c) {
	prim();
}


void IteratorColectie::prim() {
	pos = TPair{ 0, 1 };
}


void IteratorColectie::urmator() {
	if (pos.freq < col.vFreq[pos.e].freq)
		pos.freq++;
	else {
		pos.freq = 1;
		pos.e++;
	}
}


bool IteratorColectie::valid() const {
	return pos.e < col.vFreqLen && pos.freq <= col.vFreq[pos.e].freq ? true : false;
}


TElem IteratorColectie::element() const {
	if (valid())
		return col.vFreq[pos.e].e;
	return -1;
}
