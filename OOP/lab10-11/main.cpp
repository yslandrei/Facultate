#include "testDomain.h"
#include "testInfrastructure.h"
#include "testValidate.h"
#include "testService.h"
#include "gui.h"

#include <QtWidgets/QApplication>
#include <QListWidget>
#include <qboxlayout.h>
#include <qformlayout.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>


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

int main(int argc, char *argv[])
{
	testAll();

	QApplication app(argc, argv);
	
	offersRepository oRepo;
	cartRepository cRepo;
	offersService oService(oRepo);
	oService.addOffer(0, "Paris", "Franta, Paris", "Oras", 5500);
	oService.addOffer(1, "Milano", "Italia, Milano", "Oras", 6500);
	oService.addOffer(2, "Havana", "Cuba, Havana", "Litoral", 3000);
	oService.addOffer(3, "Paltinis", "Romania, Sibiu", "Munte", 2000);
	cartService cService(oRepo, cRepo);
	gui GUI(oService, cService);
	GUI.run();

    return app.exec();
}
