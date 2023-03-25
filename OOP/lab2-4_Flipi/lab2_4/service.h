#pragma once
#define MYSORT_H_
#define _CRTDB_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "repository.h"

typedef int(*FunctieComparare)(Masina* o1, Masina* o2);

int serv_adauga(Lista* lista, char* nr_inmatr, char* model, char* categorie);

int cauta_id(Lista* lista, char* nr_inmatr);

int serv_modifica(Lista* lista, char* nr_inmatr, char* model, char* categorie);

int serv_inchiriaza(Lista* lista, char* nr_inmatr);

int serv_returnare(Lista* lista, char* nr_inmatr);

Lista serv_filtrare(Lista* lista, char* categ);

void serv_sortare(Lista* lista, FunctieComparare cmpF);

void serv_sortare_model(Lista* lista);

void serv_sortare_categorie(Lista* lista);