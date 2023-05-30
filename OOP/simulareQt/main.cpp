#include <QtWidgets/QApplication>
#include "contactRepo.h"
#include "contactService.h"
#include "gui.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    contactRepo cRepo;
    contactService cService(cRepo);

    GUI gui(cService);

    return app.exec();
}
