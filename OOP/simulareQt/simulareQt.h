#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_simulareQt.h"

class simulareQt : public QMainWindow
{
    Q_OBJECT

public:
    simulareQt(QWidget *parent = nullptr);
    ~simulareQt();

private:
    Ui::simulareQtClass ui;
};
