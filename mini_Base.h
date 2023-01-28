#pragma once
#include "SFML/Graphics.hpp"



namespace Minigames {
	void minigameStartEncryptDecrypt(sf::RenderWindow& referenceToWindow);
	void minigameStartCrackPassword(sf::RenderWindow& referenceToWindow);
	void minigameStartMalwareAnalysis(sf::RenderWindow& referenceToWindow);
	void minigameStartPatchVulnerability(sf::RenderWindow& referenceToWindow);
	void minigameStartSteganography(sf::RenderWindow& referenceToWindow);

	enum MINIGAME_STATUS {
		WIN,
		LOSE
	};

}