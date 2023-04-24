#pragma once
#include <iostream>
#include "offersService.h"
#include "cartService.h"

using std::cin;
using std::cout;

class ui {
private:
	offersService& oService;
	cartService& cService;

	static void printMenu() {
		cout << "Adaugare oferta                                - add [id], [nume], [dest], [tip], [pret]\n";
		cout << "Stergere oferta                                - pop [id]\n";
		cout << "Modificare oferta                              - mod [oldId], [id], [nume], [dest], [tip], [pret]\n";
		cout << "Cautare oferta                                 - src [nume]\n";
		cout << "Sortare oferte                                 - srt [n/d/p]\n";
		cout << "Filtrare oferte                                - fil [criteriu]\n";
		cout << "Adaugare oferta in cos                         - adc [nume]\n";
		cout << "Golire cos                                     - emp\n";
		cout << "Genereaza cos                                  - gen [nr]\n";
		cout << "Exporta cos                                    - exp [nume]\n";
		cout << "\n";
	}

	static void clearScreen() {
		cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	}

	static void parseCommand(char* com, char args[10][25]) {
		char* parser;
		int argsLen = 0;
		parser = strtok(com, ", ");
		while (parser != NULL) {
			strcpy(args[argsLen++], parser);
			parser = strtok(NULL, ", ");
		}
	}

	static void printOffers(const vector<offer>& oList) {
		for (int i = 0; i < oList.size(); i++)
			cout << "id: " << oList[i].getId() << ", nume: " << oList[i].getName() << ", destinatie: " << oList[i].getDest() << ", tip: " << oList[i].getType() << ", pret: " << oList[i].getPrice() << "\n";
		cout << "\n";
	}

public:
	ui(offersService& oService, cartService& cService) :
		oService{ oService },
		cService{ cService }
	{}

	ui(const ui& ot) = delete;

	void run();
};

