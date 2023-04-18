#pragma once
#include "ui_Element.h"
#include "SFML/Graphics.hpp"
#include "Includes.h"

enum InventoryItem {
	HANDS,
	BLASTER,
	SCANNER,
	DISGUISER,
	DDOS
};

class InventorySlot : public uiElement {
private:
	sf::RectangleShape OuterBox;
	sf::RectangleShape InnerBox;
	sf::Texture Texture;
	sf::Sprite Icon;


public:
	InventoryItem Item;

	InventorySlot(sf::Image icon, sf::Vector2f position, InventoryItem item) {
		OuterBox.setPosition(position);
		OuterBox.setFillColor(sf::Color(0x786d375a));
		OuterBox.setOutlineColor(sf::Color(0x4d46245a));
		OuterBox.setOutlineThickness(5);
		OuterBox.setSize({ 100,100 });
		
		Texture.loadFromImage(icon);
		Icon.setTexture(Texture);
		Icon.setPosition(position);

		drawableList[0] = &OuterBox;
		drawableList[1] = &Icon;
	}

	void draw() {
		window.draw(OuterBox);
		window.draw(Icon);
	}
	
	void setPosition(sf::Vector2f pos) {
		OuterBox.setPosition(pos);
		Icon.setPosition(pos);
	}

	sf::Vector2f getPosition() {
		return OuterBox.getPosition();
	}

};

namespace UIInventorySlotHelper {
	std::map<int, InventorySlot*> list;

	int createInventorySlot(sf::Image image, sf::Vector2f position, InventoryItem item) {
		auto tempEnt = new InventorySlot(image, position, item);

		list[tempEnt->id] = tempEnt;
		UIElementHelper::list[tempEnt->id] = tempEnt;

		return tempEnt->id;
	}

}

class InventoryUIElement : public uiElement {
public:
	enum InventoryItemStatus {
		EQUIPPED,
		STORED,
		COOLDOWN,
		LOCKED
	};

	std::map <InventorySlot, InventoryItemStatus> Inventory = {};

	InventoryUIElement() {
		//create 6 inv slots, positioning accordingly
		sf::Image image0;
		//image0.loadFromFile("Content\\Sprites\\Icons\\testicon.png");
		image0.loadFromFile("Content\\Sprites\\Icons\\blaster.png");

		UIInventorySlotHelper::createInventorySlot(image0, { (WIDTH / 3) - 2000, 15 - 2000 }, InventoryItem::HANDS);
		UIInventorySlotHelper::createInventorySlot(image0, { (WIDTH / 3) + 115 - 2000, 15 - 2000 }, InventoryItem::HANDS);
		UIInventorySlotHelper::createInventorySlot(image0, { (WIDTH / 3) + 230 - 2000, 15 - 2000 }, InventoryItem::HANDS);
		UIInventorySlotHelper::createInventorySlot(image0, { (WIDTH / 3) + 345 - 2000, 15 - 2000 }, InventoryItem::HANDS);
		UIInventorySlotHelper::createInventorySlot(image0, { (WIDTH / 3) + 460 - 2000, 15 - 2000 }, InventoryItem::HANDS);
		UIInventorySlotHelper::createInventorySlot(image0, { (WIDTH / 3) + 575 - 2000, 15 - 2000 }, InventoryItem::HANDS);
	}

	void update() {
		for (auto pair : Inventory) {
			auto item = pair.first;
			auto status = pair.second;

			if (status == EQUIPPED) {
				//highlight slot
			}
			else if (status == LOCKED) {
				//do not draw icon
			}
			else { //cooldowned or stored
				//unhighlight
			}
		}
	}
};

namespace UIInventoryHelper {
	std::map<int, InventoryUIElement*> list;

	int createInventory() {
		auto tempEnt = new InventoryUIElement();

		list[0] = tempEnt;
		UIElementHelper::list[tempEnt->id] = tempEnt;

		return tempEnt->id;
	}

}