#pragma once
#include "SFML/Graphics.hpp"
#include "Utils.h"

class uiElement {
public:
	//sf::RectangleShape* drawable;
	std::map<int, sf::Drawable*> drawableList = {};

	int id;
	sf::Vector2f position;
	sf::Vector2f size;

	uiElement() {
		id = generateRandomNumber();
		position = { 0,0 };
		size = { 0,0 };
	}

};

namespace UIElementHelper {
	std::map<int, uiElement*> list;

	int createUIElement() {
		auto tempEnt = new uiElement();
		list[tempEnt->id] = tempEnt;

		return tempEnt->id;
	}
}