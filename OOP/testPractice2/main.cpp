#include <QtWidgets/QApplication>

#include "gui.h"
#include "rankGui.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
 
    songRepository sRepo;
    songService sService(sRepo);
    gui GUI(sService);
    GUI.show();
    rankGui RGUI(sService);
    RGUI.show();


    return a.exec();
}
