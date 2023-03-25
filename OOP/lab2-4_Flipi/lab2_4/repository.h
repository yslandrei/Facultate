#pragma once
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "domain.h"

typedef Masina ElemType;

typedef struct
{
	ElemType* elemente;
	int lungime;
	int capacitate;
}Lista;

Lista creaza_lista();

void distruge_lista(Lista* lista);

ElemType get(Lista* lista, int poz);

void seteaza_element(Lista* lista, int pozitie, ElemType element);

int size(Lista* lista);

void adauga_masina(Lista* lista, ElemType element);

Lista copy_list(Lista* lista);