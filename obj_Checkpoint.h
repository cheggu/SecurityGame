#pragma once
#include "obj_Base.h"
#include "Player.h"
#include "Font.h"


class Checkpoint : public BaseObject {
private:
	sf::FloatRect rect;
	sf::Vector2f position;
	sf::Text unlockText;
	sf::Clock textClock;

public:

	Checkpoint(sf::FloatRect _rect) {
		rect = _rect;
		position = { rect.left, rect.top };

		unlockText.setFont(Font::emulogic);
		unlockText.setString("E");
		unlockText.setPosition(rect.left + (rect.width / 2.0f) - (unlockText.getGlobalBounds().width / 4.f), rect.top - 20);
		unlockText.setCharacterSize(10);
		unlockText.setFillColor(sf::Color::White);

		drawableList[0] = &unlockText;

		
	}

	void simulate() {
		checkPlayerRange();

		if (textClock.getElapsedTime().asSeconds() > 3) {
			unlockText.setString("E");
		}

		unlockText.setPosition(rect.left + (rect.width / 2.0f) - (unlockText.getGlobalBounds().width / 2.f), rect.top - 20);
	}

	bool checkPlayerRange() {
		for (auto pair : PlayerHelper::list) {
			auto p = pair.second;

			//std::cout << "player: x" << p->position.x << " y" << p->position.y << "\nladder: x" << rect.left << " y" << rect.top << std::endl;

			if (rect.contains(p->position)) {
				//std::cout << "contains!" << std::endl;
				if (GetAsyncKeyState(0x45) & 0x8000) {
					interact();
					//std::cout << "interacting!" << std::endl;
					std::cout << "player respawn point set to X" << p->lastCheckpoint.x << " Y" << p->lastCheckpoint.y << std::endl;
					textClock.restart();
					unlockText.setString("Respawn point set!");
					
					return true;
				}
			}
		}
		return false;
	}

	void interact() {
		for (auto pair : PlayerHelper::list) {
			auto p = pair.second;
			p->lastCheckpoint = {position.x, position.y - 50};
		}

	}
};

namespace CheckpointHelper {
	std::map<int, Checkpoint*> list;

	int createCheckpoint(sf::FloatRect rect) {
		auto tempEnt = new Checkpoint(rect);

		list[tempEnt->id] = tempEnt;
		BaseObjectHelper::list[tempEnt->id] = tempEnt;

		return tempEnt->id;
	}


}