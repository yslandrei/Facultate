#pragma once
#include <string>

using namespace std;

class Product {
private:
	int id;
	string name;
	string type;
	double price;

public:
	//constructor
	Product(int id, string name, string type, double price) {
		this->id = id;
		this->name = name;
		this->type = type;
		this->price = price;
	}

	//getters
	int getId() {
		return id;
	}

	string getName() {
		return name;
	}

	string getType() {
		return type;
	}

	double getPrice() {
		return price;
	}

	//setters
	void setId(int id) {
		this->id = id;
	}

	void setName(string name) {
		this->name = name;
	}

	void setType(string type) {
		this->type = type;
	}

	void setPrice(double price) {
		this->price = price;
	}
};
