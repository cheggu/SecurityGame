#pragma once
#include "SFML/Graphics.hpp"

enum MINIGAME_STATUS {
	WIN,
	LOSE,
	ACTIVE,
	INACTIVE

};

class Minigame {
public:
	MINIGAME_STATUS status = INACTIVE;

	Minigame() {
		
	}
};

namespace Minigames {
	void minigameInitEncryptDecrypt();
	void minigameInitCrackPassword(sf::RenderWindow& referenceToWindow);
	void minigameInitMalwareAnalysis(sf::RenderWindow& referenceToWindow);
	void minigameInitPatchVulnerability(sf::RenderWindow& referenceToWindow);
	void minigameInitSteganography(sf::RenderWindow& referenceToWindow);

	void InitializeMinigames() {
		minigameInitEncryptDecrypt();
	}

	std::map<int, Minigame*> list = {};

	void createMinigame(Minigame& minigame) {
		auto tempEnt = minigame;
		list[list.size()] = &tempEnt;
	}

	void printAllMinigameStatuses() {
		for (auto mini : list) {
			std::cout << mini.second->status << std::endl;
		}
	}
}