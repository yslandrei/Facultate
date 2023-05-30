#include <QtWidgets/QApplication>
#include <QListWidget>
#include <qboxlayout.h>
#include <qformlayout.h>
#include <qlabel.h>
#include <qtablewidget.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qdebug.h>
#include <qmessagebox.h>

#include "offersService.h"
#include "cartService.h"

class guiCartCRUD : public observer {
private:
	offersService& oService;
	cartService& cService;

	QWidget* cartWindow, * formsCart, * btnsCart, * rgtCBox;
	QVBoxLayout* btnsCartLayout, * rgtCBoxLayout;
	QHBoxLayout* cartWindowLayout;
	QFormLayout* formsCartLayout;
	QListWidget* cartList;
	QLabel* lblCName;
	QLineEdit* txtCName;
	QPushButton* btnCAdd, * btnCGen, * btnCEmp, * btnCExp;

public:
	guiCartCRUD(offersService& oService, cartService& cService) : oService{ oService }, cService{ cService } {
		initGUI();
		cService.addObserver(this);
		initConnections();
		loadList(cartList, cService.getAll());
	}

	guiCartCRUD(const guiCartCRUD& ot) = delete;

	void initGUI();

	void initConnections();

	void show();

	void loadList(QListWidget* list, const vector<offer>& oList);

	void update() override {
		loadList(cartList, cService.getAll());
	}
};