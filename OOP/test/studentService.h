#pragma once
#include "studentRepo.h"
#include "observer.h"
#include <queue>

class StudentService : public observable {
private:
	StudentRepo& sRepo;
	queue<vector<Student>> undoStack;
	queue<vector<Student>> redoStack;

public:
	StudentService(StudentRepo& sRepo) : sRepo{ sRepo } {}

	vector<Student> getAll() {
		return sRepo.getAll();
	}

	void makeAllYounger() {
		auto sList = sRepo.getAll();
		undoStack.push(getAll());
		for (auto s : sList) {
			s.setAge(s.getAge() - 1);
			sRepo.modStudent(s);
		}
		notify();
	}

	void makeAllOlder() {
		auto sList = sRepo.getAll();
		undoStack.push(getAll());
		for (auto s : sList) {
			s.setAge(s.getAge() + 1);
			sRepo.modStudent(s);
		}
		notify();
	}

	void popStudents(vector<int> ids) {
		undoStack.push(getAll());
		for (int id : ids)
			sRepo.popStudent(id);
		notify();
	}

	void undo() {
		if (undoStack.empty())
			throw exception("Nu se mai poate face Undo!");
		redoStack.push(getAll());
		sRepo.setAll(undoStack.front());
		undoStack.pop();
		notify();
	}

	void redo() {
		if (redoStack.empty())
			throw exception("Nu se mai poate face Redo!");
		undoStack.push(getAll());
		sRepo.setAll(redoStack.front());
		redoStack.pop();
		notify();
	}
};