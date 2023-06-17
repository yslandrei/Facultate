#include <QtWidgets/QApplication>

#include "gui.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
 
    songRepository sRepo;
    songService sService(sRepo);
    gui GUI(sService);
    GUI.show();
    
    return a.exec();
}
