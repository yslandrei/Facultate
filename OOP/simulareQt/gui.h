#pragma once
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

#include "contactService.h"

class GUI {
private:
	contactService& cService;

	QWidget* main, * details, * sortButtons, * detailsButtons, * detailsTxt;
	QVBoxLayout* mainLayout, * detailsLayout;
	QHBoxLayout* sortButtonsLayout, detailsButtonsLayout;
	QListWidget* list;
	
	QFormLayout* detailsTxtLayout;
	QLabel* lblId, * lblNume, * lblPrenume, * lblTelefon, * lblAdresa, * lblEmail, * lblLinkedin;
	QLineEdit* txtId, * txtNume, * txtPrenume, * txtTelefon, * txtAdresa, * txtEmail, * txtLinkedin;

	QPushButton* btnSortNume, * btnSortAdresa, * btnNesortat, * btnApel, * btnSms;

public:
	GUI(contactService& cService) : cService{ cService } {
		initGUI();
		main->show();
		details->show();
	}

	void initGUI() {
		main = new QWidget();
		main->setWindowTitle("Contacts");
		mainLayout = new QVBoxLayout;

		list = new QListWidget;
		const vector<contact>& cList = cService.getAll();
		for (const auto& Contact : cList)
			list->addItem((Contact.getNume()+" "+Contact.getPrenume()).c_str());


		sortButtons = new QWidget;
		sortButtonsLayout = new QHBoxLayout;

		btnSortNume = new QPushButton("&Sorteaza dupa Nume");
		sortButtonsLayout->addWidget(btnSortNume);
		btnSortAdresa = new QPushButton("&Sorteaza dupa Adresa");
		sortButtonsLayout->addWidget(btnSortAdresa);
		btnNesortat = new QPushButton("&Nesortat");
		sortButtonsLayout->addWidget(btnNesortat);

		sortButtons->setLayout(sortButtonsLayout);

		mainLayout->addWidget(list);
		mainLayout->addWidget(sortButtons);

		main->setLayout(mainLayout);


		details = new QWidget();
		detailsLayout = new QVBoxLayout();

		detailsTxt = new QWidget();

		detailsTxtLayout = new QFormLayout();
		lblId = new QLabel("Id");
		txtId = new QLineEdit();
		detailsTxtLayout->addRow(lblId, txtId);
		lblNume = new QLabel("Nume");
		txtPrenume = new QLineEdit();
		detailsTxtLayout->addRow(lblNume, txtNume);
		lblPrenume = new QLabel("Prenume");
		txtPrenume = new QLineEdit();
		detailsTxtLayout->addRow(lblPrenume, txtPrenume);
		lblTelefon = new QLabel("Telefon");
		txtTelefon = new QLineEdit();
		detailsTxtLayout->addRow(lblTelefon, txtTelefon);
		lblAdresa = new QLabel("Adresa");
		txtAdresa = new QLineEdit();
		detailsTxtLayout->addRow(lblAdresa, txtAdresa);
		lblEmail = new QLabel("Email");
		txtEmail = new QLineEdit();
		detailsTxtLayout->addRow(lblEmail, txtEmail);
		lblLinkedin = new QLabel("Linkedin");
		txtLinkedin = new QLineEdit();

		detailsTxt->setLayout(detailsTxtLayout);

		detailsLayout->addWidget(detailsTxt);

		details->setLayout(detailsLayout);
		
	}


};