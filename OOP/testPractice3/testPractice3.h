#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_testPractice3.h"

class testPractice3 : public QMainWindow
{
    Q_OBJECT

public:
    testPractice3(QWidget *parent = nullptr);
    ~testPractice3();

private:
    Ui::testPractice3Class ui;
};
