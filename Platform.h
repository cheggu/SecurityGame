#pragma once
#include "Entity.h"

class Platform : public Entity {
private:
	bool dropdown = false;
	bool enabled = true;

public:
	
	Platform(sf::Vector2f pos, sf::RectangleShape& shape) {
		enttype = OBJECT;
		drawable = &shape;
		position = pos;
	}

	Platform(sf::RectangleShape& shape) {
		enttype = OBJECT;
		drawable = &shape;
		position = shape.getPosition();
	}

	Platform(sf::Vector2f pos, sf::RectangleShape& shape, bool isDropdownPlatform) {
		enttype = OBJECT;
		drawable = &shape;
		position = shape.getPosition();
		dropdown = isDropdownPlatform;
		if (dropdown) {
			enttype = DROPDOWN;
		}
		else {
			enttype = OBJECT;
		}
	}

	bool isDropdown() {
		return dropdown;
	}

	bool toggle() {
		enabled = !enabled;
		BulletCollisionsEnabled = !BulletCollisionsEnabled;
		return enabled;
	}

	bool isEnabled() {
		return enabled;
	}

};

namespace PlatformHelper {
	std::map<int, Platform*> list;

	int createPlatform(sf::RectangleShape& shape) {
		shape.setFillColor(sf::Color::Red);

		auto tempPlatform = new Platform(shape.getPosition(), shape);

		EntityHelper::list[tempPlatform->id] = tempPlatform;
		list[tempPlatform->id] = tempPlatform;

		return tempPlatform->id;
	}

	//int createTexturedPlatform(sf::Vector2f position, sf::Vector2f size, sf::Texture* texture) {

	//	auto tempShape = sf::RectangleShape();
	//	tempShape.setPosition(position);
	//	tempShape.setTexture(texture);
	//	tempShape.setSize(size);

	//	auto tempPlatform = new Platform(tempShape);

	//	EntityHelper::list[tempPlatform->id] = tempPlatform;
	//	list[tempPlatform->id] = tempPlatform;

	//	return tempPlatform->id;
	//}

	int createDropdownPlatform(sf::RectangleShape& shape) {
		shape.setFillColor(sf::Color::Green);

		auto tempPlatform = new Platform(shape.getPosition(), shape, true);

		EntityHelper::list[tempPlatform->id] = tempPlatform;
		list[tempPlatform->id] = tempPlatform;

		return tempPlatform->id;
	}
}