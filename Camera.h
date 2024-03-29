#pragma once
#include "Includes.h"
#include "Player.h"
#include "SFML/Graphics.hpp"
#include "BossHandler.h"

namespace Camera {
	bool created_hacker = false;

	void update(float dt)
	{
		for (auto pair : PlayerHelper::list) {
			auto player = pair.second;
			sf::Vector2f target;
			if (player->position.y > 1000) {																									//falling
				target = { player->position.x, HEIGHT / 2 };
			}
			else if (player->position.x > 3434 && player->position.x < 5055 && player->position.y > -1570 && player->position.y < -871) {		//boss 1
				target = { player->position.x, (player->position.y - (HEIGHT / 6)) };
				for (auto pair : InvisLayerHelper::list) {
					auto layer = pair.second;
					layer->disable();
				}
				BossEvent::BossFight_01();

			}
			else if (player->position.x > 2100 && player->position.x < 4756 && player->position.y > -3600 && player->position.y < -3240) {		//boss 2
				target = { player->position.x, (player->position.y - (HEIGHT / 5)) };
				if (player->position.x < 3946) { 
					BossEvent::BossFight_02();
				}
			}
			else if (player->position.x > 1050 && player->position.x < 1657 && player->position.y > -3723 && player->position.y < -1616) {		//waterfall
				target = { player->position.x, (player->position.y - (HEIGHT / 6)) };
			}
			else if (player->position.x > 4897 && player->position.x < 7101 && player->position.y > 607 && player->position.y < 923) {			//boss 3
				target = { player->position.x, player->position.y - (HEIGHT / 3) };
				if (!created_hacker) {
					CharacterHelper::createCharacter(BossEvent::boss03.position, BossEvent::boss03.getSprite(), hacker);
					created_hacker = true;
				}
				if (spawnFinalBoss) {
					BossEvent::BossFight_03();
				}
			}

			
			//else if (player->position.x > 4889 && player->position.x < 7104 && player->position.y > 606 && player->position.y < 921) {
			//}
			else {
				target = { player->position.x, player->position.y - (HEIGHT / 3) };
			}


			sf::Vector2f movement = (target - view.getCenter());
			//std::cout << view.getCenter().x << " " << view.getCenter().y << std::endl;
			view.move(movement * dt);
			window.setView(view);
		}
	}	
}