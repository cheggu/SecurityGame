#pragma once
#include "obj_Base.h"
#include "Player.h"
#include "Font.h"

class Character : public BaseObject {

private:
	sf::IntRect rect;
	sf::Vector2f position;
	sf::Sprite sprite;
	sf::Text interactText;
	sf::Clock skipDialogueClock;
	float minSkipDialogueAmount = 0.5f;

public:
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

	Character(sf::Vector2f _position, sf::Sprite _sprite) {
		position = _position;
		sprite = _sprite;

		sprite.setPosition(position);

		interactText.setFont(Font::emulogic);
		interactText.setString("e - talk");
		interactText.setPosition(sprite.getPosition().x + (sprite.getLocalBounds().width / 2.0f) - (interactText.getGlobalBounds().width / 4.f), sprite.getPosition().y - 20);
		interactText.setCharacterSize(10);
		interactText.setFillColor(sf::Color::White);

		rect = (sf::IntRect)sprite.getGlobalBounds();

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
		}
		return false;
	}

	void interact() {
		if (skipDialogueClock.getElapsedTime().asSeconds() > minSkipDialogueAmount) {
			interactText.setString("TESTESTESTESTESTESTESTESTESdsadsadsad\nasdasdasdasdasdTESTEST!" + std::to_string(generateRandomNumber()));
			interactText.setPosition(sprite.getPosition().x + (sprite.getGlobalBounds().width / 2.0f) - (interactText.getGlobalBounds().width / 4.f), sprite.getPosition().y - 20);
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

	int createCharacter(sf::Vector2f position, sf::Sprite sprite) {
		auto tempEnt = new Character(position, sprite);

		list[tempEnt->id] = tempEnt;
		BaseObjectHelper::list[tempEnt->id] = tempEnt;

		return tempEnt->id;
	}
}