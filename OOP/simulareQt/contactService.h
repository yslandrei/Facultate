#pragma once
#include "contactRepo.h"
#include <algorithm>

using std::sort;

class contactService {
private:
	contactRepo& cRepo;

	

public:
	contactService(contactRepo& cRepo) :
		cRepo{ cRepo }
	{}

	const vector<contact>& getAll() const {
		return cRepo.getAll();
	}

	void addContact(const int id, const string nume, const string prenume, const string telefon, const string adresa, const string email, const string linkedin) {
		contact newContact = contact(id, nume, prenume, telefon, adresa, email, linkedin);
		cRepo.addContact(newContact);
	}

	void exportApel(const int id) {
		cRepo.exportApel(id);
	}

	void exportSms(const int id, const string mesaj) {
		cRepo.exportSms(id, mesaj);
	}

	bool cmpByNume(const contact& a, const contact& b) {
		return a.getNume() < b.getNume();
	}

	bool cmpByAdresa(const contact& a, const contact& b) {
		return a.getAdresa() < b.getAdresa();
	}

	vector<contact> sortOffers(const char cmp) {
		const vector<contact>& cList = cRepo.getAll();
		vector<contact> cSortedList;
		for (const auto& Contact : cList)
			cSortedList.push_back(Contact);
			
		/*if (cmp == 'n')
			sort(cSortedList.begin(), cSortedList.end(), cmpByNume);
		else if (cmp == 'a')
			sort(cSortedList.begin(), cSortedList.end(), cmpByAdresa);*/

		return cSortedList;
	}
};