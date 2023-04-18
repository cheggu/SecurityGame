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
	sf::RectangleShape floor04({ 300, 10});

	sf::RectangleShape floor05({ 32, 10 });
	sf::RectangleShape floor06({ 10, 24 });

	sf::RectangleShape floor07({ 10, 32 });
	sf::RectangleShape floor08({ 32, 10 });

	sf::RectangleShape floor09({ 32, 10 });
	sf::RectangleShape floor10({ 10, 32 });

	sf::RectangleShape floor11({ 10, 32 });
	sf::RectangleShape floor12({ 32, 10 });

	sf::RectangleShape floor13({ 10, 32 });
	sf::RectangleShape floor14({ 32, 10 });

	sf::RectangleShape floor15({ 10, 32 });
	sf::RectangleShape floor16({ 32, 10 });

	sf::RectangleShape floor17({ 10, 32 });
	sf::RectangleShape floor18({ 680, 10 });

	//platforms 1
	sf::RectangleShape platform01({ 250, 10 });
	sf::RectangleShape platform02({ 250, 10 });

	



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
					
				floor00.setPosition(0, HEIGHT - 158);
				std::cout << PlatformHelper::createPlatform(floor00) << std::endl;
;
				floor01.setPosition(2580, HEIGHT - 158);
				std::cout << PlatformHelper::createPlatform(floor01) << std::endl;

				floor02.setPosition(0, HEIGHT - 158 - 200);
				std::cout << PlatformHelper::createPlatform(floor02) << std::endl;

				floor03.setPosition(7100, HEIGHT - 158 - 200);
				std::cout << PlatformHelper::createPlatform(floor03) << std::endl;

				//STAIRS
				floor04.setPosition(1775, 490);
				std::cout << PlatformHelper::createPlatform(floor04) << std::endl;

				floor05.setPosition(2075, 474);
				std::cout << PlatformHelper::createPlatform(floor05) << std::endl;

				floor06.setPosition(2075, 474);
				std::cout << PlatformHelper::createPlatform(floor06) << std::endl;

				floor07.setPosition(2100, 441);
				std::cout << PlatformHelper::createPlatform(floor07) << std::endl;

				floor08.setPosition(2100, 441);
				std::cout << PlatformHelper::createPlatform(floor08) << std::endl;

				floor09.setPosition(2130, 408);
				std::cout << PlatformHelper::createPlatform(floor09) << std::endl;

				floor10.setPosition(2130, 408);
				std::cout << PlatformHelper::createPlatform(floor10) << std::endl;

				floor11.setPosition(2160, 375);
				std::cout << PlatformHelper::createPlatform(floor11) << std::endl;

				floor12.setPosition(2160, 375);
				std::cout << PlatformHelper::createPlatform(floor12) << std::endl;

				floor13.setPosition(2190, 342);
				std::cout << PlatformHelper::createPlatform(floor13) << std::endl;

				floor14.setPosition(2190, 342);
				std::cout << PlatformHelper::createPlatform(floor14) << std::endl;

				floor15.setPosition(2220, 309);
				std::cout << PlatformHelper::createPlatform(floor15) << std::endl;

				floor16.setPosition(2220, 309);
				std::cout << PlatformHelper::createPlatform(floor16) << std::endl;

				floor17.setPosition(2250, 276);
				std::cout << PlatformHelper::createPlatform(floor17) << std::endl;

				floor18.setPosition(2250, 266);
				std::cout << PlatformHelper::createPlatform(floor18) << std::endl;


				//2010, 185
				platform01.setPosition(2010, 185);
				PlatformHelper::createDropdownPlatform(platform01);


				platform02.setPosition(2140, 90);
				PlatformHelper::createDropdownPlatform(platform02);

				}
			break;
		}
		return true;
	}
	
}