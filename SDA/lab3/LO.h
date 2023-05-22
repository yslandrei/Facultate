#pragma once

class Iterator;

typedef int TComparabil;
typedef TComparabil TElement;

typedef bool (*Relatie)(TElement, TElement);

#define NULL_TELEMENT -1

typedef struct Node {
	TElement elem;
	Node* next;
};

class LO {
private:
	friend class Iterator;
private:
	/* aici reprezentarea */
	Node* head;
	Relatie r;
public:
		// constructor
		// complexitate: Θ(1)
		LO (Relatie r);

		// returnare dimensiune
		// complexitate: Θ(n)
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

		// sterge element de pe o pozitie poz si returneaza elementul sters
		//dupa stergere poz e pozitionat pe elementul de dupa cel sters
		//arunca exceptie daca poz nu e valid
		// complexitate: O(n)
		TElement sterge(Iterator& poz);

		// cauta element si returneaza prima pozitie pe care apare (sau iterator invalid)
		// complexitate: O(n)
		Iterator cauta(TElement e) const;

		// elimina din lista curenta toate elementele care apar in lista
		// returneaza numarul de elemente eliminate
		// best case: Θ(1)
		// average case: O(n*m)
		// worst case: Θ(n*m)
		int eliminaToate(LO& list);	

		//destructor
		~LO();

		void printeaza();
};
