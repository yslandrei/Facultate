#pragma once
#include <exception>
#define NULL_TELEM -80000
#define STERS -80001
typedef int TElem;

class IteratorMultime;

class Multime {
	friend class IteratorMultime;

private:
	int m, DIM;//m-numarul de locatii din tabela de dispersie,DIM-numarul de elemente
	//tabela de elemente
	TElem* e;
	//functie de dispersie 
	int hash(TElem e, int i) const;

public:
	//constructorul implicit
	Multime();

	//adauga un element in multime
	//returneaza adevarat daca elementul a fost adaugat (nu exista deja in multime)
	bool adauga(TElem e);

	//sterge un element din multime
	//returneaza adevarat daca elementul a existat si a fost sters
	bool sterge(TElem e);

	//verifica daca un element se afla in multime
	bool cauta(TElem elem) const;

	//intoarce numarul de elemente din multime;
	int dim() const;

	//verifica daca multimea e vida;
	bool vida() const;

	//returneaza un iterator pe multime
	IteratorMultime iterator() const;

	// păstrează numai acele elemente care nu apar în mulțimea b 
	// returnează numărul de elemente eliminate 
	int diferenta(Multime& b);

	// destructorul multimii
	~Multime();
};