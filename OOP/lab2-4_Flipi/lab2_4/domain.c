#pragma once
#include "domain.h"
#include <stdlib.h>
#include <string.h>

Masina* creaza_masina(char* nr_inmatr, char* modelul, char* categoria)
{
	//Functia primeste ca parametrii 3 siruri de caractere si imi returneaza o masina creata (de tipul Masina)
	Masina* masina = malloc(sizeof(Masina));
	if (masina == NULL) return masina;
	//aloc memorie numarului de inmatriculare si il copiez in componenta structului
	masina->nr_inmatriculare = malloc((strlen(nr_inmatr) + 1) * sizeof(char));
	if (masina->nr_inmatriculare == NULL) return masina;
	strcpy(masina->nr_inmatriculare, nr_inmatr);

	//aloc memorie modelul si il copiez in componenta structului
	masina->model = malloc((strlen(modelul) + 1) * sizeof(char));
	if (masina->model == NULL) return masina;
	strcpy(masina->model, modelul);

	//aloc memorie categoriei si o copiez in componenta structului
	masina->categorie = malloc((strlen(categoria) + 1) * sizeof(char));
	if (masina->categorie == NULL) return masina; 
	strcpy(masina->categorie, categoria);

	//masina adaugata este automat neinchiriata ( 0 - neinchiriat / 1 - inchiriat )
	masina->inchiriere = 0;

	return masina;
}

void distruge_masina(Masina* masina)
{
	//Functia primeste ca parametru o Masina si o distruge (elibereaza spatiul de memorie)
	free(masina->nr_inmatriculare);
	free(masina->categorie);
	free(masina->model);
	free(masina);
}

Masina* copiaza_masina(Masina* masina)
{
	//Functia creaza o copie a unei Masini trimise ca paramametru
	Masina* copie_masina = creaza_masina((*masina).nr_inmatriculare, (*masina).model, (*masina).categorie);
	return copie_masina;
}

void modifica_masina(Masina* masina_veche, Masina* masina_noua)
{
	//Functia modifica componentele Masinii vechi cu componentele de la Masina noua
	distruge_masina(masina_veche);
	masina_veche->categorie = masina_noua->categorie;
	masina_veche->nr_inmatriculare = masina_noua->nr_inmatriculare;
	masina_veche->model = masina_noua->model;
	masina_veche->inchiriere = masina_noua->inchiriere;

}
