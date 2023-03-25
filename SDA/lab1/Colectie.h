#pragma once

#define NULL_TELEM -1
typedef int TElem;

typedef struct {
	TElem e;
	int freq;
}TPair;

class IteratorColectie;

class Colectie
{
	friend class IteratorColectie;

private:
	int maxSize;
	TPair* vFreq;
	int vFreqLen;


	//complexitate: O(n)
	void resize();


public:
	//constructorul implicit
	//complexitate: O(1)
	Colectie();

	//adauga un element in colectie
	//complexitate: O(n)
	void adauga(TElem e);

	//sterge o aparitie a unui element din colectie
	//returneaza adevarat daca s-a putut sterge
	//complexitate: O(n)
	bool sterge(TElem e);

	//verifica daca un element se afla in colectie
	//complexitate: O(n)
	bool cauta(TElem elem) const;

	//returneaza numar de aparitii ale unui element in colectie
	//complexitate: O(n)
	int nrAparitii(TElem elem) const;

	//intoarce numarul de elemente din colectie;
	//complexitate: O(n)
	int dim() const;

	//verifica daca colectia e vida;
	//complexitate: O(1)
	bool vida() const;

	//elimina nr aparitii ale elementului elem
	//In cazul in care elementul apare mai putin de nr ori, toate aparitiile sale vor fi eliminate
	//complexitate: O(n)
	int eliminaAparitii(int nr, TElem elem);

	//returneaza un iterator pe colectie
	IteratorColectie iterator() const;

	// destructorul colectiei
	//complexitate: O(1)
	~Colectie();

};

