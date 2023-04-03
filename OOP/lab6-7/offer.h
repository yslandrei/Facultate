#pragma once
#include <string>

using std::string;

class offer {
private:
	int id;
	string name;
	string dest;
	string type;
	int price;

public:
	offer(const int id, const string name, const string dest, const string type, const int price) :
		id{ id },
		name{ name },
		dest{ dest },
		type{ type },
		price{ price }
	{}
	
	int getId() const;

	string getName() const;

	string getDest() const;

	string getType() const;

	int getPrice() const;
};

