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
#include <qpainter.h>
#include <qwidget.h>

#include "offersService.h"
#include <random>
#include "cartService.h"

class guiCartReadOnly : public QWidget, public observer {
private:
	offersService& oService;
	cartService& cService;

public:
	guiCartReadOnly(offersService& oService, cartService& cService) : oService{ oService }, cService{ cService } {
		cService.addObserver(this);
	}

	void update() override {
		repaint();
	}

	void paintEvent(QPaintEvent* ev) override {
		QPainter p{ this };
		const vector<offer>& oList = cService.getAll();
		
		std::mt19937 mt{ std::random_device{}() };
		std::uniform_int_distribution<> x_coord{ 0, width() - 100 };
		std::uniform_int_distribution<> y_coord{ 0, height() - 100 };
		std::uniform_int_distribution<> width_coord{ 15, 256 };
		std::uniform_int_distribution<> height_coord{ 15, 256 };
		for (const auto& Offer : oList) {
			p.drawEllipse(x_coord(mt), y_coord(mt), width_coord(mt), height_coord(mt));
		}
	}
};