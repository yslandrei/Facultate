#pragma once
#include "taskService.h"
#include <QApplication>
#include <QListWidget>
#include <qlayout.h>
#include <QPushButton>
#include <QMessageBox>

class OpenGui : public observer {
private:
	taskService& tService;
	int selectedRow = -1;

	QWidget* window, * rgtBox;
	QHBoxLayout* windowLayout;
	QVBoxLayout* rgtBoxLayout;
	QListWidget* list;
	QPushButton* openBtn, * inprogressBtn, * closedBtn;

public:
	OpenGui(taskService& tService) : tService{ tService } {
		initGui();
		initConnections();
		loadList(tService.getAllOpen());
	}

	void update() override {
		loadList(tService.getAllOpen());
	}

	void initGui() {
		window = new QWidget;
		window->setWindowTitle("Open");
		windowLayout = new QHBoxLayout;
		rgtBox = new QWidget;
		rgtBoxLayout = new QVBoxLayout;
		list = new QListWidget;
		openBtn = new QPushButton("Open");
		inprogressBtn = new QPushButton("In progress");
		closedBtn = new QPushButton("Closed");

		windowLayout->addWidget(list);
		windowLayout->addWidget(rgtBox);
		rgtBoxLayout->addWidget(openBtn);
		rgtBoxLayout->addWidget(inprogressBtn);
		rgtBoxLayout->addWidget(closedBtn);

		window->setLayout(windowLayout);
		rgtBox->setLayout(rgtBoxLayout);
	}

	void initConnections() {
		QObject::connect(list, &QListWidget::itemSelectionChanged, [&]() {
			selectedRow = list->currentRow();
		});

		QObject::connect(openBtn, &QPushButton::clicked, [&]() {
			try {
			vector<task> tList = tService.getAllOpen();
			tList[selectedRow].setState("open");
			tService.notify();
		}
		catch (exception& e) {
			QMessageBox::critical(nullptr, "Error", e.what());
		}
		});

		QObject::connect(inprogressBtn, &QPushButton::clicked, [&]() {
			try {
				vector<task> tList = tService.getAllOpen();
				tList[selectedRow].setState("inprogress");
				tService.notify();
			}
			catch (exception& e) {
				QMessageBox::critical(nullptr, "Error", e.what());
			}
		});

		QObject::connect(closedBtn, &QPushButton::clicked, [&]() {
			try {
			vector<task> tList = tService.getAllOpen();
			tList[selectedRow].setState("closed");
			tService.notify();
		}
		catch (exception& e) {
			QMessageBox::critical(nullptr, "Error", e.what());
		}
		});
	}

	void loadList(vector<task> tList) {
		list->clear();
		for (auto& t : tList)
			list->addItem(QString::fromStdString(t.getDescription()));
	}

	void show() {
		window->show();
	}

};