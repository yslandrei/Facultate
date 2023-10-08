#pragma once
#include "studentService.h"
#include "observer.h"
#include "model.h"
#include <algorithm>

#include <QApplication>
#include <QTableView>
#include <QHBoxLayout>
#include <QPushButton>
#include <qmessagebox.h>

class MainGui : public observer {
private:
	StudentService& sService;
	vector<int> selectedIds;

	QWidget* window, * rgt;
	QHBoxLayout* windowLayout;
	QVBoxLayout* rgtLayout;
	QTableView* table;
	MyTableModel* model;
	QPushButton* btnYounger, * btnOlder, * btnPop, * btnUndo, * btnRedo;

public:
	MainGui(StudentService& sService) : sService{ sService } {
		initGui();
		initSignals();
		sService.addObserver(this);
		loadTable();
	}

	void initGui() {
		window = new QWidget;
		window->setMinimumSize(550, 400);
		windowLayout = new QHBoxLayout;

			table = new QTableView;
			model = new MyTableModel(sService.getAll());
			table->setModel(model);

		windowLayout->addWidget(table);
		
			rgt = new QWidget;
			rgtLayout = new QVBoxLayout;

				btnYounger = new QPushButton("Intinerire");

			rgtLayout->addWidget(btnYounger);

				btnOlder = new QPushButton("Imbatranire");

			rgtLayout->addWidget(btnOlder);

				btnPop = new QPushButton("Stergere");

			rgtLayout->addWidget(btnPop);

				btnUndo = new QPushButton("Undo");

			rgtLayout->addWidget(btnUndo);

				btnRedo = new QPushButton("Redo");

			rgtLayout->addWidget(btnRedo);

			rgt->setLayout(rgtLayout);

		windowLayout->addWidget(rgt);

		window->setLayout(windowLayout);
	}
	
	void initSignals() {
		//this signal connects btnYounger to the service function makeAllYounger
		QObject::connect(btnYounger, &QPushButton::clicked, [&]() {
			sService.makeAllYounger();
		});

		//this signal connects btnOlder to the service function makeAllOlder
		QObject::connect(btnOlder, &QPushButton::clicked, [&]() {
			sService.makeAllOlder();
		});

		//this signal connects btnPop to the service function popStudents
		QObject::connect(btnPop, &QPushButton::clicked, [&]() {
			sService.popStudents(selectedIds);
		});

		//this signal connects the selectionChanged signal of the selectedIds vector
		QObject::connect(table->selectionModel(), &QItemSelectionModel::selectionChanged, [&]() {
			QModelIndexList indexes = table->selectionModel()->selectedRows();
			
			selectedIds.clear();
			vector<Student> sList = model->getStudents();
			for (auto& index : indexes) {
				selectedIds.push_back(sList[index.row()].getId());
			}
		});

		//this signal connects btnUndo to the service function undo
		QObject::connect(btnUndo, &QPushButton::clicked, [&]() {
				sService.undo();
		});

		//this signal connects btnRedo to the service function redo
		QObject::connect(btnRedo, &QPushButton::clicked, [&]() {
			sService.redo();
		});
	}

	void loadTable() {
		vector<Student> sList = sService.getAll();
		sort(sList.begin(), sList.end(), [](Student s1, Student s2) {
			return s1.getAge() < s2.getAge();
		});
		model->setStudents(sList);
	}

	void update() override {
		loadTable();
	}

	void show() {
		window->show();
	}
};
