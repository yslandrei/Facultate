#pragma once
#include "task.h"
#include <fstream>

class taskRepository {
private:
	vector<task> tasks;

public:
	//constructor
	taskRepository() {
		loadTasks();
	}

	//getall tasks
	vector<task>& getAll() {
		return this->tasks;
	}

	void addTask(task t) {
		for (int i = 0; i < tasks.size(); i++) {
			if (tasks[i].getId() == t.getId()) {
				throw exception("Task already exists!");
			}
		}

		this->tasks.push_back(t);
		sort(this->tasks.begin(), this->tasks.end(), [](task t1, task t2) {
			return t1.getState() > t2.getState(); 
		});

		this->saveTasks();
	}

	//modify task with state
	void modTask(int id, task t) {
		for (int i = 0; i < tasks.size(); i++) {
			if (tasks[i].getId() == id) {
				tasks[i] = t;
				this->saveTasks();
				return;
			}
		}

		throw exception("Task does not exist!");
	}

	//load from file
	void loadTasks() {
		string fileName = "tasks.csv";
		ifstream fin(fileName);
		char line[1000] = "";
		while (fin.getline(line, 1000)) {
			char *p = strtok(line, ",");
			int id = atoi(p);
			p = strtok(NULL, ",");
			string description = p;
			p = strtok(NULL, ",");
			string state = p;
			p = strtok(NULL, ",");
			vector<string> programmers;
			
			while (p != NULL) {
				programmers.push_back(p);
				p = strtok(NULL, ",");
			}

			task t(id, description, state, programmers);
			this->tasks.push_back(t);
		}
	}

	//save tasks
	void saveTasks() {
		string fileName = "tasks.csv";
		ofstream fout(fileName);
		for (int i = 0; i < tasks.size(); i++) {
			fout << tasks[i].getId() << "," << tasks[i].getDescription() << "," << tasks[i].getState() << ",";
			vector<string> programmers = tasks[i].getProgrammers();
			for (int j = 0; j < programmers.size(); j++) {
				fout << programmers[j] << ",";
			}
			fout << endl;
		}
	}
};