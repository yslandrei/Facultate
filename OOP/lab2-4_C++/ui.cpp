#include <iostream>
#include <stdio.h>
#include <string.h>
#include "offer.h"
#include "offersList.h"
#include "offersRepository.h"
#include "offersService.h"
#pragma warning(disable : 4996)

void printMenu() {	
	std::cout << "* Adaugarea de noi oferte                                     - add [id], [tip], [suprafata], [adresa], [pret]\n";
	std::cout << "* Stergere oferte                                             - pop [id]\n";
	std::cout << "* Actualizare oferte                                          - mod [oldId], [id], [tip], [suprafata], [adresa], [pret]\n";
	std::cout << "* Vizualizare oferete ordonat dupa pret, tip (cresc/descresc) - srt\n";
	std::cout << "* Vizualizare oferta filtrate dupa un criteriu                - fil [criteriu]\n\n";
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
		args[argsLen++] = std::string(parser);
		parser = strtok(NULL, ", ");
	}
}

void printOffers(offersList* o) {
	for (int i = 0; i < o->size; i++)
		std::cout << "id: " << o->List[i].id << ", tip: " << o->List[i].type << ", suprafata: " << o->List[i].surface << ", adresa: " << o->List[i].adress << ", pret: " << o->List[i].price << "\n";
	std::cout << "\n";
}

void destroyOffers(offersList* o) {
	for (int i = 0; i < o->size; i++) {
		offer p = o->List[i];
		//destroyOffer(&p);
	}
	o->size = 0;
	delete(o->List);
}

void ui(offersList* o) {
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
			addOfferService(o, id, type, surface, adress, price);
			printOffers(o);
		}

		else if (com.substr(0, 3) == "pop") {
			parseCommand(com.substr(4, com.npos), args);
			id = stringToNumber(args[0]);
			popOfferService(o, id);
			printOffers(o);
		}

		else if (com.substr(0, 3) == "mod") {
			parseCommand(com.substr(4, com.npos), args);
			oldId = stringToNumber(args[0]);
			id = stringToNumber(args[1]);
			type = args[2];
			surface = stringToNumber(args[3]);
			adress = args[4];
			price = stringToNumber(args[5]);
			modOfferService(o, oldId, id, type, surface, adress, price);
			printOffers(o);
		}

		else if (com.substr(0, 3) == "srt") {
			offersList sortedO;
			sortListByPriceAndType(o, &sortedO);
			printOffers(&sortedO);
			//delete(sortedO.List);
			//free(sortedO.List);
		}

		else if (com.substr(0, 3) == "fil") {
			offersList filteredO;
			criteria = com.substr(4, com.npos);
			filterListByCriteria(o, &filteredO, criteria);
			printOffers(&filteredO);
			//delete(filteredO.List);
			//free(filteredO.List);
		}

		else if (com[0] == 'q') {
			//delete(o->List);
			//free(o->List);
			return;
		}
	}

}