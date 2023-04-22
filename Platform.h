#pragma once
#include "Entity.h"

class Platform : public Entity {
private:
	bool dropdown = false;
	bool enabled = true;
	bool invisible = false;
	//sf::Texture invis_texture;
	//sf::Sprite& invis_sprite;

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

	Platform(sf::Vector2f pos, sf::RectangleShape& shape, bool isDropdownPlatform, bool isInvisiblePlatform) {
		enttype = OBJECT;
	
		//invis_texture.loadFromFile("Content/Sprites/Icons/invisible-platform.png");
		//invis_sprite.setTexture(invis_texture);

		//invis_sprite.setTextureRect((sf::IntRect)shape.getGlobalBounds());
		
		drawable = &shape;

		position = shape.getPosition();
		dropdown = isDropdownPlatform;
		invisible = isInvisiblePlatform;
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

	bool isInvisible() {
		return invisible;
	}

	bool toggle() {
		enabled = !enabled;
		BulletCollisionsEnabled = !BulletCollisionsEnabled;
		return enabled;
	}

	void enable() {
		enabled = true;
		BulletCollisionsEnabled = true;
	}

	void disable() {
		enabled = false;
		BulletCollisionsEnabled = false;
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

	int createDropdownPlatform(sf::RectangleShape& shape) {
		shape.setFillColor(sf::Color::Green);

		auto tempPlatform = new Platform(shape.getPosition(), shape, true);

		EntityHelper::list[tempPlatform->id] = tempPlatform;
		list[tempPlatform->id] = tempPlatform;

		return tempPlatform->id;
	}

	int createDropdownPlatform(sf::RectangleShape& shape, bool invisible) {
		shape.setFillColor(sf::Color::Green);

		auto tempPlatform = new Platform(shape.getPosition(), shape, true, true);

		EntityHelper::list[tempPlatform->id] = tempPlatform;
		list[tempPlatform->id] = tempPlatform;

		return tempPlatform->id;
	}
}