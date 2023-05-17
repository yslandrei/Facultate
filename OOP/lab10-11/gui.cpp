#include "gui.h"

void gui::initGUI() {
	window = new QWidget();
	window->setWindowTitle("Tourist Offers");
	windowLayout = new QHBoxLayout;

	lftBox = new QWidget();
	lftBoxLayout = new QVBoxLayout();

	list = new QListWidget;

	btnsSort = new QWidget();
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
	btnCart = new QPushButton("&Open Cart");
	gridBtnsLayout->addWidget(btnCart, 1, 1);
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



	cartWindow = new QWidget();
	cartWindow->setWindowTitle("Tourist Offers Cart");
	cartWindowLayout = new QHBoxLayout();

	cartList = new QListWidget();

	rgtCBox = new QWidget();
	rgtCBoxLayout = new QVBoxLayout();

	formsCart = new QWidget();
	formsCartLayout = new QFormLayout();
	lblCName = new QLabel("Name");
	txtCName = new QLineEdit;
	formsCartLayout->addRow(lblCName, txtCName);
	formsCart->setLayout(formsCartLayout);

	btnsCart = new QWidget();
	btnsCartLayout = new QVBoxLayout();
	btnCAdd = new QPushButton("&Add");
	btnsCartLayout->addWidget(btnCAdd);
	btnCGen = new QPushButton("&Generate");
	btnsCartLayout->addWidget(btnCGen);
	btnCEmp = new QPushButton("&Empty");
	btnsCartLayout->addWidget(btnCEmp);
	btnCExp = new QPushButton("&Export");
	btnsCartLayout->addWidget(btnCExp);
	btnsCart->setLayout(btnsCartLayout);

	rgtCBoxLayout->addWidget(formsCart);
	rgtCBoxLayout->addWidget(btnsCart);
	rgtCBoxLayout->addStretch();
	rgtCBox->setLayout(rgtCBoxLayout);

	cartWindowLayout->addWidget(cartList);
	cartWindowLayout->addWidget(rgtCBox);
	cartWindow->setLayout(cartWindowLayout);
}

void gui::initConnections() {
	QObject::connect(list, &QListWidget::itemClicked, [&]() {
		const string name = list->currentItem()->text().toStdString();
		const offer selectedOffer = oService.findOffer(name);
		txtId->setText(QString::fromStdString(to_string(selectedOffer.getId())));
		txtName->setText(QString::fromStdString(selectedOffer.getName()));
		txtDest->setText(QString::fromStdString(selectedOffer.getDest()));
		txtType->setText(QString::fromStdString(selectedOffer.getType()));
		txtPrice->setText(QString::fromStdString(to_string(selectedOffer.getPrice())));
	});

	QObject::connect(cartList, &QListWidget::itemClicked, [&]() {
		txtCName->setText(cartList->currentItem()->text());
	});

	QObject::connect(btnAdd, &QPushButton::clicked, [&]() {
		try {
			const int id = atoi(txtId->text().toStdString().c_str());
			const string name = txtName->text().toStdString();
			const string dest = txtDest->text().toStdString();
			const string type = txtType->text().toStdString();
			const int price = atoi(txtPrice->text().toStdString().c_str());
			oService.addOffer(id, name, dest, type, price);
			loadList(list, oService.getAll());
			
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
			const int index = list->currentRow();
			const int id = atoi(txtId->text().toStdString().c_str());
			const string name = txtName->text().toStdString();
			const string dest = txtDest->text().toStdString();
			const string type = txtType->text().toStdString();
			const int price = atoi(txtPrice->text().toStdString().c_str());
			const vector<offer>& oList = oService.getAll();
			oService.modOffer(oList[index].getId(), id, name, dest, type, price);
			loadList(list, oService.getAll());

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

	QObject::connect(btnPop, &QPushButton::clicked, [&]() {
		try {
			const int id = txtId->text().toInt();
			oService.popOffer(id);
			txtId->clear();
			txtName->clear();
			txtDest->clear();
			txtType->clear();
			txtPrice->clear();
			loadList(list, oService.getAll()); 
			
			const vector<offer>& oList = oService.getAll();
			int i = 0;
			for (const auto& Button : dynBtnsList) {
				bool isPresent = false;
				for (const auto& Offer : oList)
					if (Offer.getType() == Button->text().toStdString()) {
						isPresent = true;
						break;
					}
				if (isPresent == false) {
					dynBtnsList.erase(dynBtnsList.begin() + i);
					//dynBtnsLayout->removeWidget(Button); #doesn't work
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
		loadList(list, oService.sortOffers('n'));
	});

	QObject::connect(btnSortD, &QPushButton::clicked, [&]() {
		loadList(list, oService.sortOffers('d'));
	});

	QObject::connect(btnSortPT, &QPushButton::clicked, [&]() {
		loadList(list, oService.sortOffers('p'));
	});

	QObject::connect(btnUndo, &QPushButton::clicked, [&]() {
		try {
			oService.doUndo();
			loadList(list, oService.getAll());
		}
		catch (validationException e) { QMessageBox::warning(nullptr, "Warning", e.what().c_str()); }
		catch (repositoryException e) { QMessageBox::warning(nullptr, "Warning", e.what().c_str()); }
	});

	QObject::connect(btnCart, &QPushButton::clicked, [&]() {
		cartWindow->show();
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
			loadList(list, oService.filterOffers(criteriaCStr));
		}
		else
			loadList(list, oService.getAll());

	});

	QObject::connect(btnCAdd, &QPushButton::clicked, [&]() {
		try {
			const string name = txtCName->text().toStdString();;
			cService.addOffer(name);
			loadList(cartList, cService.getAll());
		}
		catch (validationException e) { QMessageBox::warning(nullptr, "Warning", e.what().c_str()); }
		catch (repositoryException e) { QMessageBox::warning(nullptr, "Warning", e.what().c_str()); }
	});

	QObject::connect(btnCGen, &QPushButton::clicked, [&]() {
		cService.generateCart(rand() % oService.getAll().size() + 1);
		txtCName->clear();
		loadList(cartList, cService.getAll());
	});

	QObject::connect(btnCEmp, &QPushButton::clicked, [&]() {
		cService.emptyCart();
		txtCName->clear();
		loadList(cartList, cService.getAll());
	});

	QObject::connect(btnCExp, &QPushButton::clicked, [&]() {
		cService.exportCart("cartData");
	});
}

void gui::run() {
	window->show();
}

void gui::loadList(QListWidget* list, const vector<offer>& oList) {
	int rowCount = 0;
	list->clear();
	for (const auto& Offer : oList)
		list->addItem(Offer.getName().c_str());
}