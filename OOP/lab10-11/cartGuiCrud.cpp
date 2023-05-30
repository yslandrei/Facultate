#include "cartGuiCrud.h"

void cartGuiCrud::initGUI() {
	cartWindow = new QWidget();
	cartWindow->setWindowTitle("Tourist Offers Cart");
	cartWindowLayout = new QHBoxLayout();

	cartList = new QListWidget();


	cartWindowLayout->addWidget(cartList);
	cartWindowLayout->addWidget(rgtCBox);
	cartWindow->setLayout(cartWindowLayout);
}

void cartGuiCrud::initConnections() {
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

void cartGuiCrud::show() {
	cartWindow->show();
}

void cartGuiCrud::loadList(QListWidget* list, const vector<offer>& oList) {
	int rowCount = 0;
	list->clear();
	for (const auto& Offer : oList)
		list->addItem(Offer.getName().c_str());
}
