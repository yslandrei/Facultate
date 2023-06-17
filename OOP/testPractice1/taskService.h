#pragma once
#include "taskRepository.h"
#include "observer.h"

class taskService : public observable {
private:
	taskRepository& tRepo;

public:
	//constructor
	taskService(taskRepository& tRepo) : tRepo { tRepo } {}

	//getall tasks
	vector<task>& getAll() {
		return this->tRepo.getAll();
	}

	//getall tasks with open state
	vector<task> getAllOpen() {
		vector<task> allOpen;
		for (auto& t : this->tRepo.getAll())
			if (t.getState() == "open")
				allOpen.push_back(t);
		return allOpen;
	}

	//getall tasks with closed state
	vector<task> getAllClosed() {
		vector<task> allClosed;
		for (auto& t : this->tRepo.getAll())
			if (t.getState() == "closed")
				allClosed.push_back(t);
		return allClosed;
	}
	
	//getall tasks with inprogress state
	vector<task> getAllInProgress() {
		vector<task> allInProgress;
		for (auto& t : this->tRepo.getAll())
			if (t.getState() == "inprogress")
				allInProgress.push_back(t);
		return allInProgress;
	}

	//validate task
	void validate(task t) {
		if(t.getDescription().size() == 0)
			throw exception("Description cannot be empty!");
		
		if(t.getState() != "open" && t.getState() != "inprogress" && t.getState() != "closed") 
			throw exception("State must be open, inprogress or closed!");

		if (t.getProgrammers().size() == 0)
			throw exception("Programmers cannot be empty!");
		if (t.getProgrammers().size() > 4)
			throw exception("Programmers cannot be more than 4!");
	}

	//add task
	void addTask(int id, string description, string state, vector<string> programmers) {
		task t(id, description, state, programmers);
		validate(t);
		this->tRepo.addTask(t);
		notify();
	}

	//modify task with another state
	void modTask(int id, string state) {
		vector<task> tList = tRepo.getAll();
		for(int i = 0; i < tList.size(); i++)
			if (tList[i].getId() == id) {
				tRepo.modTask(id, task(tList[i].getId(), tList[i].getDescription(), state, tList[i].getProgrammers()));
				notify();
				return;
			}
	}

	//search task by programmer
	vector<task> search(string keyword) {
		if (keyword.size() == 0)
			return this->tRepo.getAll();

		vector<task> searchedTasks;
		for (auto t : this->tRepo.getAll())
			for (auto p : t.getProgrammers())
				//check if keyword is inside of every programmer
				if (p.find(keyword) != string::npos) {
					searchedTasks.push_back(t);
					break;
				}

		return searchedTasks;
	}
};