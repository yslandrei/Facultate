/********************************************************************************
** Form generated from reading UI file 'testPractice2.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESTPRACTICE2_H
#define UI_TESTPRACTICE2_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_testPractice2Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *testPractice2Class)
    {
        if (testPractice2Class->objectName().isEmpty())
            testPractice2Class->setObjectName("testPractice2Class");
        testPractice2Class->resize(600, 400);
        menuBar = new QMenuBar(testPractice2Class);
        menuBar->setObjectName("menuBar");
        testPractice2Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(testPractice2Class);
        mainToolBar->setObjectName("mainToolBar");
        testPractice2Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(testPractice2Class);
        centralWidget->setObjectName("centralWidget");
        testPractice2Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(testPractice2Class);
        statusBar->setObjectName("statusBar");
        testPractice2Class->setStatusBar(statusBar);

        retranslateUi(testPractice2Class);

        QMetaObject::connectSlotsByName(testPractice2Class);
    } // setupUi

    void retranslateUi(QMainWindow *testPractice2Class)
    {
        testPractice2Class->setWindowTitle(QCoreApplication::translate("testPractice2Class", "testPractice2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class testPractice2Class: public Ui_testPractice2Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTPRACTICE2_H
