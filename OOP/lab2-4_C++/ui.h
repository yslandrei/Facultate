#pragma once

void printMenu();

void clearScreen();

void printOffers(offersList* o);

void parseCommand(std::string com, std::string* args);

void ui(offersList* o);