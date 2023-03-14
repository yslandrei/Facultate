#include <iostream>
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

void parseCommand(std::string com, std::string* args) {
	char* parser;
	int argsLen = 0;
	char* comCStr = strdup(com.c_str());
	parser = strtok(comCStr, ", ");
	while (parser != NULL) {
		args[argsLen++] = parser;
		parser = strtok(NULL, ", ");
	}
}

void printOffers(offer* oList, int oListLen) {
	for (int i = 0; i < oListLen; i++)
		std::cout << "id: " << oList[i].id << ", tip: " << oList[i].type << ", suprafata: " << oList[i].surface << ", adresa: " << oList[i].adress << ", pret: " << oList[i].price << "\n";
	std::cout << "\n";
}

void ui(offer* oList, int oListLen) {
	std::string com;
	std::string args[10];

	int oldId, id, surface, price;
	std::string type, adress, criteria;

	while (1) {
		printMenu();
		printf("Introduceti comanda(q - quit): ");
		getline(std::cin, com);
		clearScreen();

		if (com.substr(0, 3) == "add") {
			parseCommand(com.substr(4, com.npos), args);
			id = stringToNumber(args[0]);
			type = args[1];
			surface = stringToNumber(args[2]);
			adress = args[3];
			price = stringToNumber(args[4]);
			addOfferService(oList, &oListLen, id, type, surface, adress, price);
			printOffers(oList, oListLen);
		}

		else if (com.substr(0, 3) == "pop") {
			parseCommand(com.substr(4, com.npos), args);
			id = stringToNumber(args[0]);
			popOfferService(oList, &oListLen, id);
			printOffers(oList, oListLen);
		}

		else if (com.substr(0, 3) == "mod") {
			parseCommand(com.substr(4, com.npos), args);
			oldId = stringToNumber(args[0]);
			id = stringToNumber(args[1]);
			type = args[2];
			surface = stringToNumber(args[3]);
			adress = args[4];
			price = stringToNumber(args[5]);
			modOfferService(oList, &oListLen, oldId, id, type, surface, adress, price);
			printOffers(oList, oListLen);
		}

		else if (com.substr(0, 3) == "srt") {
			offer sortedOList[100];
			sortListByPriceAndType(oList, oListLen, sortedOList);
			printOffers(sortedOList, oListLen);
		}

		else if (com.substr(0, 3) == "fil") {
			criteria = com.substr(4, com.npos);
			int filteredOListLen = 0;
			offer filteredOList[100];
			filterListByCriteria(oList, oListLen, criteria, filteredOList, &filteredOListLen);
			printOffers(filteredOList, filteredOListLen);
		}

		else if (com[0] == 'q')
			return;

	}

}