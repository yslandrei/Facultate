#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_testPractice1.h"

class testPractice1 : public QMainWindow
{
    Q_OBJECT

public:
    testPractice1(QWidget *parent = nullptr);
    ~testPractice1();

private:
    Ui::testPractice1Class ui;
};
