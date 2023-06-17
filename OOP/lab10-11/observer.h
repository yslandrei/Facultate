#pragma once
#include <vector>
#include <algorithm>

class observer {
public:
	virtual void update() = 0;
};

class observable {
private:
	std::vector<observer*> observers;

public:
	void addObserver(observer* obs) {
		observers.push_back(obs);
	}

	void removeObserver(observer* obs) {
		observers.erase(std::remove(observers.begin(), observers.end(), obs), observers.end());
	}

protected:
	void notify() {
		for (auto obs : observers)
			obs->update();
	}
};