#pragma once
#include "domain.h"
#include <stdlib.h>
#include <string.h>

Masina creaza_masina(char* nr_inmatr, char* modelul, char* categoria)
{
	//Functia primeste ca parametrii 3 siruri de caractere si imi returneaza o masina creata (de tipul Masina)
	Masina masina;

	//aloc memorie numarului de inmatriculare si il copiez in componenta structului
	masina.nr_inmatriculare = malloc((strlen(nr_inmatr) + 1) * sizeof(char));
	strcpy(masina.nr_inmatriculare, nr_inmatr);

	//aloc memorie modelul si il copiez in componenta structului
	masina.model = malloc((strlen(modelul) + 1) * sizeof(char));
	strcpy(masina.model, modelul);

	//aloc memorie categoriei si o copiez in componenta structului
	masina.categorie = malloc((strlen(categoria) + 1) * sizeof(char));
	strcpy(masina.categorie, categoria);

	//masina adaugata este automat neinchiriata ( 0 - neinchiriat / 1 - inchiriat )
	masina.inchiriere = 0;

	return masina;
}

void distruge_masina(Masina* masina)
{
	//Functia primeste ca parametru o Masina si o distruge (elibereaza spatiul de memorie)
	free(masina->nr_inmatriculare);
	free(masina->categorie);
	free(masina->model);
}

Masina copiaza_masina(Masina masina)
{
	//Functia creaza o copie a unei Masini trimise ca paramametru
	Masina copie_masina;
	copie_masina = creaza_masina(masina.nr_inmatriculare, masina.model, masina.categorie);
	return copie_masina;
}

void modifica_masina(Masina masina_veche, Masina masina_noua)
{
	//Functia modifica componentele Masinii vechi cu componentele de la Masina noua
	strcpy(masina_veche.categorie, masina_noua.categorie);
	strcpy(masina_veche.model, masina_noua.model);
}
