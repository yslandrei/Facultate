#pragma once
#include <limits.h>

class Iterator;

typedef int TComparabil;
typedef TComparabil TElement;

typedef bool (*Relatie)(TElement, TElement);

#define NULL_TELEMENT 0
#define FREE_TELEMENT INT_MIN

typedef struct Node {
	TElement elem;
	int next;
};

class LO {
private:
	friend class Iterator;
private:
	/* aici reprezentarea */
	Node* nodes;
	int first;
	int size, maxSize;
	Relatie r;
public:
	// constructor
	// complexitate: Θ(1)
	LO(Relatie r);

	// returnare dimensiune
	// complexitate: Θ(1)
	int dim() const;

	// verifica daca LO e vida
	// complexitate: Θ(1)
	bool vida() const;

	// prima pozitie din LO
	// complexitate: Θ(1)
	Iterator prim() const;

	// returnare element de pe pozitia curenta
	//arunca exceptie daca poz nu e valid
	// complexitate: Θ(1)
	TElement element(Iterator poz) const;

	// adaugare element in LO a.i. sa se pastreze ordinea intre elemente
	// complexitate: O(n)
	void adauga(TElement e);

	void resize();

	// sterge element de pe o pozitie poz si returneaza elementul sters
	// dupa stergere poz e pozitionat pe elementul de dupa cel sters
	// arunca exceptie daca poz nu e valid
	// complexitate: O(n)
	TElement sterge(Iterator& poz);

	// cauta element si returneaza prima pozitie pe care apare (sau iterator invalid)
	// complexitate: O(n)
	Iterator cauta(TElement e) const;

	//destructor
	~LO();

	// elimină din lista curentă toate elementele care apar în lista (lista argument) 
	// returnează numărul de elemente eliminate 
	int eliminaToate(LO& lista);
};