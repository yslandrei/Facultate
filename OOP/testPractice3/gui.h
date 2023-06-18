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

#include "model.h"
#include "miniGui.h"

class gui : public observer {
private:
    ProductService& pService;
    vector<string> types;

	QWidget* window, * form, * rgt;
    QVBoxLayout* rgtLayout;
    QHBoxLayout* windowLayout;
    QFormLayout* formLayout;
    QTableView* table;
    MyTableModel* model;
    QLineEdit* idEdit, * nameEdit, * typeEdit, * priceEdit;
    QLabel* idLbl, * nameLbl, * typeLbl, * priceLbl;
    QPushButton* addBtn, * modBtn;
    QSlider* slider;

public:
    gui(ProductService& pService) : pService{ pService } {
		pService.addObserver(this);
		initGUI();
        initSignals();
        vector<Product> oList = pService.getAll();
        for(int i = 0; i < oList.size(); i++) {
			if (std::find(types.begin(), types.end(), oList[i].getType()) == types.end()) {
				types.push_back(oList[i].getType());
				(new miniGui(oList[i].getType(), pService))->show();
			}
		}
    }

    void initGUI() {
        window = new QWidget;
        window->setMinimumWidth(880);
        window->setMinimumHeight(400);
        windowLayout = new QHBoxLayout;

            table = new QTableView;
            model = new MyTableModel(pService.getAll(), pService.filterByPrice(0));
            table->setModel(model);

        windowLayout->addWidget(table);

            rgt = new QWidget;
            rgtLayout = new QVBoxLayout;

                form = new QWidget;
                formLayout = new QFormLayout;
                    idLbl = new QLabel("ID");
                    idEdit = new QLineEdit;
                formLayout->addRow(idLbl, idEdit);
                    nameLbl = new QLabel("Nume");
                    nameEdit = new QLineEdit;
                formLayout->addRow(nameLbl, nameEdit);
                    typeLbl = new QLabel("Tip");
                    typeEdit = new QLineEdit;
                formLayout->addRow(typeLbl, typeEdit);
                    priceLbl = new QLabel("Pret");
                    priceEdit = new QLineEdit;
                formLayout->addRow(priceLbl, priceEdit);
                form->setLayout(formLayout);

            rgtLayout->addWidget(form);

                addBtn = new QPushButton("Adauga");
            
           rgtLayout->addWidget(addBtn);

                modBtn = new QPushButton("Modifica");

            rgtLayout->addWidget(modBtn);

                slider = new QSlider;
                slider->setMinimum(1);
                slider->setMaximum(100);
                slider->setTickInterval(10);
                slider->setOrientation(Qt::Horizontal);

            rgtLayout->addWidget(slider);

            rgt->setLayout(rgtLayout);

        windowLayout->addWidget(rgt);
        window->setLayout(windowLayout);
    }

    void initSignals() {
        //connect QTableView selection change signal to change the line edits values
        QObject::connect(table->selectionModel(), &QItemSelectionModel::selectionChanged, [&]() {
			if (table->selectionModel()->selectedIndexes().isEmpty()) {
				idEdit->setText("");
				nameEdit->setText("");
				typeEdit->setText("");
				priceEdit->setText("");
				return;
			}
			int selectedRow = table->selectionModel()->selectedIndexes().at(0).row();
			Product p = pService.getAll()[selectedRow];
			idEdit->setText(QString::number(p.getId()));
			nameEdit->setText(QString::fromStdString(p.getName()));
			typeEdit->setText(QString::fromStdString(p.getType()));
			priceEdit->setText(QString::number(p.getPrice()));
		});
        
        //connect the add button signal to add a product
        QObject::connect(addBtn, &QPushButton::clicked, [&]() {
            try {
                int id = idEdit->text().toInt();
                string name = nameEdit->text().toStdString();
                string type = typeEdit->text().toStdString();
                int price = priceEdit->text().toInt();
                pService.addProduct(id, name, type, price);
                reloadData();

                if (std::find(types.begin(), types.end(), type) == types.end()) {
					types.push_back(type);
                    (new miniGui(type, pService))->show();
				}
			}
			catch (std::exception& e) {
                QMessageBox::critical(nullptr, "Error", e.what());
			}
          });

		//connect the modify button signal to modify a product
		QObject::connect(modBtn, &QPushButton::clicked, [&]() {
			try {
                int id = idEdit->text().toInt();
                string name = nameEdit->text().toStdString();
                string type = typeEdit->text().toStdString();
                int price = priceEdit->text().toInt();
                pService.modProduct(id, name, type, price);
                reloadData();
			}
			catch (std::exception& e) {
                QMessageBox::critical(nullptr, "Error", e.what());
			}
		});

		//connect the slider signal to filter the products
        QObject::connect(slider, &QSlider::valueChanged, [&]() {
            reloadData();
		});
    }

    void reloadData() {
        model->setProducts(pService.getAll(), pService.filterByPrice(slider->value()));
    }

	void update() override {
        reloadData();
	}

    void show() {
		window->show();
	}
};

