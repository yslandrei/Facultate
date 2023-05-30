#include "guiCartCRUD.h"

void guiCartCRUD::initGUI() {
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

void guiCartCRUD::initConnections() {
	QObject::connect(cartList, &QListWidget::itemClicked, [&]() {
		txtCName->setText(cartList->currentItem()->text());
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

void guiCartCRUD::show() {
	cartWindow->show();
}

void guiCartCRUD::loadList(QListWidget* list, const vector<offer>& oList) {
	int rowCount = 0;
	list->clear();
	for (const auto& Offer : oList)
		list->addItem(Offer.getName().c_str());
}

