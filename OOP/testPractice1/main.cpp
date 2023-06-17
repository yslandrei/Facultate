#include <QtWidgets/QApplication>

#include "gui.h"
#include "closedgui.h"
#include "opengui.h"
#include "inprogressgui.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    taskRepository tRepo;
    taskService tService(tRepo);
    gui GUI(tService);
    ClosedGui cGUI(tService);
    OpenGui oGUI(tService);
    InProgressGui iGUI(tService);
    tService.addObserver(&GUI);
    tService.addObserver(&cGUI);
    tService.addObserver(&oGUI);
    tService.addObserver(&iGUI);
    GUI.show();
    cGUI.show();
    iGUI.show();
    oGUI.show();

    return a.exec();
}
