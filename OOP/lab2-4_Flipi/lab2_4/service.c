#pragma once
#include "service.h"
#include "validare.h"
#include <string.h>
#include <stdio.h>

int serv_adauga(Lista* lista, char* nr_inmatr, char* model, char* categorie)
{
	//Functia adauga o masina validata in lista
	Masina* masina = creaza_masina(nr_inmatr, model, categorie);
	int validat = validare(masina);
	if (validat == 0)
	{
		distruge_masina(masina);
		return 0;
	}
	adauga_masina(lista, masina);
	return 1;
}

int cauta_id(Lista* lista, char* nr_inmatr)
{
	//Functia cauta in lista masina cu numarul de inmatriculare dat.
	int pozitie = -1;
	for (int i = 0; i < lista->lungime; i++)
	{
		
		if (strcmp((*(Masina*)lista->elemente[i]).nr_inmatriculare, nr_inmatr) == 0)
		{
			pozitie = i;
			break;
		}
	}
	return pozitie;
}

int serv_modifica(Lista* lista, char* nr_inmatr, char* model, char* categorie)
{
	//Functia modifica in lista o masina
	int pozitie = cauta_id(lista, nr_inmatr);
	if (pozitie != -1)
	{
		Masina* masina_noua = creaza_masina(nr_inmatr, model, categorie);
		int validat = validare(masina_noua);
		if (validat == 0) { distruge_masina(masina_noua); return 0; }
		seteaza_element(lista, pozitie, masina_noua);
		return 1;}
	else return 0;
}

int serv_inchiriaza(Lista* lista, char* nr_inmatr)
{
	//Functia modifica statusul de inchiriere al unei masini la INCHIRIAT
	int pozitie = cauta_id(lista, nr_inmatr);
	if (pozitie != -1)
	{
		(*(Masina*)lista->elemente[pozitie]).inchiriere = 1;
		return 1;}
	else return 0;
}

int serv_returnare(Lista* lista, char* nr_inmatr)
{
	//Functia modifica statusul de inchiriere al unei masini la NEINCHIRIAT
	int pozitie = cauta_id(lista, nr_inmatr);
	if (pozitie != -1)
	{
		(*(Masina*)lista->elemente[pozitie]).inchiriere = 0;
		return 1;}
	else return 0;
}

Lista* serv_filtrare_categorie(Lista* lista, char* categ)
{
	//Functia filtreaza lista de masini dupa o categorie transmisa ca parametru
	Lista* filtered_list = creaza_lista();
	if (strcmp(categ, "sedan") == 0 || strcmp(categ, "suv") == 0 || strcmp(categ, "sport") == 0 || strcmp(categ, "mini") == 0)
	{
		for (int i = 0; i < lista->lungime; i++)
		{
			if (strcmp((*(Masina*)lista->elemente[i]).categorie, categ) == 0)
			{
				Masina* masina = copiaza_masina(lista->elemente[i]);
				adauga_masina(filtered_list, masina);
			}
		}
	}
	return filtered_list;
}

Lista* serv_filtrare_judet(Lista* lista, char* judet) 
{
	int nrJudete = 0;
	char judete[20][5] = { 0 };
	char* parser = strtok(judet, " ");
	while (parser != NULL)
	{
		strcpy(judete[nrJudete++], parser);
		parser = strtok(NULL, " ");
	}

	Lista* filtered_list = creaza_lista();
	for (int i = 0; i < lista->lungime; i++) 
	{
		for (int j = 0; j < nrJudete; j++)
			if (strncmp((*(Masina*)lista->elemente[i]).nr_inmatriculare, judete[j], 2) == 0)
			{
				Masina* masina = copiaza_masina(lista->elemente[i]);
				adauga_masina(filtered_list, masina);
			}
	}
	return filtered_list;
}


void serv_sortare(Lista* lista, FunctieComparare cmpF)
{
	//Functia sorteaza crescator lista de masini in functie de functia de comparare
	//Lista lista_sortata = copy_list(lista);
	for (int i = 0; i < lista->lungime - 1; i++)
		for (int j = i + 1; j < lista->lungime; j++)
		{
			if (cmpF(lista->elemente[i], lista->elemente[j]) > 0)
			{
				ElemType aux = lista->elemente[i];
				lista->elemente[i] = lista->elemente[j];
				lista->elemente[j] = aux;
			}
		}
}
//strcmp(lista->elemente[i].model, lista->elemente[j].model) > 0

int cmpModel(Masina* m1, Masina* m2) 
{
	//Este criteriul de comparatie pentru functia de sortare
	return strcmp(m1->model, m2->model);
}

int cmpCategorie(Masina* m1, Masina* m2)
{
	return strcmp(m1->categorie, m2->categorie);
}

void serv_sortare_model(Lista* lista)
{
	//Functia de sortare
	serv_sortare(lista, cmpModel);
}

void serv_sortare_categorie(Lista* lista)
{
	serv_sortare(lista, cmpCategorie);
}
