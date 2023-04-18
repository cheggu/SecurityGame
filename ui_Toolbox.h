#pragma once
#include "ui_Element.h"
#include "ui_Button.h"
#include "SFML/Graphics.hpp"
#include "Includes.h"
#include "map_Reader.h"

#include "mini_Encryption.h"

class ToolboxUIElement : public uiElement {
public:

	sf::Vector2f backPos = { WIDTH - (WIDTH / 5) - 10, 10 };
	sf::Vector2f backSize = { WIDTH / 5, HEIGHT / 2 };

	sf::RectangleShape toolboxBackground;
	sf::Vector2f positionBackground = backPos;
	sf::Vector2f sizeBackground = backSize;

	int btn_expand_id;
	int btn_debug_id;

	bool expanded = true;
	bool mutex = false;

	ToolboxUIElement() {
		float intPad = 4.f, extPad = 10.0f;
		float sizex = 200, sizey = 15;


		//Button btn_expand = Button( { positionBackground.x + intPad, positionBackground.y + intPad } , SMALL, sf::Color(0xd44032aa), "Expand");
		btn_expand_id = UIButtonHelper::createButton({ positionBackground.x + sizeBackground.x - 50 - intPad, positionBackground.y + intPad }, TINY, sf::Color(0xd44032aa), "Resize");

		toolboxBackground.setPosition(positionBackground);
		toolboxBackground.setSize(sizeBackground);
		toolboxBackground.setFillColor(sf::Color(0xff8853aa));
		
		btn_debug_id = UIButtonHelper::createButton({ positionBackground.x + intPad, positionBackground.y + intPad }, TINY, sf::Color(0xd44032aa), "debug");


		drawableList[0] = &toolboxBackground;
		
		//drawableList[1] = &healthValue;
	}

	void update(sf::Vector2f mousePos) {
		auto btn_expand = UIButtonHelper::list.find(btn_expand_id);
		btn_expand->second->update(mousePos);

		if (btn_expand->second->isClicked() && !mutex) {
			if (expanded) {
				//de-expand
				std::cout << "deexpand" << std::endl;
				expanded = false;
				sizeBackground = { backSize.x, 40 };
			}
			else if (!expanded) {
				//expand
				std::cout << "expand" << std::endl;
				expanded = true;
				sizeBackground = backSize;
				
			}
			toolboxBackground.setSize(sizeBackground);
			mutex = true;
		}
		else {
			//std::cout << "mutex, cant expand" << std::endl;
		}

		//auto btn_debug = UIButtonHelper::list[btn_debug_id];
		auto btn_debug = UIButtonHelper::list[btn_debug_id];
		btn_debug->update(mousePos);
		//std::cout << "btn id " << btn_debug->second->id << std::endl;
		if (btn_debug->isClicked() && !mutex) {
			
			//start debug minigame
			std::cout << "debug" << std::endl;
			Minigames::InitializeMinigames();
			Minigames::printAllMinigameStatuses();
			
			MapReader::read();

			
			
			mutex = true;
		}
		else {
			//std::cout << "mutex, cant expand" << std::endl;
			
		}

	}

};

namespace UIToolboxHelper {
	std::map<int, ToolboxUIElement*> list;

	int createToolbox() {
		auto tempEnt = new ToolboxUIElement();

		list[0] = tempEnt;
		UIElementHelper::list[tempEnt->id] = tempEnt;

		return tempEnt->id;
	}
}