#include "gui.h"

void gui::initGUI() {
	window = new QWidget();
	window->setWindowTitle("Tourist Offers");
	windowLayout = new QHBoxLayout;

	lftBox = new QWidget();
	lftBoxLayout = new QVBoxLayout();

	list = new QTableView;
	model = new MyTableModel(oService.getAll());
	//list->setModel(model);

	btnsSort = new QWidget;
	btnsSortLayout = new QHBoxLayout();
	btnSortN = new QPushButton("&Sort By Name");
	btnsSortLayout->addWidget(btnSortN);
	btnSortD = new QPushButton("&Sort By Destination");
	btnsSortLayout->addWidget(btnSortD);
	btnSortPT = new QPushButton("&Sort By Price and Type");
	btnsSortLayout->addWidget(btnSortPT);
	btnsSort->setLayout(btnsSortLayout);
		
	lftBoxLayout->addWidget(list);
	lftBoxLayout->addWidget(btnsSort);
	lftBox->setLayout(lftBoxLayout);

	rgtBox = new QWidget();
	rgtBoxLayout = new QVBoxLayout();

	forms = new QWidget();
	formsLayout = new QFormLayout();
	lblId = new QLabel("ID");
	txtId = new QLineEdit;
	formsLayout->addRow(lblId, txtId);
	lblName = new QLabel("Name");
	txtName = new QLineEdit;
	formsLayout->addRow(lblName, txtName);
	lblDest = new QLabel("Destination");
	txtDest = new QLineEdit;
	formsLayout->addRow(lblDest, txtDest);
	lblType = new QLabel("Type");
	txtType = new QLineEdit;
	formsLayout->addRow(lblType, txtType);
	lblPrice = new QLabel("Price");
	txtPrice = new QLineEdit;
	formsLayout->addRow(lblPrice, txtPrice);
	forms->setLayout(formsLayout);

	btns = new QWidget();
	gridBtnsLayout = new QGridLayout();
	btnAdd = new QPushButton("&Add");
	gridBtnsLayout->addWidget(btnAdd, 0, 0);
	btnMod = new QPushButton("&Modify");
	gridBtnsLayout->addWidget(btnMod, 0, 1);
	btnPop = new QPushButton("&Remove");
	gridBtnsLayout->addWidget(btnPop, 0, 2);
	btnUndo = new QPushButton("&Undo");
	gridBtnsLayout->addWidget(btnUndo, 1, 0);
	btnCartCrud= new QPushButton("&Open Cart CRUD");
	gridBtnsLayout->addWidget(btnCartCrud, 1, 1);
	btnCartRead = new QPushButton("&Open Cart Read-Only");
	gridBtnsLayout->addWidget(btnCartRead, 1, 2);
	btns->setLayout(gridBtnsLayout);

	filters = new QWidget();
	filtersLayout = new QGridLayout();

	btnFilter = new QPushButton("&Filter by");
	filtersLayout->addWidget(btnFilter, 0, 0);
	lblFPrice = new QLabel("Price");
	txtFPrice = new QLineEdit;
	filtersLayout->addWidget(lblFPrice, 1, 0);
	filtersLayout->addWidget(txtFPrice, 1, 1);
	lblFName = new QLabel("Name");
	txtFName = new QLineEdit;
	filtersLayout->addWidget(lblFName, 1, 2);
	filtersLayout->addWidget(txtFName, 1, 3);
	lblFDest = new QLabel("Destination");
	txtFDest = new QLineEdit;
	filtersLayout->addWidget(lblFDest, 2, 0);
	filtersLayout->addWidget(txtFDest, 2, 1);
	lblFType = new QLabel("Type");
	txtFType = new QLineEdit;
	filtersLayout->addWidget(lblFType, 2, 2);
	filtersLayout->addWidget(txtFType, 2, 3);

	filters->setLayout(filtersLayout);

	rgtBoxLayout->addWidget(forms);
	rgtBoxLayout->addWidget(btns);
	rgtBoxLayout->addWidget(filters);
	rgtBoxLayout->addStretch();
	rgtBox->setLayout(rgtBoxLayout);

	dynBtns = new QWidget();
	dynBtnsLayout = new QVBoxLayout();
	dynBtns->setLayout(dynBtnsLayout);

	windowLayout->addWidget(lftBox);
	windowLayout->addWidget(rgtBox);
	windowLayout->addWidget(dynBtns);

	window->setLayout(windowLayout);
}

