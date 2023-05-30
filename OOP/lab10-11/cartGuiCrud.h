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

class cartGuiCrud {
private:
	offersService& oService;
	cartService& cService;

	QWidget* cartWindow;
	QHBoxLayout* cartWindowLayout;
	QListWidget* cartList;

public:
	cartGuiCrud(offersService& oService, cartService& cService) : oService{ oService }, cService{ cService } {
		initGUI();
		initConnections();
		loadList(cartList, cService.getAll());
	}

	cartGuiCrud(const cartGuiCrud& ot) = delete;

	void initGUI();

	void initConnections();

	void show();

	void loadList(QListWidget* list, const vector<offer>& oList);
};