#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_testPractice2.h"

class testPractice2 : public QMainWindow
{
    Q_OBJECT

public:
    testPractice2(QWidget *parent = nullptr);
    ~testPractice2();

private:
    Ui::testPractice2Class ui;
};
