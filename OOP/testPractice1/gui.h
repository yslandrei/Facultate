#pragma once
#pragma once
#include "taskService.h"

#include <QtWidgets/QApplication>
#include <QWidget>
#include <QListWidget>
#include <QFormLayout>
#include <QPushButton>
#include <QLabel>
#include <QTableWidget>
#include <qlineedit.h>
#include <QMessageBox>
#include <sstream>

class gui : public observer {
private:
	taskService& tService;

	QWidget* window, * rgtBox, * form, * search;
	QTableWidget* tasksTable;
	QFormLayout* formLayout, * searchLayout;
	QVBoxLayout* rgtBoxLayout;
	QHBoxLayout* windowLayout;
	QPushButton* addBtn;
	QLabel* lblId, * lblDesc, * lblStatus, * lblProgrammers, * lblSearch;
	QLineEdit* txtId, * txtDesc, * txtStatus, * txtProgrammers, * txtSearch;

public:
	gui(taskService& tService) : tService{ tService } {
		initGUI();
		initConnections();
		loadTable(tService.getAll());
	}

	void update() override {
		loadTable(tService.search(txtSearch->text().toStdString()));
	}

	void initGUI() {
		window = new QWidget;
		window->setMinimumWidth(900);

		windowLayout = new QHBoxLayout;

		tasksTable = new QTableWidget;

		windowLayout->addWidget(tasksTable);

		rgtBox = new QWidget;

		rgtBoxLayout = new QVBoxLayout;

		form = new QWidget;

		formLayout = new QFormLayout;

		lblId = new QLabel("ID");
		txtId = new QLineEdit;
		formLayout->addRow(lblId, txtId);
		lblDesc = new QLabel("Description");
		txtDesc = new QLineEdit;
		formLayout->addRow(lblDesc, txtDesc);
		lblStatus = new QLabel("State");
		txtStatus = new QLineEdit;
		formLayout->addRow(lblStatus, txtStatus);
		lblProgrammers = new QLabel("Programmers");
		txtProgrammers = new QLineEdit;
		formLayout->addRow(lblProgrammers, txtProgrammers);
		
		form->setLayout(formLayout);

		rgtBoxLayout->addWidget(form);

		addBtn = new QPushButton("Add");

		rgtBoxLayout->addWidget(addBtn);

		search = new QWidget;

		searchLayout = new QFormLayout;

		lblSearch = new QLabel("Search");
		txtSearch = new QLineEdit;
		searchLayout->addRow(lblSearch, txtSearch);

		search->setLayout(searchLayout);

		rgtBoxLayout->addWidget(search);

		rgtBox->setLayout(rgtBoxLayout);

		windowLayout->addWidget(rgtBox);

		window->setLayout(windowLayout);
	}

	void initConnections() {
		//connect add button to add function from service
		QObject::connect(addBtn, &QPushButton::clicked, [&]() {
			try {
				//transform this string into a vector of strings
				vector<string> programmers;
				stringstream ss(txtProgrammers->text().toStdString());
				string token;
				while (getline(ss, token, ' '))
					programmers.push_back(token);
				
				tService.addTask(txtId->text().toInt(), txtDesc->text().toStdString(), txtStatus->text().toStdString(), programmers);
				loadTable(tService.search(txtSearch->text().toStdString()));
			}
			catch (exception& e) {
				QMessageBox::critical(nullptr, "Error", e.what());
			}
		});

		//connect search field to search function from service
		QObject::connect(txtSearch, &QLineEdit::textChanged, [&]() {
			loadTable(tService.search(txtSearch->text().toStdString()));
		});

		//connect click on table to show details on form
		QObject::connect(tasksTable, &QTableWidget::itemSelectionChanged, [&]() {
			if (tasksTable->selectedItems().isEmpty()) {
				txtId->setText("");
				txtDesc->setText("");
				txtStatus->setText("");
				txtProgrammers->setText("");
			}
			else {
				int selRow = tasksTable->selectedItems().at(0)->row();
				txtId->setText(tasksTable->item(selRow, 0)->text());
				txtDesc->setText(tasksTable->item(selRow, 1)->text());
				txtStatus->setText(tasksTable->item(selRow, 2)->text());
				txtProgrammers->setText(tasksTable->item(selRow, 3)->text());
			}
		});
	}

	void loadTable(vector<task> tList) {
		tasksTable->setRowCount(tList.size());
		tasksTable->setColumnCount(4);
		int row = 0;
		for (auto& t : tList) {
			tasksTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(std::to_string(t.getId()))));
			tasksTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(t.getDescription())));
			tasksTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(t.getState())));
			string programmers = "";
			for(auto& p : t.getProgrammers())
				programmers += p + " ";
			tasksTable->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(programmers)));
			row++;
		}
	}

	void show() {
		window->show();
	}
};