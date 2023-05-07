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

class gui {
private:
	offersService& oService;
	cartService& cService;

	QWidget* window, * cartWindow, * lftBox, * rgtBox, * forms, * filters, * btns, * btns2, * btnsSort, * formsCart, * btnsCart, * rgtCBox;
	QVBoxLayout* lftBoxLayout, * rgtBoxLayout, * btnsCartLayout, * rgtCBoxLayout;
	QHBoxLayout* windowLayout, * cartWindowLayout, * btnsSortLayout;
	QGridLayout* gridBtnsLayout, * filtersLayout;
	QFormLayout* formsLayout, * formsCartLayout;
	QListWidget* list, * cartList;
	QLabel* lblId, * lblName, * lblDest, * lblType, * lblPrice, * lblFPrice, * lblFName, * lblFDest, * lblFType, * lblCName;
	QLineEdit* txtId, * txtName, * txtDest, * txtType, * txtPrice, * txtFPrice, * txtFName, * txtFDest, * txtFType, * txtCName;
	QPushButton* btnAdd, * btnMod, * btnPop, * btnUndo, * btnCart, * btnFilter, * btnSortN, * btnSortD, * btnSortPT, * btnCAdd, * btnCGen, * btnCEmp, * btnCExp;

public:
	gui(offersService& oService, cartService& cService) : oService{ oService }, cService{ cService } {
		initGUI();
		initConnections();
		loadList(list, oService.getAll());
		loadList(cartList, cService.getAll());
	}

	gui(const gui& ot) = delete;

	void initGUI();

	void initConnections();

	void run();

	void loadList(QListWidget* list, const vector<offer>& oList);
};