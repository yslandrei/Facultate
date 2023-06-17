#pragma once
#include "songRepository.h"

class songService {
private:
	songRepository& sRepo;

public:
	songService(songRepository& sRepo) : sRepo{ sRepo } {}

	vector<song> getAll() {
		return sRepo.getAll();
	}

	void validateSong(song s) {
		if (s.getId() < 0)
			throw exception("ID-ul trebuie sa fie pozitiv!");
		if (s.getTitle().size() == 0)
			throw exception("Titlul nu poate fi vid!");
		if (s.getArtist().size() == 0)
			throw exception("Artistul nu poate fi vid!");
		if (s.getRank() < 0)
			throw exception("Rank-ul trebuie sa fie pozitiv!");
	}

	void addSong(int id, string title, string artist, int rank) {
		song s(id, title, artist, rank);
		validateSong(s);
		sRepo.addSong(s);
	}

	void popSong(int id) {
		vector<song> sList = sRepo.getAll();
		string artist;

		for (int i = 0; i < sList.size(); i++)
			if (sList[i].getId() == id)
				artist = sList[i].getArtist();
		
		int k = 0;
		for (int i = 0; i < sList.size(); i++)
			if (sList[i].getArtist() == artist)
				k++;

		if(k > 1)
			sRepo.popSong(id);
		else
			throw exception("Nu se poate sterge ultima melodie a unui artist!");
	}

	//modify a song from id
	void modSong(int id, string title, string artist, int rank) {
		song s(id, title, artist, rank);
		validateSong(s);
		sRepo.modSong(s);
	}
};