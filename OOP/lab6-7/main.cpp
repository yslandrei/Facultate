#include "testDomain.h"
#include "testInfrastructure.h"
#include "testValidate.h"
#include "testService.h"
#include "ui.h"

void testAll() {
	testOffer();
	testAddOfferRepo();
	testPopOfferRepo();
	testModOfferRepo();
	testValidate();
	testAddOfferService();
	testModOfferService();
	testPopOfferService();
	testFindOfferService();
	testFilterOffersService();
	testSortOffersService();
}

int main() {
	testAll();

	offersRepository oRepo;
	offersService oService(oRepo);
	ui UI(oService);
	UI.run();

	_CrtDumpMemoryLeaks();
}