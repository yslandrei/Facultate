#include <string>

using std::string;

class contact {
private:
	int id;
	string nume, prenume, telefon, adresa, email, linkedin;
public:
	contact(const int id, const string nume, const string prenume, const string telefon, const string adresa, const string email, const string linkedin) :
		id{id},
		nume{nume},
		prenume{prenume},
		telefon{telefon},
		adresa{adresa},
		email{email},
		linkedin{linkedin}
	{}

	int getId() const{
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
};