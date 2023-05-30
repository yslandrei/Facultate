#pragma once
/*
  Abstract class
  update method need to be implemented by observers
*/
class observer {
public:
	virtual void update() = 0;
};
/*
  Observable or Subject - class that notify changes in it's state
  Derive from this class if you want to provide notifications
*/
#include <vector>
#include <algorithm>
class observable {
private:
	/*Non owning pointers to observer instances*/
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
		for (auto obs : observers) {
			obs->update();
		}
	}
};