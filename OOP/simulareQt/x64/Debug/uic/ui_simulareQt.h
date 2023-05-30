/********************************************************************************
** Form generated from reading UI file 'simulareQt.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIMULAREQT_H
#define UI_SIMULAREQT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_simulareQtClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *simulareQtClass)
    {
        if (simulareQtClass->objectName().isEmpty())
            simulareQtClass->setObjectName("simulareQtClass");
        simulareQtClass->resize(600, 400);
        menuBar = new QMenuBar(simulareQtClass);
        menuBar->setObjectName("menuBar");
        simulareQtClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(simulareQtClass);
        mainToolBar->setObjectName("mainToolBar");
        simulareQtClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(simulareQtClass);
        centralWidget->setObjectName("centralWidget");
        simulareQtClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(simulareQtClass);
        statusBar->setObjectName("statusBar");
        simulareQtClass->setStatusBar(statusBar);

        retranslateUi(simulareQtClass);

        QMetaObject::connectSlotsByName(simulareQtClass);
    } // setupUi

    void retranslateUi(QMainWindow *simulareQtClass)
    {
        simulareQtClass->setWindowTitle(QCoreApplication::translate("simulareQtClass", "simulareQt", nullptr));
    } // retranslateUi

};

namespace Ui {
    class simulareQtClass: public Ui_simulareQtClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIMULAREQT_H
