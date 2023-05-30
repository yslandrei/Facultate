#include "Iterator.h"
#include "LO.h"
#include <iostream>

LO::LO(Relatie r) {
	first = 0;
	size = 1;
	maxSize = 2;
	nodes = new Node[maxSize];
	this->r = r;
}

// returnare dimensiune
int LO::dim() const {
	return size - 1;
}

// verifica daca LO e vida
bool LO::vida() const {
	return size - 1 == 0;
}

// prima pozitie din LO
Iterator LO::prim() const {
	Iterator it = Iterator(*this);

	it.prim();
	return it;
}

// returnare element de pe pozitia curenta
//arunca exceptie daca poz nu e valid
TElement LO::element(Iterator poz) const {
	return poz.element();
}

//sterge element de pe o pozitie poz si returneaza elementul sters
//dupa stergere poz e pozitionat pe elementul de dupa cel sters
//arunca exceptie daca poz nu e valid
TElement LO::sterge(Iterator& poz) {
	if (poz.valid() == false)
		throw std::exception();
	int e = poz.element();
	poz.urmator();

	size--;
	if (e == nodes[first].elem) { // stergem primul element
		nodes[first].elem = FREE_TELEMENT;
		first = nodes[first].next;
		return e;
	}

	int curr = first, prev;
	while (nodes[curr].elem != e) {
		prev = curr;
		curr = nodes[curr].next;
	}
	nodes[prev].next = nodes[curr].next;
	nodes[curr].elem = FREE_TELEMENT;
	return e;
}


// cauta element si returneaza prima pozitie pe care apare (sau iterator invalid)
Iterator LO::cauta(TElement e) const {
	Iterator it = Iterator(*this);

	it.prim();
	while (it.valid() && it.element() != e) {
		it.urmator();
	}
	return it;
}

// adaugare element in LO
void LO::adauga(TElement e) {
	if (first == 0) { // primul element
		first = 1;
		nodes[size++] = Node{ e, NULL_TELEMENT };
		return;
	}
	
	if (size == maxSize)
		resize();
	// gasesc pozitia in vectorul dinamic unde voi insera valoare
	int freePosition = -1;
	for (int i = 1; i < maxSize; i++)
		if (nodes[i].elem == FREE_TELEMENT) {
			freePosition = i;
			break;
		}
	// gasesc elementele din lista ordonata intre care trebuie sa il pun
	if (r(e, nodes[first].elem)) { // intra la inceput
		nodes[freePosition] = Node{ e, first };
		first = freePosition;
		size++;
		return;
	}
	size++;
	int curr = first, prev;
	while (r(nodes[curr].elem, e) && curr != NULL_TELEMENT) {
		prev = curr;
		curr = nodes[curr].next;
	}
	nodes[prev].next = freePosition;
	nodes[freePosition] = Node{ e, curr };
}

void LO::resize() {
	maxSize *= 2;
	Node* resizedNodes = new Node[maxSize];

	for (int i = 0; i < size; i++)
		resizedNodes[i] = nodes[i];

	for (int i = size; i < maxSize; i++)
		resizedNodes[i].elem = FREE_TELEMENT;

	delete[] nodes;
	nodes = resizedNodes;
}

/*
{pre: lo - Lista Ordonata}
{pre: sterse - Lista Ordonata (cu elementele care vor fi sterse)}
{post: lo are 0 elemente, returnam numarul de elemente eliminate}

iter - Iterator(sterse)
iter <- lo.prim
dim <- 0

cat timp(lo.valid)
	sterge(iter)
	dim <- dim + 1

return dim
*/

int LO::eliminaToate(LO& listaDeSters) {
	Iterator it = Iterator(listaDeSters);
	int dim = 0;

	it.prim();
	while (it.valid()) {
		sterge(it);
		dim++;
	}
	return dim;
}


//destructor
LO::~LO() {
	delete nodes;
}
