#pragma once
#include "Entity.h"

class Platform : public Entity {
public:
	Platform(sf::Vector2f pos, sf::RectangleShape& shape) {
		drawable = &shape;
		position = pos;
	}

};

namespace PlatformHelper {
	std::map<int, Platform*> list;

	int createPlatform(sf::Vector2f pos, sf::RectangleShape& shape) {
		auto tempPlatform = new Platform(pos, shape);

		EntityHelper::list[tempPlatform->id] = tempPlatform;
		list[tempPlatform->id] = tempPlatform;

		return tempPlatform->id;
	}
}