#include "testInfrastructure.h"

void testAddOfferRepo() {
	offersRepository oRepo;
	
	oRepo.addOffer(offer(0, "nume0", "dest0", "tip0", 100));
	assert(oRepo.getAll().size() == 1);
	try {
		oRepo.addOffer(offer(0, "nume1", "dest1", "tip1", 100)); assert(false);
	}
	catch (exception e){
		assert(true);
	}
	oRepo.addOffer(offer(1, "nume1", "dest1", "tip1", 100));
	assert(oRepo.getAll().size() == 2);
}

void testPopOfferRepo() {
	offersRepository oRepo;

	oRepo.addOffer(offer(0, "nume0", "dest0", "tip0", 100));
	oRepo.addOffer(offer(1, "nume1", "dest1", "tip1", 100));
	oRepo.popOffer(0);
	assert(oRepo.getAll().size() == 1);
	try {
		oRepo.popOffer(0); assert(false);
	}
	catch (exception e) {
		assert(true);
	}
	assert(oRepo.getAll()[0].getId() == 1);
}

void testModOfferRepo() {
	offersRepository oRepo;

	oRepo.addOffer(offer(0, "nume0", "dest0", "tip0", 100));
	oRepo.addOffer(offer(1, "nume1", "dest1", "tip1", 100));
	oRepo.modOffer(1, offer(2, "nume2", "dest2", "tip2", 100));
	assert(oRepo.getAll()[1].getId() == 2);
	assert(oRepo.getAll()[1].getName() == "nume2");
	assert(oRepo.getAll()[1].getDest() == "dest2");
	assert(oRepo.getAll()[1].getType() == "tip2");
	assert(oRepo.getAll()[1].getPrice() == 100);
	try {
		oRepo.modOffer(1, offer(2, "nume2", "dest2", "tip2", 100)); assert(false);
	}
	catch (exception e) {
		assert(true);
	}
}


void testAddOfferCartRepo() {
	cartRepository cRepo;

	cRepo.addOffer(offer(0, "nume0", "dest0", "tip0", 100));
	assert(cRepo.getAll().size() == 1);
	try {
		cRepo.addOffer(offer(0, "nume1", "dest1", "tip1", 100)); assert(false);
	}
	catch (exception e) {
		assert(true);
	}
	cRepo.addOffer(offer(1, "nume1", "dest1", "tip1", 100));
	assert(cRepo.getAll().size() == 2);
}

void testEmptyCartRepo() {
	cartRepository cRepo;

	cRepo.addOffer(offer(0, "nume0", "dest0", "tip0", 100));
	cRepo.addOffer(offer(1, "nume1", "dest1", "tip1", 100));
	cRepo.emptyCart();
	assert(cRepo.getAll().size() == 0);
}

void testExportCartRepo() {
	cartRepository cRepo;

	cRepo.addOffer(offer(0, "nume0", "dest0", "tip0", 100));
	cRepo.addOffer(offer(1, "nume1", "dest1", "tip1", 100));
	cRepo.exportCart("test");
}
