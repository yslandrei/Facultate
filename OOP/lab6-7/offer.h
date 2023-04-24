#pragma once
#include <string>
#include <iostream>

using std::ostream;
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

	offer() = default;

	offer(const offer& ot) :
		id{ ot.id },
		name{ ot.name },
		dest{ ot.dest },
		type{ ot.type },
		price{ ot.price } {
		//std::cout << "copy\n";
	}

	int getId() const;

	string getName() const;

	string getDest() const;

	string getType() const;

	int getPrice() const;

	offer& operator=(const offer& other);

	bool operator==(const offer& other) const;

	bool operator!=(const offer& other) const;

	friend ostream& operator<<(ostream& os, const offer& Offer);
};

