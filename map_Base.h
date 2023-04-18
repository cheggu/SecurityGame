#pragma once
#include "Entity.h"
#include "Player.h"
#include "Platform.h"
#include "AIEntity.h"

#include "PhysicsSystem.h"
#include "CollisionHandler.h"

#include "Includes.h"

#include "ui_Element.h"
#include "ui_Health.h"
#include "ui_Button.h"
#include "ui_Toolbox.h"

#include "mini_Base.h"

#include "Font.h"

namespace Map {
	enum maps {
		LEVEL0,
		LEVEL1,
		LEVEL2,
		LEVEL3
	};

	//first level
	sf::RectangleShape floor00({ 2300, 10 });
	sf::RectangleShape floor01({ 5000, 10 });
	sf::RectangleShape floor02({ 10, 200 });
	sf::RectangleShape floor03({ 10, 200 });

	//second level



	sf::Texture texture;
	sf::Sprite mapSprite;
	
	bool load(maps map) {
		switch (map) {
		case LEVEL0:

			window.setView(view);

			if (!texture.loadFromFile("map01.png"))
			{
				std::cout << "shuit...." << std::endl;
			}
			else {
				std::cout << "hooplah...." << std::endl;
				mapSprite.setTexture(texture);
				mapSprite.setScale(4, 4);
				mapSprite.move(-325, -4934);


					// floor0
					
				floor00.setFillColor(sf::Color::Red);
				floor00.setPosition(0, HEIGHT - 158);
				std::cout << PlatformHelper::createPlatform(floor00) << std::endl;


					
				floor01.setFillColor(sf::Color::Red);
				floor01.setPosition(2580, HEIGHT - 158);
				std::cout << PlatformHelper::createPlatform(floor01) << std::endl;

					
				floor02.setFillColor(sf::Color::Red);
				floor02.setPosition(0, HEIGHT - 158 - 200);
				std::cout << PlatformHelper::createPlatform(floor02) << std::endl;

				floor03.setFillColor(sf::Color::Red);
				floor03.setPosition(7100, HEIGHT - 158 - 200);
				std::cout << PlatformHelper::createPlatform(floor03) << std::endl;






				}
			break;
		}
		return true;
	}
	
}