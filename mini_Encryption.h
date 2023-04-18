#pragma once
#include "mini_Base.h"
#include "SFML/Graphics.hpp"
#include "ui_Button.h"
#include "Includes.h"




class EncryptionMinigame : public Minigame {
public:
	

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

	EncryptionMinigame() { //EncryptionMinigame(sf::RenderWindow& referenceToWindow) : window(referenceToWindow) {
		std::string intro = "a hacker has encrypted everything on the network! \n\nfigure out what encryption algorithms are used\n\non each part of the system to move forward";
			// a hacker has encrypted all of the files on the system!
			// figure out what encryption algorithms are used on each part of the system to move forward

			// encryption algorithms 
			// caesar cipher
			// rot13
			// vigenere

		UIButtonHelper::createExactButton({ WIDTH / 10, HEIGHT / 10 }, { WIDTH * 0.8f, HEIGHT * 0.8f }, sf::Color(229, 228, 233, 0xaa), intro);

	}

	void start();
	void end(MINIGAME_STATUS reason);

};

void Minigames::minigameInitEncryptDecrypt() {
	EncryptionMinigame minigame;

	Minigames::createMinigame(minigame);
}