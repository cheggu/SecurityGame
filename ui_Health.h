#pragma once
#include "Player.h"
#include "ui_Element.h"

class HealthUIElement : public uiElement{
public:
	sf::RectangleShape healthBorder;
	sf::RectangleShape healthValue;

	sf::Vector2f positionBorder;
	sf::Vector2f positionValue;
	sf::Vector2f sizeBorder;
	sf::Vector2f sizeValue;

	HealthUIElement() {
		float intPad = 4.f, extPad = 10.0f;
		float sizex = 200, sizey = 15;


		positionBorder = { extPad, extPad };
		positionValue = { intPad + extPad, intPad + extPad };
		sizeBorder = { sizex + (intPad * 2), sizey + (intPad * 2) };
		sizeValue = { sizex, sizey };

		healthBorder.setPosition(positionBorder);
		healthBorder.setSize(sizeBorder);
		healthBorder.setFillColor(sf::Color(0xffa3a3a3));

		healthValue.setPosition(positionValue);
		healthValue.setSize(sizeValue);
		healthValue.setFillColor(sf::Color::Red);

		drawableList[0] = &healthBorder;
		drawableList[1] = &healthValue;
	}

};

namespace UIHealthHelper {
	std::map<int, HealthUIElement*> list;

	int createHealthBar() {
		auto tempEnt = new HealthUIElement();

		list[tempEnt->id] = tempEnt;
		UIElementHelper::list[tempEnt->id] = tempEnt;

		return tempEnt->id;
	}
}