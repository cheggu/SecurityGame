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

	float* health;

	HealthUIElement(Player& player) {
		float intPad = 4.f, extPad = 10.0f;
		float sizex = 200, sizey = 15;

		health = &player.health;

		positionBorder = { extPad, extPad };
		positionValue = { intPad + extPad, intPad + extPad };
		sizeBorder = { sizex + (intPad * 2), sizey + (intPad * 2) };
		sizeValue = { sizex, sizey };

		healthBorder.setPosition(positionBorder - sf::Vector2f({ 2000,2000 }));
		healthBorder.setSize(sizeBorder);
		healthBorder.setFillColor(sf::Color(0xffa3a3a3));

		healthValue.setPosition(positionValue - sf::Vector2f({2000,2000}));
		healthValue.setSize(sizeValue);
		healthValue.setFillColor(sf::Color::Red);

		drawableList[0] = &healthBorder;
		drawableList[1] = &healthValue;
	}

	void update() {
		healthValue.setSize({ sizeValue.x * (*health / 100.0f), sizeValue.y });
	}
};

namespace UIHealthHelper {
	std::map<int, HealthUIElement*> list;

	int createHealthBar(Player& player) {
		auto tempEnt = new HealthUIElement(player);

		list[tempEnt->id] = tempEnt;
		UIElementHelper::list[tempEnt->id] = tempEnt;

		return tempEnt->id;
	}
}