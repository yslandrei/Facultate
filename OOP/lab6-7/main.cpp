#include "testDomain.h"
#include "testInfrastructure.h"
#include "testValidate.h"
#include "testService.h"

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

	_CrtDumpMemoryLeaks();
}