#pragma once
#include <string>

using namespace std;

class Student {
private:
	int id;
	string name;
	int age;
	string facultate;

public:
	//getters
	int getId() {
		return id;
	}

	string getName() {
		return name;
	}

	int getAge() {
		return age;
	}

	string getFacultate() {
		return facultate;
	}

	//setters
	void setId(int id) {
		this->id = id;
	}

	void setName(string name) {
		this->name = name;
	}

	void setAge(int age) {
		this->age = age;
	}

	void setFacultate(string facultate) {
		this->facultate = facultate;
	}
};