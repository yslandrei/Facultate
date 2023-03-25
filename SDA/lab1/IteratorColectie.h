#pragma once
#include "Colectie.h"

class Colectie;
typedef int TElem;

class IteratorColectie
{
	friend class Colectie;
private:
	//constructorul primeste o referinta catre Container
	//iteratorul va referi primul element din container
	//complexitate: O(1)
	IteratorColectie(const Colectie& c);

	//contine o referinta catre containerul pe care il itereaza
	const Colectie& col;
	/* aici e reprezentarea pecifica a iteratorului*/
	TPair pos;

public:

	//reseteaza pozitia iteratorului la inceputul containerului
	//complexitate: O(1)
	void prim();

	//muta iteratorul in container
	// arunca exceptie daca iteratorul nu e valid
	//complexitate: O(1)
	void urmator();

	//verifica daca iteratorul e valid (indica un element al containerului)
	//complexitate: O(1)
	bool valid() const;

	//returneaza valoarea elementului din container referit de iterator
	//arunca exceptie daca iteratorul nu e valid
	//complexitate: O(1)
	TElem element() const;
};

