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
#include <qwidget.h>
#include <qpainter.h>

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
		int i = 0;
		for (const auto& Offer : oList) {
			p.drawRect(0, i, 240, 40);
			i += 80;
		}
	}
};