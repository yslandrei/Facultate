#pragma once
#include "song.h"
#include <vector>
#include <fstream>
#include <sstream>

class songRepository {
private:
	vector<song> sList;

public:
	songRepository() {
		loadSongs();
	}

	vector<song> getAll() {
		return sList;
	}

	void addSong(song s) {
		for (int i = 0; i < sList.size(); i++) {
			if (sList[i].getId() == s.getId()) {
				throw exception("Acest ID este prezent deja!");
			}
		}

		sList.push_back(s);
		saveSongs();
	}

	void modSong(song s) {
		for (int i = 0; i < sList.size(); i++)
			if (sList[i].getId() == s.getId()) {
				sList[i] = s;
				saveSongs();
				return;
			}

		throw exception("Nu exista nicio melodie cu acest ID!");
	}

	//remove a song from id
	void popSong(int id) {
		for (int i = 0; i < sList.size(); i++)
			if (sList[i].getId() == id) {
				sList.erase(sList.begin() + i);
				saveSongs();
				return;
			}

		throw exception("Nu exista nicio melodie cu acest ID!");
	}

	//load songs from file "songs.csv"
	void loadSongs() {
		ifstream fin("songs.csv");
		string line;
		while (getline(fin, line)) {
			song s(0, "", "", 0);
			stringstream ss(line);
			string token;
			getline(ss, token, ',');
			s.setId(stoi(token));
			getline(ss, token, ',');
			s.setTitle(token);
			getline(ss, token, ',');
			s.setArtist(token);
			getline(ss, token, ',');
			s.setRank(stoi(token));
			sList.push_back(s);
		}
		fin.close();
	}

	//save songs to file "songs.csv"
	void saveSongs() {
		ofstream fout("songs.csv");
		for (int i = 0; i < sList.size(); i++)
			fout << sList[i].getId() << "," << sList[i].getTitle() << "," << sList[i].getArtist() << "," << sList[i].getRank() << endl;
		fout.close();
	}
};
