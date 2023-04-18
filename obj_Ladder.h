#pragma once
#include "obj_Base.h"
#include "Player.h"
#include <iostream>

class Ladder : public BaseObject {
private:
	sf::Texture texture;
	sf::IntRect rect;
	sf::Sprite *sprite;
	std::vector<sf::Drawable*> localDrawList = {};
	sf::Vector2f teleportLocation = {};
	sf::Vector2f lastTeleportOrigin = {};
	

public:
	int height;

	Ladder(int h, sf::Vector2f position, sf::Vector2f scale, sf::Vector2f destination) {
		height = h;
		for (int i = 0; i < height; i++) {
			//create base ladder model sprite
			//add to drawable list

			if (!texture.loadFromFile("Content/Sprites/Other/ladder.png")) {
				std::cout << "Content/Sprites/Other/ladder.png missing" << std::endl;
			}
			rect = sf::IntRect(0, 0, 8, 8);
			sprite = new sf::Sprite(texture, rect);
			sprite->setScale(scale);
			sprite->setPosition(position.x, position.y + (i*(8*scale.y)));
			
			localDrawList.push_back(sprite);
			drawableList[i] = localDrawList.at(localDrawList.size() - 1);
		}

		rect = sf::IntRect(position.x, position.y, 8 * scale.x, h * 8 * scale.y);

		teleportLocation = destination;
	}

	void simulate() {
		checkPlayerRange();
	}


	void setTeleportLocation(sf::Vector2f location) {
		teleportLocation = location;
	}

	bool checkPlayerRange() {
		for (auto pair : PlayerHelper::list) {
			auto p = pair.second;

			//std::cout << "player: x" << p->position.x << " y" << p->position.y << "\nladder: x" << rect.left << " y" << rect.top << std::endl;

			if (rect.contains((sf::Vector2i)p->position)) {
				//std::cout << "contains!" << std::endl;
				if (GetAsyncKeyState(0x45) & 0x8000) {
					interact();
					std::cout << "interacting!" << std::endl;
					return true;
				}
			}
		}
		return false;
	}

	void interact() {
		for (auto pair : PlayerHelper::list) {
			auto p = pair.second;
			p->setPos(teleportLocation);
		}
	}
};

namespace LadderObjectHelper {
	std::map<int, Ladder*> list;

	int createLadder(int height, sf::Vector2f position, sf::Vector2f scale, sf::Vector2f teleportLocation) {
		auto tempEnt = new Ladder(height, position, scale, teleportLocation);

		list[tempEnt->id] = tempEnt;
		BaseObjectHelper::list[tempEnt->id] = tempEnt;

		return tempEnt->id;
	}

	
}