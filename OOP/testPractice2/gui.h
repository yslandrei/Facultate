#pragma once
#include "songService.h"
#include "observer.h"
#include <qwidget.h>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <qslider.h>

class gui : public observer {
private:
	songService& sService;

	QWidget* window, * rgtBox, * form, * btnsList;
	QHBoxLayout* windowLayout;
	QVBoxLayout* rgtBoxLayout, * btnsListLayout;
	QTableWidget* table;
	QFormLayout* formLayout;
	QLabel* lblId, * lblTitle, * lblArtist;
	QLineEdit* txtId, * txtTitle, * txtArtist;
	QPushButton* btnAdd, * btnPop, * btnMod;
	QSlider* slider;


public:
	gui(songService& sService) : sService{ sService } {
		initGui();
		initConnections();
		loadData(sService.getAll());
	}

	void update() override {
		//loadData();
	}

	//load the data from the vector into the table
	void loadData(vector<song> sList) {
		table->clear();
		table->setRowCount(sList.size());
		table->setColumnCount(5);
		table->setHorizontalHeaderItem(0, new QTableWidgetItem("ID"));
		table->setHorizontalHeaderItem(1, new QTableWidgetItem("Titlu"));
		table->setHorizontalHeaderItem(2, new QTableWidgetItem("Artist"));
		table->setHorizontalHeaderItem(3, new QTableWidgetItem("Rank"));
		table->setHorizontalHeaderItem(4, new QTableWidgetItem("Rank Similar"));

		sort(sList.begin(), sList.end(), [](song s1, song s2) {
			return s1.getRank() < s2.getRank(); 
		});

		map<int, int> ranks;
		for (auto s : sList) {
			if (ranks.find(s.getRank()) == ranks.end())
				ranks[s.getRank()] = 0;
			ranks[s.getRank()]++;
		}

		int row = 0;
		for (auto s : sList) {
			table->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(to_string(s.getId()))));
			table->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(s.getTitle())));
			table->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(s.getArtist())));
			table->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(to_string(s.getRank()))));
			table->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(to_string(ranks[s.getRank()]))));
			row++;
		}
	}

	void initGui() {
		window = new QWidget;
		window->setMinimumWidth(1080);
		window->setMinimumHeight(400);
		windowLayout = new QHBoxLayout;

		table = new QTableWidget;
		windowLayout->addWidget(table);

			rgtBox = new QWidget;
			rgtBoxLayout = new QVBoxLayout;

				form = new QWidget;
				formLayout = new QFormLayout;
				lblId = new QLabel("ID");
				txtId = new QLineEdit;
				formLayout->addRow(lblId, txtId);
				lblTitle = new QLabel("Titlu");
				txtTitle = new QLineEdit;
				formLayout->addRow(lblTitle, txtTitle);
				lblArtist = new QLabel("Artist");
				txtArtist = new QLineEdit;
				formLayout->addRow(lblArtist, txtArtist);
				slider = new QSlider;
				slider->setOrientation(Qt::Horizontal);
				slider->setTickPosition(QSlider::TicksAbove);
				slider->setTickInterval(1);
				slider->setFixedWidth(200);
				slider->setMinimum(1);
				slider->setMaximum(10);
				formLayout->addRow(slider);
				form->setLayout(formLayout);

			rgtBoxLayout->addWidget(form);

				btnsList = new QWidget;
				btnsListLayout = new QVBoxLayout;
				btnAdd = new QPushButton("Adauga");
				btnsListLayout->addWidget(btnAdd);
				btnMod = new QPushButton("Modifica");
				btnsListLayout->addWidget(btnMod);
				btnPop = new QPushButton("Sterge");
				btnsListLayout->addWidget(btnPop);
				btnsList->setLayout(btnsListLayout);

			rgtBoxLayout->addWidget(btnsList);
			rgtBox->setLayout(rgtBoxLayout);

		windowLayout->addWidget(rgtBox);
		window->setLayout(windowLayout);
	}

	void initConnections() {
		QObject::connect(slider, &QSlider::valueChanged, [&]() {
			qDebug() << slider->value();
		});
		
		//Connect the table click event to change the text in the line edits
		QObject::connect(table, &QTableWidget::cellClicked, [&]() {
			int row = table->currentRow();
			txtId->setText(table->item(row, 0)->text());
			txtTitle->setText(table->item(row, 1)->text());
			txtArtist->setText(table->item(row, 2)->text());
			slider->setValue(stoi(table->item(row, 3)->text().toStdString()));
		});

		//Connect the add button to the addSong service method
		QObject::connect(btnAdd, &QPushButton::clicked, [&]() {
			try {
				int id = stoi(txtId->text().toStdString());
				string title = txtTitle->text().toStdString();
				string artist = txtArtist->text().toStdString();
				int rank = slider->value();
				sService.addSong(id, title, artist, rank);
				loadData(sService.getAll());
			}
			catch (exception& e) {
				QMessageBox::critical(nullptr, "Error", e.what());
			}
		});

		//Connect the modify button to the modifySong service method
		QObject::connect(btnMod, &QPushButton::clicked, [&]() {
			try {
				int id = stoi(txtId->text().toStdString());
				string title = txtTitle->text().toStdString();
				string artist = txtArtist->text().toStdString();
				int rank = slider->value();
				sService.modSong(id, title, artist, rank);
				loadData(sService.getAll());
			}
		catch (exception& e) {
				QMessageBox::critical(nullptr, "Error", e.what());
			}
		});

		//Connect the remove button to the popSong service method
		QObject::connect(btnPop, &QPushButton::clicked, [&]() {
			try {
				int id = stoi(txtId->text().toStdString());
				sService.popSong(id);
				loadData(sService.getAll());
			}
			catch (exception& e) {
				QMessageBox::critical(nullptr, "Error", e.what());
			}
		});
	}

	void show() {
		window->show();
	}
};