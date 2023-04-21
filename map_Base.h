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
#include "obj_Checkpoint.h"

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
	sf::RectangleShape floor00({ 3000, 10 });
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

	sf::RectangleShape floor30({ 3000, 10 });

	sf::RectangleShape floor31({ 10, 400 });

	sf::RectangleShape floor32({ 50,40 });
	sf::RectangleShape floor33({ 50,40 });
	sf::RectangleShape floor34({ 50,40 });
	sf::RectangleShape floor35({ 320,40 });

	sf::RectangleShape floor36({ 50, 2100 });
	sf::RectangleShape floor37({ 30, 3500 - 9});

	sf::RectangleShape floor38({ 900, 40 });

	sf::RectangleShape floor39({ 40,40 });
	sf::RectangleShape floor40({ 40,40 });
	sf::RectangleShape floor41({ 40,40 });
	sf::RectangleShape floor42({ 40,40 });

	sf::RectangleShape floor43({ 40,40 });
	sf::RectangleShape floor44({ 40,40 });
	sf::RectangleShape floor45({ 40,40 });
	sf::RectangleShape floor46({ 40,40 });

	sf::RectangleShape floor47({ 420, 10 });
	sf::RectangleShape floor48({ 30, 500 });
	sf::RectangleShape floor49({ 800, 20 });

	sf::RectangleShape floor50({ 20, 1000 });
	sf::RectangleShape floor51({ 60, 200 });
	sf::RectangleShape floor52({ 60, 200 });

	sf::RectangleShape floor53({ 10, 190 });
	sf::RectangleShape floor54({ 160, 160 });

	sf::RectangleShape floor55({ 10, 2560 });
	sf::RectangleShape floor56({ 20, 1400 });
	sf::RectangleShape floor57({ 40, 40 });
	sf::RectangleShape floor58({ 40, 40 });
	sf::RectangleShape floor59({ 40, 40 });
	sf::RectangleShape floor60({ 40, 40 });






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

	sf::RectangleShape platform28({ 1000, 10 });

	sf::RectangleShape platform29({ 100, 10 });
	sf::RectangleShape platform30({ 100, 10 });
	sf::RectangleShape platform31({ 100, 10 });
	sf::RectangleShape platform32({ 100, 10 });
	sf::RectangleShape platform33({ 100, 10 });
	sf::RectangleShape platform34({ 100, 10 });
	sf::RectangleShape platform35({ 100, 10 });
	

	sf::RectangleShape platform1337({ 1000, 10 });

	
	int gate_castle;
	int gate_boss_01_left;
	int gate_boss_01_right;
	int gate_boss_02_left;
	int gate_boss_02_right;
	int gate_boss_03_left;
	int gate_boss_03_right;


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
				//std::cout << PlatformHelper::createPlatform(floor02) << std::endl;

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

				floor30.setPosition(2100, -3270);
				PlatformHelper::createPlatform(floor30);

				floor31.setPosition(4763, -3430);
				PlatformHelper::createPlatform(floor31);

				//2054, -3302
				floor32.setPosition(2054, -3302);
				PlatformHelper::createPlatform(floor32);

				//2030, -3335
				floor33.setPosition(2030, -3335);
				PlatformHelper::createPlatform(floor33);
				
				//2000, -3367
				floor34.setPosition(2000, -3367);
				PlatformHelper::createPlatform(floor34);

				//1691, -3400
				floor35.setPosition(1691, -3400);
				PlatformHelper::createPlatform(floor35);

				floor36.setPosition(1659, -3367);
				PlatformHelper::createPlatform(floor36);

				floor37.setPosition(1020, -5000);
				PlatformHelper::createPlatform(floor37);

				floor38.setPosition(923, -1351);
				PlatformHelper::createPlatform(floor38);

				floor39.setPosition(892, -1317);
				PlatformHelper::createPlatform(floor39);

				floor40.setPosition(859, -1286);
				PlatformHelper::createPlatform(floor40);

				floor41.setPosition(826, -1255);
				PlatformHelper::createPlatform(floor41);

				floor42.setPosition(795, -1222);
				PlatformHelper::createPlatform(floor42);

				
				floor43.setPosition(764, -1190);
				PlatformHelper::createPlatform(floor43);

				floor44.setPosition(730, -1157);
				PlatformHelper::createPlatform(floor44);

				floor45.setPosition(697, -1124);
				PlatformHelper::createPlatform(floor45);

				floor46.setPosition(666, -1094);
				PlatformHelper::createPlatform(floor46);

				floor47.setPosition(252, -1063);
				PlatformHelper::createPlatform(floor47);

				floor48.setPosition(230, -1527);
				PlatformHelper::createPlatform(floor48);

				floor49.setPosition(230, -1527);
				PlatformHelper::createPlatform(floor49);

				floor50.setPosition(-87, -164);
				PlatformHelper::createPlatform(floor50);

				floor51.setPosition(-83, 666);
				PlatformHelper::createPlatform(floor51);

				floor52.setPosition(-54, 760);
				PlatformHelper::createPlatform(floor52);

				floor53.setPosition(1865, 602);
				PlatformHelper::createPlatform(floor53);

				floor54.setPosition(1777, 493);
				PlatformHelper::createPlatform(floor54);



				floor55.setPosition(5369, -3429);
				PlatformHelper::createPlatform(floor55);

				floor56.setPosition(4678, -5000);
				PlatformHelper::createPlatform(floor56);

				floor57.setPosition(4698, -3655);
				PlatformHelper::createPlatform(floor57);

				floor58.setPosition(4729, -3624);
				PlatformHelper::createPlatform(floor58);

				floor59.setPosition(4761, -3591);
				PlatformHelper::createPlatform(floor59);

				floor60.setPosition(4792, -3559);
				PlatformHelper::createPlatform(floor60);








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

				platform28.setPosition(1050, -3367);
				PlatformHelper::createDropdownPlatform(platform28);
				
				platform29.setPosition(1146, -1895);
				PlatformHelper::createDropdownPlatform(platform29);

				platform30.setPosition(1435, -2085);
				PlatformHelper::createDropdownPlatform(platform30);

				platform31.setPosition(1082, -2310);
				PlatformHelper::createDropdownPlatform(platform31);

				platform32.setPosition(1436, -2502);
				PlatformHelper::createDropdownPlatform(platform32);

				platform33.setPosition(1181, -2727);
				PlatformHelper::createDropdownPlatform(platform33);

				platform34.setPosition(1083, -3013);
				PlatformHelper::createDropdownPlatform(platform34);

				platform35.setPosition(1466, -3174);
				PlatformHelper::createDropdownPlatform(platform35);



				gate_boss_01_left = GateObjectHelper::createGate(48, { 3420, -2400 }, { 4,4 });
				gate_boss_01_right = GateObjectHelper::createGate(48, { 5040, -2400 }, { 4,4 });

				gate_boss_02_left = GateObjectHelper::createGate(10, { 2529, -3574 }, { 4,4 });
				gate_boss_02_right = GateObjectHelper::createGate(3, { 4800, -3526 }, { 4,4 });

				gate_boss_03_left = GateObjectHelper::createGate(4, { 1866, 794 }, { 4,4 });
				gate_boss_03_right = GateObjectHelper::createGate(10, { 4876, 600 }, { 4,4 });

				LadderObjectHelper::createLadder(80, { 5340, -3430 }, { 4,4 }, { 5275, -3500 });
				LadderObjectHelper::createLadder(10, { 283, -1119 }, { 4,4 }, { -54, 600 });

				CheckpointHelper::createCheckpoint(sf::FloatRect({ 853,875 }, { 64, 48 }));
				CheckpointHelper::createCheckpoint(sf::FloatRect({ 3446,-913 }, { 64, 48 }));
				CheckpointHelper::createCheckpoint(sf::FloatRect({ 5076, -3471 }, { 64, 48 }));
				CheckpointHelper::createCheckpoint(sf::FloatRect({ 1811, -3437 }, { 64, 48 }));
				CheckpointHelper::createCheckpoint(sf::FloatRect({ 2197, 887 }, { 64, 48 }));

				}
			break;
		}
		return true;
	}
	
}