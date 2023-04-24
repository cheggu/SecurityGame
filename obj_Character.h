#pragma once
#include "obj_Base.h"
#include "Player.h"
#include "Font.h"

enum character {
	bird0,
	bird1,
	bird2,
	hacker
};

sf::FileInputStream riddle0file;
sf::FileInputStream riddle1file;
sf::FileInputStream riddle2file;

//rot13 helloworld uryybjbeyq
std::vector<std::string> bird0_dialogue = { "hello, i am lord confidencius", "i am a keeper of the sacred relic of cryptus",
										   "solve our ciphers to earn your prize", "my cipher is located at\n/Content/Ciphers/cipher0.txt\nin the game files",
											"write your answer and save the document,\nand talk to me when you've solved it.", "my cipher is 'uryybjbeyq' and my hint is \n'a=n'" };

//caeser cryptography fubswrjudskb
std::vector<std::string> bird1_dialogue = { "hello, i am lord integrius", "i am a keeper of the sacred relic of cryptus",
											"solve our ciphers to earn your prize", "my cipher is located at\n/Content/Ciphers/cipher1.txt\nin the game files",
											"write your answer and save the document,\nand talk to me when you've solved it.", "my cipher is 'fubswrjudskb' and my hint is \n'a=d'\n'b=e\n'c=f'" };

//atbash security hvxfirgb
std::vector<std::string> bird2_dialogue = { "hello, i am lord availabilitus", "i am a keeper of the sacred relic of cryptus", 
											"solve our ciphers to earn your prize", "my cipher is located at\n/Content/Ciphers/cipher2.txt\nin the game files",
											"write your answer and save the document,\nand talk to me when you've solved it.", "my cipher is 'hvxfirgb' and my hint is \n'a=z'\n'b=y'\n'c=x'" };

std::vector<std::string> hacker_dialogue = { "huh?", "why are you here?\nthis is my root domain.", "... you're here to challenge me,\naren't you?", "well then, prepare to be dereferenced.", ""};

class Character : public BaseObject {

private:
	char riddle0attempt[10], riddle1attempt[12], riddle2attempt[8];
	sf::IntRect rect;
	sf::Vector2f position;
	sf::Sprite sprite;
	
	sf::Clock skipDialogueClock;
	float minSkipDialogueAmount = 0.5f;
	sf::Clock readclock;
	sf::Text interactText;
	int dialogue_counter;
	bool cipher_solved;
	bool ishacker = false;

public:
	
	character _character;
	bool isQuestGiver = false;

	Character() {
		position = { 0,0 };
		sprite = sf::Sprite();
	}

	Character(sf::IntRect rect) {
		position = {(float)rect.left, (float)rect.top};
		sprite = sf::Sprite();
		sprite.setTextureRect(rect);

		interactText.setFont(Font::emulogic);
		interactText.setString("e - talk");
		interactText.setPosition(sprite.getPosition().x + (sprite.getLocalBounds().width / 2.0f) - (interactText.getGlobalBounds().width / 4.f), sprite.getPosition().y - 20);
		interactText.setCharacterSize(10);
		interactText.setFillColor(sf::Color::White);

		rect = (sf::IntRect)sprite.getGlobalBounds();

		drawableList[0] = &sprite;
		drawableList[1] = &interactText;
	}

	Character(sf::Vector2f _position, sf::Sprite _sprite, character c) {
		position = _position;
		sprite = _sprite;

		_character = c;
		
		riddle0file.open("Content/Ciphers/cipher0.txt");
		riddle1file.open("Content/Ciphers/cipher1.txt");
		riddle2file.open("Content/Ciphers/cipher2.txt");

		sprite.setPosition(position);

		interactText.setFont(Font::emulogic);
		interactText.setString("e - talk");
		interactText.setPosition(sprite.getPosition().x + (sprite.getLocalBounds().width / 2.0f) - (interactText.getGlobalBounds().width / 4.f), sprite.getPosition().y - 20);
		interactText.setCharacterSize(10);
		interactText.setFillColor(sf::Color::White);

		rect = (sf::IntRect)sprite.getGlobalBounds();

		if (c == hacker) {
			rect.height += 100;
			rect.width += 100;
			rect.left -= 50;
			rect.top -= 50;
			ishacker = true;
		}

		drawableList[0] = &sprite;
		drawableList[1] = &interactText;

		skipDialogueClock.restart();
	}

	void simulate() {
		checkPlayerRange();
	}

