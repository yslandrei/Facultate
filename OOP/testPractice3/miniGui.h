#pragma once
#include "productService.h"
#include "observer.h"
#include <QAbstractTableModel>
#include <QBrush>
#include <Qt>
#include <QFont>
#include <vector>
#include <qdebug.h>
#include <QAbstractTableModel>
#include <QBrush>
#include <Qt>
#include <QFont>
#include <vector>
#include <qdebug.h>
#include <QTableView>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QMessageBox>
#include <QLineEdit>


class miniGui : public observer {
private:
    ProductService& pService;
    string type;

    QWidget* window;
    QHBoxLayout* windowLayout;
    QLabel* number;

public:
    miniGui(string type, ProductService& pService) : type{ type }, pService { pService } {
        pService.addObserver(this);
        initGUI();
    }

    QString countType() {
        int count = 0;
        for (auto& p : pService.getAll()) {
            if (p.getType() == type)
                count++;
        }
        return QString::fromStdString(to_string(count));
    }

    void initGUI() {
        window = new QWidget;
        window->setWindowTitle(QString::fromStdString(type));
        window->setMinimumWidth(200);
        window->setMinimumHeight(200);
        
        windowLayout = new QHBoxLayout;
        
        number = new QLabel(countType());

        windowLayout->addWidget(number);

        window->setLayout(windowLayout);
    }

    void update() override {
        number->setText(countType());
    }

    void show() {
        window->show();
    }
};

