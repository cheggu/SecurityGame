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

#include "obj_Gate.h"

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
	sf::RectangleShape floor18({ 289, 10 });

	sf::RectangleShape floor19({ 10, 237 }); //2521 25
	sf::RectangleShape floor20({ 433, 10 }); //433 

	sf::RectangleShape floor21({ 10, 254 }); 
	sf::RectangleShape floor22({ 850, 10 }); 

	sf::RectangleShape floor23({ 10, 100 }); //2521 25
	sf::RectangleShape floor24({ 3000, 10 }); //433 

	sf::RectangleShape floor25({ 3000, 10 }); //433 


	sf::RectangleShape floor26({ 10, 2000 });

	sf::RectangleShape floor27({ 4000, 10 }); //574

	sf::RectangleShape floor28({ 20, 1345 });

	sf::RectangleShape floor29({ 10, 572 });

	//platforms 1
	sf::RectangleShape platform01({ 250, 10 });
	sf::RectangleShape platform02({ 280, 10 });
	sf::RectangleShape platform03({ 250, 10 });
	sf::RectangleShape platform04({ 250, 10 });
	sf::RectangleShape platform05({ 280, 10 });
	sf::RectangleShape platform06({ 310, 10 });
	sf::RectangleShape platform07({ 250, 10 });

	sf::RectangleShape platform08({ 270, 10 });
	sf::RectangleShape platform09({ 220, 10 });
	sf::RectangleShape platform10({ 270, 10 });
	sf::RectangleShape platform11({ 400, 10 });
	sf::RectangleShape platform12({ 270, 10 });
	sf::RectangleShape platform13({ 270, 10 });
	sf::RectangleShape platform14({ 360, 10 });
	sf::RectangleShape platform15({ 300, 10 });
	sf::RectangleShape platform16({ 360, 10 });
	sf::RectangleShape platform17({ 300, 10 });
	sf::RectangleShape platform18({ 200, 10 });

	sf::RectangleShape platform19({ 260, 10 });
	sf::RectangleShape platform20({ 260, 10 });
	sf::RectangleShape platform21({ 260, 10 });
	sf::RectangleShape platform22({ 260, 10 });
	sf::RectangleShape platform23({ 290, 10 });
	sf::RectangleShape platform24({ 290, 10 });
	sf::RectangleShape platform25({ 290, 10 });
	sf::RectangleShape platform26({ 384, 10 });
	sf::RectangleShape platform27({ 384, 10 });

	
	

	sf::RectangleShape platform1337({ 1000, 10 });

	
	int gate_boss_01_left;
	int gate_boss_01_right;


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

				floor19.setPosition(2521, 25);
				PlatformHelper::createPlatform(floor19);

				floor20.setPosition(2521, 25);
				PlatformHelper::createPlatform(floor20);

				//2936, -229
				floor21.setPosition(2936, -229);
				PlatformHelper::createPlatform(floor21);

				floor22.setPosition(2936, -229);
				PlatformHelper::createPlatform(floor22);

				//3768, -328
				floor23.setPosition(3768, -328);
				PlatformHelper::createPlatform(floor23);

				floor24.setPosition(3768, -328);
				PlatformHelper::createPlatform(floor24);


				floor25.setPosition(3417, -872);
				PlatformHelper::createPlatform(floor25);

				floor26.setPosition(8375, -5000);
				PlatformHelper::createPlatform(floor26);

				floor27.setPosition(4764, -3430);
				PlatformHelper::createPlatform(floor27);

				floor28.setPosition(6440, -5000);
				PlatformHelper::createPlatform(floor28);

				floor29.setPosition(5733, -872);
				PlatformHelper::createPlatform(floor29);



				//2010, 185
				platform01.setPosition(2010, 185);
				PlatformHelper::createDropdownPlatform(platform01);


				platform02.setPosition(2140, 90);
				PlatformHelper::createDropdownPlatform(platform02);

				//2363 -37
				platform03.setPosition(2363, -37);
				PlatformHelper::createDropdownPlatform(platform03);

				//2426 -135
				platform04.setPosition(2426, -135);
				PlatformHelper::createDropdownPlatform(platform04);

				//2619 -233
				platform05.setPosition(2619, -233);
				PlatformHelper::createDropdownPlatform(platform05);
				 
				//2939 -327
				platform06.setPosition(2939, -327);
				PlatformHelper::createDropdownPlatform(platform06);

				//3450, -360
				platform07.setPosition(3450, -360);
				PlatformHelper::createDropdownPlatform(platform07);

				//3834, -424
				platform08.setPosition(3834, -424);
				PlatformHelper::createDropdownPlatform(platform08);


				//4217, -455
				platform09.setPosition(4217, -455);
				PlatformHelper::createDropdownPlatform(platform09);

				//4539, -456
				platform10.setPosition(4539, -456);
				PlatformHelper::createDropdownPlatform(platform10);

				//4952, -456
				platform11.setPosition(4952, -456);
				PlatformHelper::createDropdownPlatform(platform11);

				//5305, -550
				platform12.setPosition(5305, -550);
				PlatformHelper::createDropdownPlatform(platform12);

				//4922, -614
				platform13.setPosition(4922, -614);
				PlatformHelper::createDropdownPlatform(platform13);

				//4412, -679
				platform14.setPosition(4412, -679);
				PlatformHelper::createDropdownPlatform(platform14);

				//3963, -680
				platform15.setPosition(3963, -680);
				PlatformHelper::createDropdownPlatform(platform15);

				//3451, -680
				platform16.setPosition(3451, -680);
				PlatformHelper::createDropdownPlatform(platform16);

				//3067, -775
				platform17.setPosition(3067, -775);
				PlatformHelper::createDropdownPlatform(platform17);

				//3227, -872
				platform18.setPosition(3227, -872);
				PlatformHelper::createDropdownPlatform(platform18);

				//3609, -970
				platform19.setPosition(3609, -970);
				PlatformHelper::createDropdownPlatform(platform19);

				//3963, -970
				platform20.setPosition(3962, -970);
				PlatformHelper::createDropdownPlatform(platform20);

				//4317, -970
				platform21.setPosition(4315, -970);
				PlatformHelper::createDropdownPlatform(platform21);

				//4671, -970
				platform22.setPosition(4667, -970);
				PlatformHelper::createDropdownPlatform(platform22);

				//354

				//3770, -1063
				platform23.setPosition(3770, -1063);
				PlatformHelper::createDropdownPlatform(platform23);

				//4122, -1063
				platform24.setPosition(4122, -1063);
				PlatformHelper::createDropdownPlatform(platform24);

				//4474, -1063
				platform25.setPosition(4474, -1063);
				PlatformHelper::createDropdownPlatform(platform25);


				//3833, -1191
				platform26.setPosition(3833, -1191);
				PlatformHelper::createDropdownPlatform(platform26);

				//4315, -1191
				platform27.setPosition(4315, -1191);
				PlatformHelper::createDropdownPlatform(platform27);


				




				gate_boss_01_left = GateObjectHelper::createGate(48, { 3420, -2400 }, { 4,4 });
				gate_boss_01_right = GateObjectHelper::createGate(48, { 5040, -2400 }, { 4,4 });

				LadderObjectHelper::createLadder(80, { 5340, -3430 }, { 4,4 }, { 5275, -3500 });

				}
			break;
		}
		return true;
	}
	
}