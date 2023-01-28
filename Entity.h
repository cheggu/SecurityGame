#pragma once
#include "EntityType.h"

#include "Utils.h"

#include <SFML/Graphics.hpp>

class Entity {
public:
	sf::RectangleShape* drawable;
	int id;
	EntityType enttype;
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Vector2f acceleration;

	Entity() {
		id = generateRandomNumber();
		position = { 0,0 };
		velocity = { 0,0 };
		acceleration = { 0,0 };
	}

};

namespace EntityHelper {
	std::map<int, Entity*> list;

	int createEntity(EntityType type) {
		auto tempEnt = new Entity();
		tempEnt->enttype = type;
		list[tempEnt->id] = tempEnt;

		return tempEnt->id;
	}
}