#include <iostream>
#include <stdio.h>
#include <string.h>
#include "offer.h"
#include "offersList.h"
#include "offersRepository.h"
#include "offersService.h"
#pragma warning(disable : 4996)

void printMenu() {
	printf("* Adaugarea de noi oferte                                     - add [id], [tip], [suprafata], [adresa], [pret]\n");
	printf("* Stergere oferte                                             - pop [id]\n");
	printf("* Actualizare oferte                                          - mod [oldId], [id], [tip], [suprafata], [adresa], [pret]\n");
	printf("* Vizualizare oferete ordonat dupa pret, tip (cresc/descresc) - srt\n");
	printf("* Vizualizare oferta filtrate dupa un criteriu                - fil [criteriu]\n\n");
}

void clearScreen() {
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

void parseCommand(char* com, char args[10][25]) {
	char* parser;
	int argsLen = 0;
	com[strlen(com) - 1] = NULL;
	parser = strtok(com, ", ");
	while (parser != NULL) {
		strcpy(args[argsLen++], parser);
		parser = strtok(NULL, ", ");
	}
}

void printOffers(offersList* o) {
	for (int i = 0; i < o->size; i++)
		printf("id: %d, tip: %s, suprafata: %d, adresa: %s, pret: %d\n", o->List[i].id, o->List[i].type, o->List[i].surface, o->List[i].adress, o->List[i].price);
	printf("\n");
}
/*
void destroyOffers(offersList* o) {
	for (int i = 0; i < o->size; i++) {
		offer p = o->List[i];
		//destroyOffer(&p);
	}
	o->size = 0;
	delete(o->List);
}
*/
void ui(offersList* o) {
	char com[100];
	char args[10][25];

	int oldId, id, surface, price;
	char type[25], adress[25], criteria[25];

	while (1) {
		printMenu();
		printf("Introduceti comanda(q - quit): ");
		fgets(com, sizeof(com), stdin);
		clearScreen();

		if (strncmp(com, "add", sizeof(char) * 3) == 0) {
			parseCommand(com + 4, args);
			id = stringToNumber(args[0]);
			strcpy(type, args[1]);
			surface = stringToNumber(args[2]);
			strcpy(adress, args[3]);
			price = stringToNumber(args[4]);
			addOfferService(o, id, type, surface, adress, price);
			printOffers(o);
		}

		else if (strncmp(com, "pop", sizeof(char) * 3) == 0) {
			parseCommand(com + 4, args);
			id = stringToNumber(args[0]);
			popOfferService(o, id);
			printOffers(o);
		}

		else if (strncmp(com, "mod", sizeof(char) * 3) == 0) {
			parseCommand(com + 4, args);
			oldId = stringToNumber(args[0]);
			id = stringToNumber(args[1]);
			strcpy(type, args[2]);
			surface = stringToNumber(args[3]);
			strcpy(adress, args[4]);
			price = stringToNumber(args[5]);
			modOfferService(o, oldId, id, type, surface, adress, price);
			printOffers(o);
		}

		else if (strncmp(com, "srt", sizeof(char) * 3) == 0) {
			offersList sortedO;
			sortListByPriceAndType(o, &sortedO);
			printOffers(&sortedO);
			//delete(sortedO.List);
			//free(sortedO.List);
		}

		else if (strncmp(com, "fil", sizeof(char) * 3) == 0) {
			offersList filteredO;
			strcpy(criteria, com + 4);
			criteria[strlen(criteria) - 1] = NULL;
			filterListByCriteria(o, &filteredO, criteria);
			printOffers(&filteredO);
			//delete(filteredO.List);
			//free(filteredO.List);
		}

		else if (strncmp(com, "q", sizeof(char) * 1) == 0)
			//delete(o->List);
			//free(o->List);
			return;
	}
}

}

		else if (strncmp(com, "fil", sizeof(char) * 3) == 0) {
			strcpy(criteria, com + 4);
			criteria[strlen(criteria) - 1] = NULL;
			int filteredOListLen = 0;
			offer* filteredOList = getFilteredListByCriteria(oList, oListLen, criteria, &filteredOListLen);
			printOffers(filteredOList, filteredOListLen);
			continue;
		}

		else if (strncmp(com, "q", sizeof(char) * 1) == 0)
			return;

		printOffers(oList, oListLen);
	}

}