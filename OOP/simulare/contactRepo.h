#include "contact.h"
#include <vector>
#include <exception>
#include <fstream>
#include <ctime>

using std::exception;
using std::vector;

class contactRepo {
private:
	vector<contact> cList;

public:
	const vector<contact>& getAll() const {
		return cList;
	}

	void addContact(contact newContact) {
		for (const auto& Contact : cList) {
			if (Contact.getId() == newContact.getId())
				throw exception("ID deja prezent");
		}
		cList.push_back(newContact);
	}

	void exportApel(int id) const {
		const string fileNameCsv = "apeluri.csv";
		std::ofstream csvout(fileNameCsv);

		time_t now = time(0);
		char* dt = ctime(&now);

		for (const auto& Contact : cList)
			csvout << Contact.getNume() << " " << Contact.getPrenume() << " " << Contact.getTelefon() << " " << dt;

		csvout.close();
	}

	void exportSms(const int id, const string mesaj) const {
		const string fileNameCsv = "mesaje.csv";
		std::ofstream csvout(fileNameCsv);

		time_t now = time(0);
		char* dt = ctime(&now);

		for (const auto& Contact : cList)
			csvout << Contact.getNume() << " " << Contact.getPrenume() << " " << Contact.getTelefon() << " " << dt << ": " << mesaj;

		csvout.close();
	}
};