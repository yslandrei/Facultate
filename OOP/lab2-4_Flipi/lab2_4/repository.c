#pragma once
#include "repository.h"
#include <stdlib.h>
#include <string.h>
#include <string.h>

Lista creaza_lista() 
{
	//Functia creaza o lista goala
	Lista lista;
	lista.capacitate = 2;
	lista.lungime = 0;
	lista.elemente = malloc(sizeof(ElemType) * lista.capacitate);
	return lista;
}

void distruge_lista(Lista* lista)
{
	//Functia elibereaza spatiul de memorie alocat listei
	for (int i = 0; i < lista->lungime; i++)
	{
		ElemType element = get(lista, i);
		distruge_masina(&element);
	}
	lista->lungime = 0;
	free(lista->elemente);
}

ElemType get(Lista* lista, int poz)
{
	//Lista returneaza elementul de pe o pozitia data
	return lista->elemente[poz];
}

void seteaza_element(Lista* lista, int pozitie, ElemType element)
{
	//Adauaga un anumit element la o anumita pozitie din lista
	lista->elemente[pozitie] = element;
}

int size(Lista* lista)
{
	//Functia returneaza lungimea listei
	return lista->lungime;
}

void resize(Lista* lista)
{
	//Functia aloca memorie aditionala vectorului dinamic
	int capacitate_noua = lista->capacitate * 2;
	ElemType* elemente_auxiliare = malloc(capacitate_noua * sizeof(ElemType));
	for (int i = 0; i < lista->lungime; i++) elemente_auxiliare[i] = lista->elemente[i];
	free(lista->elemente);
	lista->capacitate = capacitate_noua;
	lista->elemente = elemente_auxiliare;
}

void adauga_masina(Lista* lista, ElemType element)
{
	//Adauga un nou element in lista
	if (lista->lungime == lista->capacitate) resize(lista);
	lista->elemente[lista->lungime] = element;
	lista->lungime++;
}

Lista copy_list(Lista* lista)
{
	//Functia creaza o copie la lista transmisa ca parametru
	Lista copie_lista = creaza_lista();
	for (int i = 0; i < lista->lungime; i++)
	{
		ElemType element = get(lista, i);
		adauga_masina(&copie_lista, copiaza_masina(element));
	}
	return copie_lista;
}
