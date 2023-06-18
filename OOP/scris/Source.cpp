#include <string>
#include <vector>
#include <iostream>

using namespace std;

template<typename t>
class Geanta {
private:
	string owner;
	vector<t> obiecte;

public:
	Geanta(string nume) : owner{ nume } {}

	Geanta operator+(const t& o) {
		Geanta temp = *this;
        temp.obiecte.push_back(o);
        return temp;

		/*obiecte.push_back(o);
		return *this;*/
	}

	typename vector<t>::iterator begin() {
		return obiecte.begin();
	}

	typename vector<t>::iterator end() {
		return obiecte.end();
	}
};


int main() {
	Geanta<string> ganta{ "Ion" };//creaza geanta pentru Ion
	ganta = (ganta + string{ "haine" }); //adauga obiect in ganta
	ganta = (ganta + string{ "pahar" }); //adauga obiect in ganta
	ganta + string{ "pahar" };
	for (auto o : ganta) {//itereaza obiectele din geanta
		cout << o << "\n";
	}
}