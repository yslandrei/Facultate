#pragma once
#include "IteratorMultime.h"
#include <vector>
#include <iostream>

#define NULL_TELEM -1
typedef int TElem;


class Multime {
	friend class IteratorMultime;

private:
	struct Nod {
		TElem element;
		bool ocupat;
		bool sters;
	};

	std::vector<Nod> tabela;
	int dimensiune;
	int capacitate;

	// Functia de dispersie pentru primul pas
	int functieHash1(TElem element) const {
		return std::hash<TElem>{}(element) % capacitate;
	}

	// Functia de dispersie pentru al doilea pas
	int functieHash2(TElem element) const {
		return 1 + (std::hash<TElem>{}(element) % (capacitate - 1));
	}

public:
	//constructorul implicit
	Multime() : dimensiune(0), capacitate(10) {
		tabela.resize(capacitate);
		for (auto& nod : tabela) {
			nod.ocupat = false;
			nod.sters = false;
		}
	}

	//adauga un element in multime
	//returneaza adevarat daca elementul a fost adaugat (nu exista deja in multime)
	bool adauga(TElem e) {
		if (dimensiune >= capacitate / 2)
			rehash();

		int index = functieHash1(e);
		int pas = 0;

		while (tabela[index].ocupat && !tabela[index].sters) {
			if (tabela[index].element == e)
				return false; // Elementul exista deja in multime

			pas++;
			index = (functieHash1(e) + pas * functieHash2(e)) % capacitate;
		}

		tabela[index].element = e;
		tabela[index].ocupat = true;
		tabela[index].sters = false;
		dimensiune++;

		return true;
	}

	//sterge un element din multime
	//returneaza adevarat daca elementul a existat si a fost sters
	bool sterge(TElem e) {
		int index = functieHash1(e);
		int pas = 0;

		while (tabela[index].ocupat) {
			if (!tabela[index].sters && tabela[index].element == e) {
				tabela[index].sters = true;
				dimensiune--;
				return true;
			}

			pas++;
			index = (functieHash1(e) + pas * functieHash2(e)) % capacitate;
		}

		return false; // Elementul nu exista in multime
	}

	//verifica daca un element se afla in multime
	bool cauta(TElem elem) const {
		int index = functieHash1(elem);
		int pas = 0;

		while (tabela[index].ocupat) {
			if (!tabela[index].sters && tabela[index].element == elem)
				return true;

			pas++;
			index = (functieHash1(elem) + pas * functieHash2(elem)) % capacitate;
		}

		return false;
	}

	//intoarce numarul de elemente din multime;
	int dim() const {
		return dimensiune;
	}

	//verifica daca multimea e vida;
	bool vida() const {
		return dimensiune == 0;
	}

	//returneaza un iterator pe multime
	IteratorMultime iterator() const;

	// destructorul multimii
	~Multime() {
		tabela.clear();
	}

	void afisare() const {
		if (dimensiune == 0) {
			std::cout << "Multimea este vida." << std::endl;
			return;
		}

		std::cout << "Elementele din multime sunt: ";
		for (const auto& nod : tabela) {
			if (nod.ocupat && !nod.sters) {
				std::cout << nod.element.first << ":" << nod.element.second << " ";
			}
		}
		std::cout << std::endl;
	}

private:
	// Functia de rehashare
	void rehash() {
		std::vector<Nod> tabelaNoua;
		int capacitateNoua = capacitate * 2;
		tabelaNoua.resize(capacitateNoua);
		for (auto& nod : tabelaNoua) {
			nod.ocupat = false;
			nod.sters = false;
		}

		for (const auto& nod : tabela) {
			if (nod.ocupat && !nod.sters) {
				int index = functieHash1(nod.element);
				int pas = 0;

				while (tabelaNoua[index].ocupat) {
					pas++;
					index = (functieHash1(nod.element) + pas * functieHash2(nod.element)) % capacitateNoua;
				}

				tabelaNoua[index].element = nod.element;
				tabelaNoua[index].ocupat = true;
			}
		}

		tabela = tabelaNoua;
		capacitate = capacitateNoua;
	}
};
