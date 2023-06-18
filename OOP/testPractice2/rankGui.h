#pragma once
#include "songService.h"
#include "observer.h"

#include <qpainter.h>

class rankGui : public QWidget, public observer {
private:
	songService sService;

public:
	rankGui(songService& sService) : sService{ sService } {
		sService.addObserver(this);
	}

	void update() override {
		repaint();
	}

	void paintEvent(QPaintEvent* ev) override {
		QPainter p{ this };
		const vector<song> sList = sService.getAll();

		map<int, int> rankMap;
		for (int i = 1; i <= 10; i++)
			rankMap[i] = 0;
		for(auto s : sList)
			rankMap[s.getRank()]++;

		
		int x = 0;
		for (auto r : rankMap) {
			p.setBrush(Qt::red);
			p.drawText(20, x+30, QString::number(r.first));
			p.drawRect(50, x, r.second * 100, 50);
			x += 60;
		}
	}
};