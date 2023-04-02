#include "testService.h"

void testAddOfferService() {
	offersRepository oRepo;
	offersService oService(oRepo);
	
	oService.addOffer(0, "nume0", "dest0", "tip0", 100);
	assert(oService.getAll()[0].getId() == 0);
}

void testPopOfferService() {
	offersRepository oRepo;
	offersService oService(oRepo);

	oService.addOffer(0, "nume0", "dest0", "tip0", 100);
	oService.popOffer(0);
	assert(oService.getAll().size() == 0);
}

void testModOfferService() {
	offersRepository oRepo;
	offersService oService(oRepo);

	oService.addOffer(0, "nume0", "dest0", "tip0", 100);
	oService.modOffer(0, 1, "nume1", "dest1", "tip1", 100);
	assert(oService.getAll()[0].getId() == 1);
}

void testFindOfferService() {
	offersRepository oRepo;
	offersService oService(oRepo);

	oService.addOffer(0, "nume0", "dest0", "tip0", 100);
	oService.addOffer(1, "nume1", "dest1", "tip1", 100);
	oService.addOffer(2, "nume2", "dest2", "tip2", 100);
	assert(oService.findOffer("nume1") == true);
}

void testSortOffersService() {
	offersRepository oRepo;
	offersService oService(oRepo);
	vector<offer> oSortedList;

	oService.addOffer(0, "nume3", "dest0", "tip0", 100);
	oService.addOffer(1, "nume2", "dest1", "tip1", 200);
	oService.addOffer(2, "nume1", "dest2", "tip2", 200);
	oService.addOffer(3, "nume0", "dest3", "tip3", 500);
	oSortedList = oService.sortOffers('n');
	assert(oSortedList[0].getId() == 3);
	assert(oSortedList[3].getId() == 0);
	oSortedList = oService.sortOffers('d');
	assert(oSortedList[0].getId() == 0);
	assert(oSortedList[3].getId() == 3); 
	oSortedList = oService.sortOffers('p');
	assert(oSortedList[0].getId() == 3);
	assert(oSortedList[3].getId() == 0);
}

void testFilterOffersService() {
	offersRepository oRepo;
	offersService oService(oRepo);

	oService.addOffer(0, "nume3", "dest0", "tip0", 100);
	oService.addOffer(1, "nume2", "dest1", "tip1", 200);
	oService.addOffer(2, "nume1", "dest2", "tip2", 150);
	oService.addOffer(3, "nume0", "dest3", "tip3", 500);
	char criteria[100] = "p<200 n>=nume0 d<=dest3 t>tip p=100";
	vector<offer> oFilteredList = oService.filterOffers(criteria);
	assert(oFilteredList.size() == 1);
}
