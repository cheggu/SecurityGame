#pragma once
#include "SFML/Graphics.hpp"
#include "Utils.h"
#include "Entity.h"

class BaseObject : public Entity {
public:
	//sf::RectangleShape* drawable;
	std::map<int, sf::Drawable*> drawableList = {};

	int id;
	sf::Vector2f position;
	sf::Vector2f size;

	BaseObject() {
		id = generateRandomNumberRange(1501, 2000);
		position = { 0,0 };
		size = { 0,0 };
	}

	void simulate();
};

namespace BaseObjectHelper {
	std::map<int, BaseObject*> list;

	int createObject() {
		auto tempEnt = new BaseObject();
		list[tempEnt->id] = tempEnt;

		return tempEnt->id;
	}

	//void simulateAll() {
	//	for (auto pair : list) {
	//		auto obj = pair.second;

	//		obj->simulate();

	//	}
	//}
}