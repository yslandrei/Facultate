#include <QtWidgets/QApplication>

#include "gui.h"


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    ProductRepository pRepo;
    ProductService pService(pRepo);
    gui GUI(pService);
    GUI.show();

    return a.exec();
}
