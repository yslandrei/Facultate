#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Wiskey {
private:
	int ice;
	vector<string> flavs;
	int size;

public:
	Wiskey(int ice, vector<string> flavs, int size) :
		ice{ice},
		flavs{flavs},
		size{size}
	{}

	Wiskey& operator>>(ostream& os) {
		os << (size == 1 ? "small " : "large ") << "with " << ice << " ice and ";
		os << flavs.size() << " flavours\n";
		return *this;
	}

	vector<string>::iterator begin() {
		return flavs.begin();
	}

	vector<string>::iterator end() {
		return flavs.end();
	}
};

class Builder {
private:
	int ice;
	vector<string> flavs;
	int size;

public:
	Builder(int size) : size{size}, ice{0} {}

	Builder& addFlavour(string flavour) {
		flavs.push_back(flavour);
		return *this;
	}

	Builder& addIce() {
		ice++;
		return *this;
	}

	Wiskey build() {
		return Wiskey(ice, flavs, size);
	}
};

int main() {
	Builder b{ 1 };
	Wiskey w1 = b.addFlavour("persica").build();
	b.addIce().addIce();
	Wiskey w2 = b.addFlavour("gin").build();

	w1 >> cout;
	for (auto& f : w1) {
		cout << f << ", ";
	}
	cout << "\n";
	w2 >> cout;

	for (auto& f : w2) {
		cout << f << ", ";
	}
	cout << "\n";
}

