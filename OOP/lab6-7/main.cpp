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
	testAddOfferCartRepo();
	testEmptyCartRepo();
	testExportCartRepo();
	testValidate();
	testAddOfferService();
	testModOfferService();
	testPopOfferService();
	testFindOfferService();
	testSortOffersService();
	testFilterOffersService();
	testAddOfferCartService();
	testEmptyCartService();
	testExportCartService();
	testGenerateCartService();
	testTypeOfCartService();
}

int main() {
	testAll();
	{
		offersRepository oRepo;
		cartRepository cRepo;
		offersService oService(oRepo);
		cartService cService(oRepo, cRepo);
		ui UI(oService, cService);
		UI.run();
	}
	
	_CrtDumpMemoryLeaks();
}