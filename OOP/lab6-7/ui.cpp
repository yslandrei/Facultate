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
				cout << "Oferte:\n";
				ui::printOffers(oService.getAll());
				cout << "Cos:\n";
				ui::printOffers(cService.getAll());
			}
			catch (validationException e) { cout << e << "\n"; }
			catch (repositoryException e) { cout << e << "\n"; }
		}

		else if (strncmp(com, "pop", sizeof(char) * 3) == 0) {
			try {
				ui::parseCommand(com + 4, args);
				oService.popOffer(atoi(args[0]));
				cout << "Oferte:\n";
				ui::printOffers(oService.getAll());
				cout << "Cos:\n";
				ui::printOffers(cService.getAll());
			}
			catch (validationException e) { cout << e << "\n"; }
			catch (repositoryException e) { cout << e << "\n"; }
		}

		else if (strncmp(com, "mod", sizeof(char) * 3) == 0) {
			try {
				ui::parseCommand(com + 4, args);
				oService.modOffer(atoi(args[0]), atoi(args[1]), args[2], args[3], args[4], atoi(args[5]));
				cout << "Oferte:\n";
				ui::printOffers(oService.getAll());
				cout << "Cos:\n";
				ui::printOffers(cService.getAll());
			}
			catch (validationException e) { cout << e << "\n"; }
			catch (repositoryException e) { cout << e << "\n"; }
		}

		else if (strncmp(com, "src", sizeof(char) * 3) == 0) {
			try {
				ui::parseCommand(com + 4, args);
				vector<offer> foundOffer;
				foundOffer.push_back(oService.findOffer(args[0]));
				ui::printOffers(foundOffer);
			}
			catch (validationException e) { cout << e << "\n"; }
			catch (repositoryException e) { cout << e << "\n"; }
		}

		else if (strncmp(com, "srt", sizeof(char) * 3) == 0) {
			try {
				vector<offer> oSortedList;
				oSortedList = oService.sortOffers(com[4]);
				cout << "Oferte sortate\n";
				ui::printOffers(oSortedList);
			}
			catch (validationException e) { cout << e << "\n"; }
			catch (repositoryException e) { cout << e << "\n"; }
		}

		else if (strncmp(com, "fil", sizeof(char) * 3) == 0) {
			try {
				vector<offer> oFilteredList;
				oFilteredList = oService.filterOffers(com + 4);
				cout << "Oferte filtrate\n";
				ui::printOffers(oFilteredList);
			}
			catch (validationException e) { cout << e << "\n"; }
			catch (repositoryException e) { cout << e << "\n"; }
		}

		else if (strncmp(com, "adc", sizeof(char) * 3) == 0) {
			try {
				ui::parseCommand(com + 4, args);
				cService.addOffer(args[0]);
				cout << "Oferte:\n";
				ui::printOffers(oService.getAll());
				cout << "Cos:\n";
				ui::printOffers(cService.getAll());
			}
			catch (validationException e) { cout << e << "\n"; }
			catch (repositoryException e) { cout << e << "\n"; }
		}

		else if (strncmp(com, "emp", sizeof(char) * 3) == 0) {
			try {
				cService.emptyCart();
				cout << "Oferte:\n";
				ui::printOffers(oService.getAll());
				cout << "Cos:\n";
				ui::printOffers(cService.getAll());
			}
			catch (validationException e) { cout << e << "\n"; }
			catch (repositoryException e) { cout << e << "\n"; }
		}

		else if (strncmp(com, "gen", sizeof(char) * 3) == 0) {
			try {
				ui::parseCommand(com + 4, args);
				cService.generateCart(atoi(args[0]));
				cout << "Oferte:\n";
				ui::printOffers(oService.getAll());
				cout << "Cos:\n";
				ui::printOffers(cService.getAll());
			}
			catch (validationException e) { cout << e << "\n"; }
			catch (repositoryException e) { cout << e << "\n"; }
		}

		else if (strncmp(com, "exp", sizeof(char) * 3) == 0) {
			try {
				ui::parseCommand(com + 4, args);
				cService.exportCart(args[0]);
				cout << "Oferte:\n";
				ui::printOffers(oService.getAll());
				cout << "Cos:\n";
				ui::printOffers(cService.getAll());
			}
			catch (validationException e) { cout << e << "\n"; }
			catch (repositoryException e) { cout << e << "\n"; }
		}

		else if (strncmp(com, "tip", sizeof(char) * 3) == 0) {
			try {
				ui::parseCommand(com + 4, args);
				cout << "Au fost gasite " << cService.typeOfCart(args[0]) << " oferte in cos de acel tip\n\n";
				cout << "Oferte:\n";
				ui::printOffers(oService.getAll());
				cout << "Cos:\n";
				ui::printOffers(cService.getAll());
			}
			catch (validationException e) { cout << e << "\n"; }
			catch (repositoryException e) { cout << e << "\n"; }
		}

		else if (strncmp(com, "q", sizeof(char) * 1) == 0) {
			return;
		}
	}
}
