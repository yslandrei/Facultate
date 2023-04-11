#include "ui.h"



void ui::run() {
	char com[100] = { 0 }, args[10][25] = { 0 };
	ui::clearScreen();
	
	while (true) {
		ui::printMenu();
		cout << "Introduceti comanda(q - quit): ";
		cin.getline(com, 100);
		ui::clearScreen();

		if (strncmp(com, "add", sizeof(char) * 3) == 0) {
			try {
				ui::parseCommand(com + 4, args);
				oService.addOffer(atoi(args[0]), args[1], args[2], args[3], atoi(args[4]));
				ui::printOffers(oService.getAll());
			}
			catch (exception e) {
				cout << e.what() << "\n";
			}
		}

		else if (strncmp(com, "pop", sizeof(char) * 3) == 0) {
			try {
				ui::parseCommand(com + 4, args);
				oService.popOffer(atoi(args[0]));
				ui::printOffers(oService.getAll());
			}
			catch (exception e) {
				cout << e.what() << "\n";
			}
		}

		else if (strncmp(com, "mod", sizeof(char) * 3) == 0) {
			try {
				ui::parseCommand(com + 4, args);
				oService.modOffer(atoi(args[0]), atoi(args[1]), args[2], args[3], args[4], atoi(args[5]));
				ui::printOffers(oService.getAll());
			}
			catch (exception e) {
				cout << e.what() << "\n";
			}
		}

		else if (strncmp(com, "src", sizeof(char) * 3) == 0) {
			try {
				ui::parseCommand(com + 4, args);
				vector<offer> foundOffer;
				foundOffer.push_back(oService.findOffer(args[0]));
				ui::printOffers(foundOffer);
			}
			catch (exception e) {
				cout << e.what() << "\n";
			}
		}

		else if (strncmp(com, "srt", sizeof(char) * 3) == 0) {
			try {
				vector<offer> oSortedList;
				oSortedList = oService.sortOffers(com[4]);
				ui::printOffers(oSortedList);
			}
			catch (exception e) {
				cout << e.what() << "\n";
			}
		}

		else if (strncmp(com, "fil", sizeof(char) * 3) == 0) {
			try {
				vector<offer> oFilteredList;
				oFilteredList = oService.filterOffers(com + 4);
				ui::printOffers(oFilteredList);
			}
			catch (exception e) {
				cout << e.what() << "\n";
			}
		}

		else if (strncmp(com, "q", sizeof(char) * 1) == 0) {
			return;
		}
	}
}
