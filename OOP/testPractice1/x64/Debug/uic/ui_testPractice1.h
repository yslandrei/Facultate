/********************************************************************************
** Form generated from reading UI file 'testPractice1.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESTPRACTICE1_H
#define UI_TESTPRACTICE1_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_testPractice1Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *testPractice1Class)
    {
        if (testPractice1Class->objectName().isEmpty())
            testPractice1Class->setObjectName("testPractice1Class");
        testPractice1Class->resize(600, 400);
        menuBar = new QMenuBar(testPractice1Class);
        menuBar->setObjectName("menuBar");
        testPractice1Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(testPractice1Class);
        mainToolBar->setObjectName("mainToolBar");
        testPractice1Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(testPractice1Class);
        centralWidget->setObjectName("centralWidget");
        testPractice1Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(testPractice1Class);
        statusBar->setObjectName("statusBar");
        testPractice1Class->setStatusBar(statusBar);

        retranslateUi(testPractice1Class);

        QMetaObject::connectSlotsByName(testPractice1Class);
    } // setupUi

    void retranslateUi(QMainWindow *testPractice1Class)
    {
        testPractice1Class->setWindowTitle(QCoreApplication::translate("testPractice1Class", "testPractice1", nullptr));
    } // retranslateUi

};

namespace Ui {
    class testPractice1Class: public Ui_testPractice1Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTPRACTICE1_H
