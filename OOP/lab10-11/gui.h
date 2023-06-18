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
#include "guiCartCRUD.h"
#include "guiCartReadOnly.h"
#include "tabel.h"

class gui {
private:
	offersService& oService;
	cartService& cService;

	QWidget* window, * lftBox, * rgtBox, * forms, * filters, * btns, * btns2, * btnsSort, * dynBtns;
	QVBoxLayout* lftBoxLayout, * rgtBoxLayout, * dynBtnsLayout;
	QHBoxLayout* windowLayout, * btnsSortLayout;
	QGridLayout* gridBtnsLayout, * filtersLayout;
	QFormLayout* formsLayout;
	//QListWidget* list;
	MyTableModel* model;
	QTableView* list;
	QLabel* lblId, * lblName, * lblDest, * lblType, * lblPrice, * lblFPrice, * lblFName, * lblFDest, * lblFType;
	QLineEdit* txtId, * txtName, * txtDest, * txtType, * txtPrice, * txtFPrice, * txtFName, * txtFDest, * txtFType;
	QPushButton* btnAdd, * btnMod, * btnPop, * btnUndo, * btnCartCrud, * btnCartRead, * btnFilter, * btnSortN, * btnSortD, * btnSortPT;
	vector<QPushButton*> dynBtnsList;

public:
	gui(offersService& oService, cartService& cService) : oService{ oService }, cService{ cService } {
		initGUI();
		initConnections();
		loadList(oService.getAll());
	}

	gui(const gui& ot) = delete;

	void initGUI();

	void initConnections();

	void show();

	void loadList(const vector<offer>& oList);
};