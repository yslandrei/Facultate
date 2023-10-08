#pragma once
#include "student.h"
#include <vector>
#include <exception>
#include <sstream>
#include <fstream>

class StudentRepo {
private:
	vector<Student> sList;

public:
	StudentRepo() {
		loadFromFile();
	}

	vector<Student> getAll() {
		return sList;
	}

	void setAll(vector<Student> sList) {
		this->sList = sList;
	}

	void modStudent(Student student) {
		for (auto& s : sList) {
			if (s.getId() == student.getId()) {
				s = student;
				saveToFile();
				return;
			}
		}
		throw exception("Studentul nu a fost gasit!");
	}

	void popStudent(int id) {
		int c = 0;
		for (auto& s : sList) {
			if (s.getId() == id) {
				sList.erase(sList.begin() + c);
				saveToFile();
				return;
			}
			c++;
		}
		throw exception("Studentul nu a fost gasit!");
	}

	//loads all students in the repo from "students.csv"
	void loadFromFile() {
		ifstream fin("students.csv");
		string line;
		while (getline(fin, line)) {
			Student s;
			stringstream ss(line);
			string token;
			getline(ss, token, ',');
			s.setId(stoi(token));
			getline(ss, token, ',');
			s.setName(token);
			getline(ss, token, ',');
			s.setAge(stoi(token));
			getline(ss, token, ',');
			s.setFacultate(token);
			sList.push_back(s);
		}
		fin.close();
	}
	
	//saves all students in the repo to "students.csv"
	void saveToFile() {
		ofstream fout("students.csv");
		for (auto& s : sList) {
			fout << s.getId() << "," << s.getName() << "," << s.getAge() << "," << s.getFacultate() << endl;
		}
		fout.close();
	}
};