	bool checkPlayerRange() {
		for (auto pair : PlayerHelper::list) {
			auto p = pair.second;

			if (rect.contains((sf::Vector2i)p->position)) {
				//std::cout << "contains!" << std::endl;
				if (GetAsyncKeyState(0x45) & 0x8000) {
					interact();
					//std::cout << "interacting!" << std::endl;
					return true;
				}
			}
			if (abs(p->position.x - position.x) > 300 || abs(p->position.y - position.y) > 300) {
				interactText.setString("e - talk");
				interactText.setPosition(sprite.getPosition().x + 30, sprite.getPosition().y - (interactText.getGlobalBounds().height) - 10);
			}
		}
		return false;
	}

	bool isCipherSolved() {
		return cipher_solved;
	}

	void updateText(std::string text) {
		interactText.setString(text);
		interactText.setPosition(sprite.getPosition().x + 30, sprite.getPosition().y - (interactText.getGlobalBounds().height) - 10);
	}

	void interact() {
		if (skipDialogueClock.getElapsedTime().asSeconds() > minSkipDialogueAmount) {
			std::cout << _character << std::endl;

			
			memset(riddle0attempt, 0, sizeof riddle0attempt);
			memset(riddle1attempt, 0, sizeof riddle1attempt);
			memset(riddle2attempt, 0, sizeof riddle2attempt);

			memset(&riddle0file, 0, sizeof riddle0file);
			memset(&riddle1file, 0, sizeof riddle1file);
			memset(&riddle2file, 0, sizeof riddle2file);

			riddle0file.open("Content/Ciphers/cipher0.txt");
			riddle1file.open("Content/Ciphers/cipher1.txt");
			riddle2file.open("Content/Ciphers/cipher2.txt");

			switch (_character) {
			case bird0:
				isQuestGiver = true;
				interactText.setString(bird0_dialogue.at(dialogue_counter));

				if (dialogue_counter == bird0_dialogue.size() - 1) {
					riddle0file.read(riddle0attempt, 11);

					std::cout << riddle0attempt << std::endl;

					if (strcmp(riddle0attempt, "helloworld") == 0) {
						cipher_solved = true;
					}
				}
				else {
					dialogue_counter++;
				}
				break;
			case bird1:
				isQuestGiver = true;
				interactText.setString(bird1_dialogue.at(dialogue_counter));

				if (dialogue_counter == bird1_dialogue.size() - 1) {
					riddle1file.read(riddle1attempt, 13);
					if (strcmp(riddle1attempt, "cryptography") == 0) {
						cipher_solved = true;
					}
				}
				else {
					dialogue_counter++;
				}
				break;
			case bird2:
				isQuestGiver = true;
				interactText.setString(bird2_dialogue.at(dialogue_counter));

				if (dialogue_counter == bird2_dialogue.size() - 1) {
					riddle2file.read(riddle2attempt, 8);

					std::cout << riddle2attempt << std::endl;

					if (strcmp(riddle2attempt, "security") == 0) {
						cipher_solved = true;
					}
				}
				else {
					dialogue_counter++;
				}
				break;
			case hacker:
				isQuestGiver = false;
				interactText.setString(hacker_dialogue.at(dialogue_counter));
				if (dialogue_counter == hacker_dialogue.size() - 1) {

					interactText.setFillColor(sf::Color::Transparent);
					sprite.setColor(sf::Color::Transparent);
					//BossEvent::BossFight_03();
					std::cout << "start boss 3 event" << std::endl;
					spawnFinalBoss = true;
				}
				else {
					dialogue_counter++;
				}
				break;

			}
			
			interactText.setPosition(sprite.getPosition().x - (interactText.getGlobalBounds().width / 4), sprite.getPosition().y -(interactText.getGlobalBounds().height) - 10);
			skipDialogueClock.restart();
		}
	}

	void setScale(sf::Vector2f scale) {
		sprite.setScale(scale);
		interactText.setPosition(sprite.getPosition().x + (sprite.getGlobalBounds().width / 2.0f) - (interactText.getGlobalBounds().width / 4.f), sprite.getPosition().y - 20);
		rect = (sf::IntRect)sprite.getGlobalBounds();
	}

	void setPosition(sf::Vector2f position) {
		sprite.setPosition(position);
		interactText.setPosition(sprite.getPosition().x + (sprite.getGlobalBounds().width / 2.0f) - (interactText.getGlobalBounds().width / 4.f), sprite.getPosition().y - 20);
		rect = (sf::IntRect)sprite.getGlobalBounds();
	}

};


namespace CharacterHelper {
	std::map<int, Character*> list;

	int createCharacter(sf::Vector2f position, sf::Sprite sprite, character c) {
		auto tempEnt = new Character(position, sprite, c);

		list[tempEnt->id] = tempEnt;
		BaseObjectHelper::list[tempEnt->id] = tempEnt;

		return tempEnt->id;
	}
}