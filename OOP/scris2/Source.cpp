#include <iostream>
#include <vector>
#include <string>

using namespace std;

template <typename t>
class Cos {
private:
	vector<t> v;
public:


	Cos operator+ (const t& o) {
		Cos temp = *this;
		temp.v.push_back(o);
		return temp;
	}

	Cos& undo() {
		if (v.size())
			v.pop_back();
		return *this;
	}

	void tipareste(ostream& os) {
		for (auto o : v)
			os << o << " ";
	}

};

void cumparaturi() {
	Cos<string> cos;//creaza un cos de cumparaturi
	cos = cos + "Mere"; //adauga Mere in cos
	cos + "Pula"; //adauga Mere in cos
	cos.tipareste(cout);//tipareste elementele din cos (Mere)
	cout << "\n";
	cos = cos + "Paine" + "Lapte";//adauga Paine si Lapte in cos
	cos.tipareste(cout);//tipareste elementele din cos (Mere)
	cout << "\n";

	cos.undo().undo();//elimina ultimele doua produse adaugate
	cos.tipareste(cout);//tipareste elementele din cos (Mere)
	cout << "\n";

}

int main() {
	cumparaturi();
	_CrtDumpMemoryLeaks();
}