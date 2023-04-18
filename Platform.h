#pragma once
#include "Entity.h"

class Platform : public Entity {
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

};

namespace PlatformHelper {
	std::map<int, Platform*> list;

	int createPlatform(sf::RectangleShape& shape) {
		auto tempPlatform = new Platform(shape.getPosition(), shape);

		EntityHelper::list[tempPlatform->id] = tempPlatform;
		list[tempPlatform->id] = tempPlatform;

		return tempPlatform->id;
	}

	int createTexturedPlatform(sf::Vector2f position, sf::Vector2f size, sf::Texture* texture) {

		auto tempShape = sf::RectangleShape();
		tempShape.setPosition(position);
		tempShape.setTexture(texture);
		tempShape.setSize(size);

		auto tempPlatform = new Platform(tempShape);

		EntityHelper::list[tempPlatform->id] = tempPlatform;
		list[tempPlatform->id] = tempPlatform;

		return tempPlatform->id;
	}
}