void gui::initConnections() {
	QObject::connect(list, &QTableView::clicked, [this]() {
		if (list->selectionModel()->selectedIndexes().isEmpty()) {
			txtId->setText("");
			txtName->setText("");
			txtDest->setText("");
			txtType->setText("");
			txtPrice->setText("");
			return;
		}
		int selRow = list->selectionModel()->selectedIndexes().at(0).row();
		qDebug() << selRow;
		txtId->setText(list->model()->data(list->model()->index(selRow, 0), Qt::DisplayRole).toString());
		txtName->setText(list->model()->data(list->model()->index(selRow, 1), Qt::DisplayRole).toString());
		txtDest->setText(list->model()->data(list->model()->index(selRow, 2), Qt::DisplayRole).toString());
		txtType->setText(list->model()->data(list->model()->index(selRow, 3), Qt::DisplayRole).toString());
		txtPrice->setText(list->model()->data(list->model()->index(selRow, 4), Qt::DisplayRole).toString());
	});

	QObject::connect(btnAdd, &QPushButton::clicked, [&]() {
		try {
			const int id = atoi(txtId->text().toStdString().c_str());
			const string name = txtName->text().toStdString();
			const string dest = txtDest->text().toStdString();
			const string type = txtType->text().toStdString();
			const int price = atoi(txtPrice->text().toStdString().c_str());
			oService.addOffer(id, name, dest, type, price);
			loadList(oService.getAll());
			
			const vector<offer>& oList = oService.getAll();
			for (const auto& Offer : oList) {
				bool isPresent = false;
				for (const auto& Button : dynBtnsList)
					if (Offer.getType() == Button->text().toStdString()) {
						isPresent = true;
						break;
					}
				if (isPresent == false) {
					dynBtnsList.push_back(new QPushButton(QString::fromStdString(Offer.getType())));
					dynBtnsLayout->addWidget(dynBtnsList.back());
				}
			}
			for (const auto& Button : dynBtnsList) {
				Button->disconnect();
				QObject::connect(Button, &QPushButton::clicked, [&]() {
					QMessageBox::information(nullptr, Button->text(), QString::fromStdString(to_string(oService.countTypes(Button->text().toStdString()))));
				});
			}
		}
		catch (validationException e) { QMessageBox::warning(nullptr, "Warning", e.what().c_str()); }
		catch (repositoryException e) { QMessageBox::warning(nullptr, "Warning", e.what().c_str()); }
	});

	QObject::connect(btnMod, &QPushButton::clicked, [&]() {
		try {
			const int index = list->selectionModel()->selectedIndexes().at(0).row();
			const int id = atoi(txtId->text().toStdString().c_str());
			const string name = txtName->text().toStdString();
			const string dest = txtDest->text().toStdString();
			const string type = txtType->text().toStdString();
			const int price = atoi(txtPrice->text().toStdString().c_str());
			const vector<offer>& oList = oService.getAll();
			oService.modOffer(oList[index].getId(), id, name, dest, type, price);
			loadList(oService.getAll());

			for (const auto& Offer : oList) {
				bool isPresent = false;
				for (const auto& Button : dynBtnsList)
					if (Offer.getType() == Button->text().toStdString()) {
						isPresent = true;
						break;
					}
				if (isPresent == false) {
					dynBtnsList.push_back(new QPushButton(QString::fromStdString(Offer.getType())));
					dynBtnsLayout->addWidget(dynBtnsList.back());
				}
			}
			int i = 0;
			for (const auto& Button : dynBtnsList) {
				bool wasDeleted = true;
				for (const auto& Offer : oList) {
					if (Button->text().toStdString() == Offer.getType()) {
						wasDeleted = false;
						break;
					}
				}
				if (wasDeleted == true) {
					dynBtnsList.erase(dynBtnsList.begin() + i);
					i--;
					delete Button;
				}
				i++;
			}
			for (const auto& Button : dynBtnsList) {
				Button->disconnect();
				QObject::connect(Button, &QPushButton::clicked, [&]() {
					QMessageBox::information(nullptr, Button->text(), QString::fromStdString(to_string(oService.countTypes(Button->text().toStdString()))));
				});
			}
		}
		catch (validationException e) { QMessageBox::warning(nullptr, "Warning", e.what().c_str()); }
		catch (repositoryException e) { QMessageBox::warning(nullptr, "Warning", e.what().c_str()); }
	});

	QObject::connect(btnPop, &QPushButton::clicked, [&]() {
		try {
			const int id = txtId->text().toInt();
			oService.popOffer(id);
			txtId->clear();
			txtName->clear();
			txtDest->clear();
			txtType->clear();
			txtPrice->clear();
			loadList(oService.getAll()); 
			
			const vector<offer>& oList = oService.getAll();
			int i = 0;
			for (const auto& Button : dynBtnsList) {
				bool wasDeleted = false;
				for (const auto& Offer : oList)
					if (Offer.getType() == Button->text().toStdString()) {
						wasDeleted = true;
						break;
					}
				if (wasDeleted == false) {
					dynBtnsList.erase(dynBtnsList.begin() + i);
					delete Button;
				}
				i++;
			}
			for (const auto& Button : dynBtnsList) {
				Button->disconnect();
				QObject::connect(Button, &QPushButton::clicked, [&]() {
					QMessageBox::information(nullptr, Button->text(), QString::fromStdString(to_string(oService.countTypes(Button->text().toStdString()))));
				});
			}
		}
		catch (validationException e) { QMessageBox::warning(nullptr, "Warning", e.what().c_str()); }
		catch (repositoryException e) { QMessageBox::warning(nullptr, "Warning", e.what().c_str()); }
	});

	QObject::connect(btnSortN, &QPushButton::clicked, [&]() {
		loadList(oService.sortOffers('n'));
	});

	QObject::connect(btnSortD, &QPushButton::clicked, [&]() {
		loadList(oService.sortOffers('d'));
	});

	QObject::connect(btnSortPT, &QPushButton::clicked, [&]() {
		loadList(oService.sortOffers('p'));
	});

	QObject::connect(btnUndo, &QPushButton::clicked, [&]() {
		try {
			oService.doUndo();
			loadList(oService.getAll());
		}
		catch (validationException e) { QMessageBox::warning(nullptr, "Warning", e.what().c_str()); }
		catch (repositoryException e) { QMessageBox::warning(nullptr, "Warning", e.what().c_str()); }
	});

	QObject::connect(btnCartCrud, &QPushButton::clicked, [&]() {
		(new guiCartCRUD(oService, cService))->show();
	});

	QObject::connect(btnCartRead, &QPushButton::clicked, [&]() {
		(new guiCartReadOnly(oService, cService))->show();
	});

	QObject::connect(btnFilter, &QPushButton::clicked, [&]() {
		string criteria = "";
		if (txtFPrice->text() != "")
			criteria += "p" + txtFPrice->text().toStdString() + " ";
		if (txtFName->text() != "")
			criteria += "n" + txtFName->text().toStdString() + " ";
		if (txtFDest->text() != "")
			criteria += "d" + txtFDest->text().toStdString() + " ";
		if (txtFType->text() != "")
			criteria += "t" + txtFType->text().toStdString() + " ";
		if (criteria != "") {
			char criteriaCStr[100] = "";
			for (int i = 0; i < criteria.size() - 1; i++)
				criteriaCStr[i] = criteria[i];
			loadList(oService.filterOffers(criteriaCStr));
		}
		else
			loadList(oService.getAll());

	});
}

void gui::show() {
	window->show();
}

void gui::loadList(const vector<offer>& oList) {
	model->setOffers(oList);
}