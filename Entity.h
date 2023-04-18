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
	float health = -1;

	Entity() {

		id = generateID();
		
		
		
		position = { 0,0 };
		velocity = { 0,0 };
		acceleration = { 0,0 };
	}

	void damage(float amount);

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

void Entity::damage(float amount) {
	health -= amount;
	if (health == 0) {
		EntityHelper::list.erase(this->id);
	}
}