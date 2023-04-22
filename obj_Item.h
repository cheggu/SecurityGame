#pragma once
#include "obj_Base.h"
#include "Player.h"
#include "Font.h"

class Item : public BaseObject {

private:
	sf::FloatRect rect;
	sf::Vector2f position;
	sf::Sprite sprite;
	sf::Text pickupText;
	InventoryItem item_id;

public:
	Item() {
		position = { 0,0 };
		sprite = sf::Sprite();
	}

	Item(sf::Vector2f _position, sf::Sprite _sprite, InventoryItem item) {
		position = _position;
		sprite = _sprite;
		item_id = item;

		sprite.setPosition(position);

		pickupText.setFont(Font::emulogic);
		pickupText.setString("E");
		pickupText.setPosition(sprite.getPosition().x + (sprite.getLocalBounds().width / 2.0f) - (pickupText.getGlobalBounds().width / 4.f), sprite.getPosition().y - 20);
		pickupText.setCharacterSize(10);
		pickupText.setFillColor(sf::Color::White);

		rect = sprite.getGlobalBounds();

		drawableList[0] = &sprite;
		drawableList[1] = &pickupText;
	}

	void simulate() {
		checkPlayerRange();
	}

	bool checkPlayerRange() {
		for (auto pair : PlayerHelper::list) {
			auto p = pair.second;

			//std::cout << "player: x" << p->position.x << " y" << p->position.y << "\nladder: x" << rect.left << " y" << rect.top << std::endl;

			if (rect.contains(p->position)) {
				//std::cout << "contains!" << std::endl;
				if (GetAsyncKeyState(0x45) & 0x8000) {
					interact();
					std::cout << "interacting!" << std::endl;
					return true;
				}
			}
		}
		return false;
	}

	void interact() {
		Inventory::unlockItem(item_id);
		sprite.setColor(sf::Color::Transparent);
		pickupText.setFillColor(sf::Color::Transparent);
	}

	void setScale(sf::Vector2f scale) {
		sprite.setScale(scale);
		pickupText.setPosition(sprite.getPosition().x + (sprite.getGlobalBounds().width / 2.0f) - (pickupText.getGlobalBounds().width / 4.f), sprite.getPosition().y - 20);
		rect = sprite.getGlobalBounds();
	}

	void setPosition(sf::Vector2f position) {
		sprite.setPosition(position);
		pickupText.setPosition(sprite.getPosition().x + (sprite.getGlobalBounds().width / 2.0f) - (pickupText.getGlobalBounds().width / 4.f), sprite.getPosition().y - 20);
		rect = sprite.getGlobalBounds();
	}

};


namespace ItemHelper {
	std::map<int, Item*> list;

	int createItem(sf::Vector2f position, sf::Sprite sprite, InventoryItem item_id) {
		auto tempEnt = new Item(position, sprite, item_id);

		list[tempEnt->id] = tempEnt;
		BaseObjectHelper::list[tempEnt->id] = tempEnt;

		return tempEnt->id;
	}
}