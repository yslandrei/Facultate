#include <string>
#pragma once

using std::string;

class contact {
private:
	int id;
	string nume, prenume, telefon, adresa, email, linkedin;
public:
	contact(const int id, const string nume, const string prenume, const string telefon, const string adresa, const string email, const string linkedin) :
		id{ id },
		nume{ nume },
		prenume{ prenume },
		telefon{ telefon },
		adresa{ adresa },
		email{ email },
		linkedin{ linkedin }
	{}

	int getId() const {
		return id;
	}

	string getNume() const {
		return nume;
	}

	string getPrenume() const {
		return prenume;
	}

	string getTelefon() const {
		return telefon;
	}

	string getAdresa() const {
		return adresa;
	}

	string getEmail() const {
		return email;
	}

	string getLinkedin() const {
		return linkedin;
	}

	contact& operator=(const contact& other) {
		if (this != &other) {
			this->id = other.getId();
			this->nume = other.getNume();
			this->prenume = other.getPrenume();
			this->telefon = other.getTelefon();
			this->adresa = other.getAdresa();
			this->email = other.getEmail();
			this->linkedin = other.getLinkedin();
		}
		return *this;
	}

	bool operator==(const contact& other) const {
		return id == other.id &&
			nume == other.nume &&
			prenume == other.prenume &&
			telefon == other.telefon &&
			adresa == other.adresa &&
			email == other.email &&
			linkedin == other.linkedin;
	}

};