#pragma once
#include "obj_Base.h"
#include "Player.h"
#include "Platform.h"
#include <iostream>

class Gate : public BaseObject {
private:
	sf::Texture texture;
	sf::IntRect rect;
	sf::Sprite* sprite;
	std::vector<sf::Drawable*> localDrawList = {};
	bool enabled = true;
	int platformID;
	sf::RectangleShape rectShape;

public:
	int height;

	Gate(int h, sf::Vector2f position, sf::Vector2f scale) {
		height = h;
		for (int i = 0; i < height; i++) {
			//create base ladder model sprite
			//add to drawable list

			if (!texture.loadFromFile("Content/Sprites/Other/gate.png")) {
				std::cout << "Content/Sprites/Other/gate.png missing" << std::endl;
			}
			rect = sf::IntRect(0, 0, 8, 8);
			sprite = new sf::Sprite(texture, rect);
			sprite->setScale(scale);
			sprite->setPosition(position.x, position.y + (i * (8 * scale.y)));

			localDrawList.push_back(sprite);
			drawableList[i] = localDrawList.at(localDrawList.size() - 1);
		}

		rect = sf::IntRect(position.x, position.y, 8 * scale.x, h * 8 * scale.y);

		rectShape.setPosition(rect.left, rect.top);
		rectShape.setSize(sf::Vector2f(rect.width, rect.height));
		platformID = PlatformHelper::createPlatform(rectShape);
	}

	bool toggle() {
		enabled = !enabled;
		PlatformHelper::list.at(platformID)->toggle();

		if (enabled) {
			for (auto drawable : drawableList) {
				auto sprite = (sf::Sprite*)drawable.second;
				sprite->setColor(sf::Color::White);
				
			}
			rectShape.setFillColor(sf::Color::Red);
		}
		else {
			for (auto drawable : drawableList) {
				auto sprite = (sf::Sprite*)drawable.second;
				sprite->setColor(sf::Color::Transparent);

			}
			rectShape.setFillColor(sf::Color::White);
		}

		return enabled;
	}

	void enable() {
		enabled = true;
		PlatformHelper::list.at(platformID)->enable();
	}

	void disable() {
		enabled = false;
		PlatformHelper::list.at(platformID)->disable();
	}

	void disableBullets() {
		PlatformHelper::list.at(platformID)->BulletCollisionsEnabled = false;
	}
};

namespace GateObjectHelper {
	std::map<int, Gate*> list;

	int createGate(int height, sf::Vector2f position, sf::Vector2f scale) {
		auto tempEnt = new Gate(height, position, scale);

		list[tempEnt->id] = tempEnt;
		BaseObjectHelper::list[tempEnt->id] = tempEnt;

		return tempEnt->id;
	}


}