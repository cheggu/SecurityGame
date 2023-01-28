#pragma once
#include "mini_Base.h"
#include "SFML/Graphics.hpp"




class EncryptionMinigame {
public:
	sf::RenderWindow& window;

	std::string rot13_encode(std::string input) {
		std::string output = "";
		for (int i = 0; i < input.length(); i++) {
			char c = input[i];
			if (isalpha(c)) {
				if (isupper(c)) {
					c = ((c - 'A' + 13) % 26) + 'A';
				}
				else {
					c = ((c - 'a' + 13) % 26) + 'a';
				}
			}
			output += c;
		}
		return output;
	}


	std::string rot13_decode(std::string input) {
		std::string output = "";
		for (int i = 0; i < input.length(); i++) {
			char c = input[i];
			if (isalpha(c)) {
				if (isupper(c)) {
					c = ((c - 'A' + 13) % 26) + 'A';
				}
				else {
					c = ((c - 'a' + 13) % 26) + 'a';
				}
			}
			output += c;
		}
		return output;
	}

	EncryptionMinigame(sf::RenderWindow& referenceToWindow) : window(referenceToWindow) {
		// a hacker has encrypted all of the files on the system!
		// figure out what encryption algorithms are used on each part of the system to move forward

		// encryption algorithms 
		// caesar cipher
		// rot13
		// vigenere
	}

	void start();
	void end(Minigames::MINIGAME_STATUS reason);

};

void Minigames::minigameStartEncryptDecrypt(sf::RenderWindow& referenceToWindow) {
	EncryptionMinigame minigame(referenceToWindow);
	minigame.start();
}