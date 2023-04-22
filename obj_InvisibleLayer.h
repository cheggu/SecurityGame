#pragma once
#include "obj_Base.h"

class InvisibleLayer : public BaseObject {
private:
	sf::Texture text;
	sf::Sprite sprite;
	bool render = true;

public:

	InvisibleLayer(sf::IntRect rect) {
		if (!text.loadFromFile("Content/Sprites/Icons/invisible-platform.png")) {
			std::cout << "invisible layer fault" << std::endl;
		}
		sprite.setPosition(rect.left, rect.top);
		sprite.setTexture(text);
		sprite.setTextureRect(rect);
	}

	void enable() {
		render = true;
		sprite.setColor(sf::Color::White);
	}
	
	void disable() {
		render = false;
		sprite.setColor(sf::Color::Transparent);
	}

	sf::Sprite getSprite() {
		return sprite;
	}

	bool isInvisible() {
		return render;
	}

};


namespace InvisLayerHelper {
	std::map<int, InvisibleLayer*> list;

	int createInvisibleLayer(sf::IntRect rect) {
		auto tempEnt = new InvisibleLayer(rect);

		list[tempEnt->id] = tempEnt;
		BaseObjectHelper::list[tempEnt->id] = tempEnt;

		return tempEnt->id;
	}
}