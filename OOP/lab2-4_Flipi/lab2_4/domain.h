#pragma once
#define _CRTDB_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

typedef struct
{
	char* nr_inmatriculare;
	char* model;
	char* categorie;
	int inchiriere;
}Masina;

Masina creaza_masina(char* nr_inmatr, char* modelul, char* categoria);

void distruge_masina(Masina* masina);

Masina copiaza_masina(Masina masina);

void modifica_masina(Masina masina_veche, Masina masina_noua);