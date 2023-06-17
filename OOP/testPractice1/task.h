#pragma once
#include <string>
#include <vector>

using namespace std;

class task {
private:
	int id;
	string description;
	string state;
	vector<string> programmers;

public:
	//constructor
	task(int id, string description, string state, vector<string> programmers) {
		this->id = id;
		this->description = description;
		this->state = state;
		this->programmers = programmers;
	}

	//getters
	int getId() {
		return this->id;
	}

	string getDescription() {
		return this->description;
	}

	vector<string> getProgrammers() {
		return this->programmers;
	}

	string getState() {
		return this->state;
	}

	//setters
	void setId(int id) {
		this->id = id;
	}

	void setDescription(string description) {
		this->description = description;
	}

	void setProgrammers(vector<string> programmers) {
		this->programmers = programmers;
	}

	void setState(string state) {
		this->state = state;
	}
};