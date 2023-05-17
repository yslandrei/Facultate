#include "Iterator.h"
#include "LO.h"
#include <iostream>

LO::LO(Relatie r) {
	this->head = NULL;
	this->r = r;
}

// returnare dimensiune
int LO::dim() const {
	int dim = 0;
	Iterator it = Iterator(*this);
	
	it.prim();
	while (it.valid()) {
		dim++;
		it.urmator();
	}
	return dim;
}

// verifica daca LO e vida
bool LO::vida() const {
	return head == NULL;
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
	//elementul sters e primul element
	if (e == head->elem) {
		int elemSters = head->elem;
		Node* headAux = head;
		head = head->next;
		free(headAux);
		return elemSters;
	}

	Node* curr = head;
	Node* prev = NULL;
	while (curr != NULL && curr->elem != e) {
		prev = curr;
		curr = curr->next;
	}

	// elementul sters e ultimul element
	if (curr == NULL) {
		int elemSters = prev->elem;
		free(prev);
		prev = NULL;
		return elemSters;
	}
	// caz general
	int elemSters = curr->elem;
	prev->next = curr->next;
	free(curr);
	return elemSters;
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
	if (head == NULL) {
		head = new Node{ e, NULL };
		return;
	}

	Node* curr = head;
	Node* lftNode = NULL;
	while (curr != NULL && r(curr->elem, e)) {
		lftNode = curr;
		curr = curr->next;
	}

	if (curr == NULL) {
		lftNode->next = new Node{ e, NULL };
		return;
	}
	if (curr == head) {
		Node* newNode = new Node { e, head };
		head = newNode;
		return;
	}

	Node* rgtNode = lftNode->next;
	lftNode->next = new Node{ e, rgtNode };
}


//destructor
LO::~LO() {
	Node* curr = head;
	while (curr != NULL) {
		Node* currAux = curr;
		curr = curr->next;
		delete currAux;
	}
}

void LO::printeaza() {
	Node* curr = head;
	while (curr != NULL) {
		std::cout << curr->elem << "\n";
		curr = curr->next;
	}
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

int LO::eliminaToate(LO& sterse) {
	Iterator it = Iterator(sterse);
	int dim = 0;

	it.prim();
	while (it.valid()) {
		sterge(it);
		dim++;
	}
	return dim;
}
