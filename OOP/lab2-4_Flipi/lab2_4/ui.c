#pragma once
#include "service.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


void main_meniu()
{
	//Functia care imi afiseaza un meniul principal pe ecran
	printf("Alegeti o optiune de mai jos:\n\n");
	printf("   1. Adauga o noua masina in lista\n");
	printf("   2. Actualizeaza o masina din lista\n");
	printf("   3. Inchiriati o masina\n");
	printf("   4. Returnati o masina\n");
	printf("   5. Filtrati dupa categorie\n");
	printf("   6. Sortati crescator dupa model\n");
	printf("   7. Afisati toata lista\n");

	printf("   0. Iesiti din aplicatie\n");
}

void ui_adauga(Lista* lista)
{
	char numar_inmatriculare[105], mod[105], categ[105];
	printf("Introduceti un numar de inmatriculare, un model si o categorie( suv / sedan / mini / sport)\n");
	printf("Numarul de inmatriculare:\n");
	printf(">>> ");
	scanf("%s", &numar_inmatriculare);
	printf("Modelul:\n");
	printf(">>> ");
	scanf("%s", &mod);
	printf("Categoria:\n");
	printf(">>> ");
	scanf("%s", &categ);
	printf("\n");
	int ok;
	ok = serv_adauga(lista, numar_inmatriculare, mod, categ);
	if (ok) printf("Masina a fost adaugata cu succes!");
	else printf("Input invalid!");
}

void ui_modifica(Lista* lista)
{
	char numar_inmatriculare[105], mod[105], categ[105];
	printf("Introduceti numarul de inmatriculare al masinii pe care doriti sa o modificati, un model nou si o categorie noua( suv / sedan / mini / sport)\n");
	printf("Numarul de inmatriculare:\n");
	printf(">>> ");
	scanf("%s", &numar_inmatriculare);
	printf("Modelul:\n");
	printf(">>> ");
	scanf("%s", &mod);
	printf("Categoria:\n");
	printf(">>> ");
	scanf("%s", &categ);
	printf("\n");
	int succes = serv_modifica(lista, numar_inmatriculare, mod, categ);
	if (succes) printf("Masina a fost modificata cu succes!");
	else printf("Input invalid!");
}

void ui_afiseaza(Lista* lista)
{
	if (lista->lungime == 0) printf("Lista este goala!\n");
	else
	{
		for (int i = 0; i < lista->lungime; i++)
		{
			ElemType element = get(lista, i);
			printf("Numar de inmatriculare: %s | Model: %s | Categorie: %s | ", element.nr_inmatriculare, element.model, element.categorie);
			if (element.inchiriere == 0) printf("Neinchiriat");
			else printf("Inchiriat");
			printf("\n");
		}
	}
}

void ui_inchiriaza(Lista* lista)
{
	char numar_inmatriculare[105];
	printf("Introduceti numarul de inmatriculare al masinii pe care doriti sa o inchiriati\n");
	printf("Numarul de inmatriculare:\n");
	printf(">>> ");
	scanf("%s", &numar_inmatriculare);
	int succes = serv_inchiriaza(lista, numar_inmatriculare);
	if (succes) printf("Masina a fost inchiriata cu succes!");
	else printf("Numar de inmatriculare invalid!");
}

void ui_returneaza(Lista* lista)
{
	char numar_inmatriculare[105];
	printf("Introduceti numarul de inmatriculare al masinii pe care doriti sa o returnati\n");
	printf("Numarul de inmatriculare:\n");
	printf(">>> ");
	scanf("%s", &numar_inmatriculare);
	int succes = serv_returnare(lista, numar_inmatriculare);
	if (succes) printf("Masina a fost inchiriata cu succes!");
	else printf("Numar de inmatriculare invalid!");
}

void ui_filtrare(Lista* lista)
{
	char categorie[105];
	printf("Introduceti categoria dupa care doriti sa filtrati\n");
	printf(">>> ");
	scanf("%s", &categorie);
	Lista filtered_list = creaza_lista();
	filtered_list = serv_filtrare(lista, categorie);
	if (filtered_list.lungime == 0) printf("Nu exista masini de aceasta categorie!");
	else ui_afiseaza(&filtered_list);
	distruge_lista(&filtered_list);
}

void ui()
{
	//Functia main
	Lista lista = creaza_lista();
	while (1)
	{
		printf("\n");
		main_meniu();
		int comanda;
		printf(">>> ");
		scanf("%d", &comanda);
		printf("\n");
		if (comanda == 1) ui_adauga(&lista);
		if (comanda == 2) ui_modifica(&lista);
		if (comanda == 3) ui_inchiriaza(&lista);
		if (comanda == 4) ui_returneaza(&lista);
		if (comanda == 5) ui_filtrare(&lista);
		if (comanda == 6)
		{
			serv_sortare_model(&lista);
			printf("Lista a fost sortata cu succes!\n");
		}
		if (comanda == 7) ui_afiseaza(&lista);
		if (comanda == 0)
		{
			printf("Se iese din program...");
			distruge_lista(&lista);
			return;
		}
		printf("\n");
	}
}