#pragma once
#include <string>

using namespace std;

class song {
private:
	int id;
	string title;
	string artist;
	int rank;

public:
	song(int id, string title, string artist, int rank) {
		this->id = id;
		this->title = title;
		this->artist = artist;
		this->rank = rank;
	}

	//getters
	int getId() {
		return id;
	}

	string getTitle() {
		return title;
	}

	string getArtist() {
		return artist;
	}

	int getRank() {
		return rank;
	}

	//setters
	void setId(int id) {
		this->id = id;
	}

	void setTitle(string title) {
		this->title = title;
	}

	void setArtist(string artist) {
		this->artist = artist;
	}

	void setRank(int rank) {
		this->rank = rank;
	}
};