#include <QtWidgets/QApplication>
#include "mainGui.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    StudentRepo sRepo;
    StudentService sService(sRepo);
    MainGui mainGui(sService);
    mainGui.show();

    return a.exec();
}
