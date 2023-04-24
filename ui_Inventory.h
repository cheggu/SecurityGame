#pragma once
#include "ui_Element.h"
#include "SFML/Graphics.hpp"
#include "Includes.h"

enum InventoryItem {
	DOSGUN,
	PORTGUN,
	CRYPTOGUN,
	BRUTEFORCE,
	INVNONE
};

class InventorySlot : public uiElement {
private:
	sf::RectangleShape OuterBox;
	sf::RectangleShape InnerBox;
	sf::Texture Texture;
	sf::Sprite Icon;
	sf::FloatRect rect;


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
		if (item == BRUTEFORCE) {
			Icon.setScale(2, 2);
		}
		else {
			Icon.setScale(4, 4);
		}
		Icon.setPosition(position);

		Item = item;

		rect = { position.x, position.y, 100, 100 };

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

	void select() {
		OuterBox.setOutlineColor(sf::Color::Green);
	}

	void unselect() {
		OuterBox.setOutlineColor(sf::Color(0x4d46245a));
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

	//std::map <InventorySlot, InventoryItemStatus> Inventory = {};

	InventoryUIElement() {
		//create 6 inv slots, positioning accordingly
		sf::Image image0;
		//image0.loadFromFile("Content\\Sprites\\Icons\\testicon.png");
		image0.loadFromFile("Content\\Sprites\\Icons\\blaster.png");

		sf::Image image1;
		image1.loadFromFile("Content\\Sprites\\Icons\\scanner.png");

		sf::Image image2;
		image2.loadFromFile("Content\\Sprites\\Icons\\crypto.png");

		sf::Image image3;
		image3.loadFromFile("Content\\Sprites\\Icons\\brute.png");

		UIInventorySlotHelper::createInventorySlot(image0, { (WIDTH / 2) - 230 - 2000, 15 - 2000 }, InventoryItem::DOSGUN);
		UIInventorySlotHelper::createInventorySlot(image1, { (WIDTH / 2) - 115 - 2000, 15 - 2000 }, InventoryItem::PORTGUN);
		UIInventorySlotHelper::createInventorySlot(image2, { (WIDTH / 2) - 2000, 15 - 2000 }, InventoryItem::CRYPTOGUN);
		UIInventorySlotHelper::createInventorySlot(image3, { (WIDTH / 2) + 115 - 2000, 15 - 2000 }, InventoryItem::BRUTEFORCE);
		//UIInventorySlotHelper::createInventorySlot(image0, { (WIDTH / 3) + 460 - 2000, 15 - 2000 }, InventoryItem::HANDS);
		//UIInventorySlotHelper::createInventorySlot(image0, { (WIDTH / 3) + 575 - 2000, 15 - 2000 }, InventoryItem::HANDS);
	}

	void update(std::map<InventoryItem, bool> inventoryFromHandler, InventoryItem currentlyEquippedItem) {
		for (auto pair : inventoryFromHandler) {
			auto item = pair.first;
			auto unlocked = pair.second;

			for (auto i : UIInventorySlotHelper::list) {
				auto l_item = i.second->Item;
				
				if (item == l_item) {
					if (!unlocked) {
						((sf::Sprite*)(i.second->drawableList.at(1)))->setColor(sf::Color::Transparent);
					}
					else {
						((sf::Sprite*)(i.second->drawableList.at(1)))->setColor(sf::Color::White);
					}
				}

			}
		}

		for (auto pair : UIInventorySlotHelper::list) {
			auto slot = pair.second;

			if (slot->Item == currentlyEquippedItem) {
				slot->select();
			}
			else {
				slot->unselect();
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