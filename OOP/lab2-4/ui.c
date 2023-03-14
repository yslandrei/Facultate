#include <stdio.h>
#include <string.h>
#include "offer.h"
#include "offersRepository.h"
#include "offersService.h"
#pragma warning(disable : 4996)

void printMenu() {	
	printf("* Adaugarea de noi oferte				      - add [id], [tip], [suprafata], [adresa], [pret]\n");
	printf("* Actualizare oferte				 	      - pop [id]\n");
	printf("* Stergere oferta					      - mod [oldId], [id], [tip], [suprafata], [adresa], [pret]\n");
	printf("* Vizualizare oferete ordonat dupa pret, tip (cresc/descresc) - srt\n");
	printf("* Vizualizare oferta filtrate dupa un criteriu		      - fil [criteriu]\n\n");
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

void printOffers(offer* oList, int oListLen) {
	for (int i = 0; i < oListLen; i++)
		printf("id: %d, tip: %s, suprafata: %d, adresa: %s, pret: %d\n", oList[i].id, oList[i].type, oList[i].surface, oList[i].adress, oList[i].price);
	printf("\n");
}

void ui(offer* oList, int oListLen) {
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
			addOfferService(oList, &oListLen, id, type, surface, adress, price);

		}

		else if (strncmp(com, "pop", sizeof(char) * 3) == 0) {
			parseCommand(com + 4, args);
			id = stringToNumber(args[0]);
			popOfferService(oList, &oListLen, id);
		}

		else if (strncmp(com, "mod", sizeof(char) * 3) == 0) {
			parseCommand(com + 4, args);
			oldId = stringToNumber(args[0]);
			id = stringToNumber(args[1]);
			strcpy(type, args[2]);
			surface = stringToNumber(args[3]);
			strcpy(adress, args[4]);
			price = stringToNumber(args[5]);
			modOfferService(oList, &oListLen, oldId, id, type, surface, adress, price);
		}

		else if (strncmp(com, "srt", sizeof(char) * 3) == 0) {
			offer* sortedOList = getSortedListByPriceAndType(oList, oListLen);
			printOffers(sortedOList, oListLen);
			continue;
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