#pragma once
#include "Includes.h"
#include "Player.h"
#include "SFML/Graphics.hpp"
#include "BossHandler.h"

namespace Camera {
	void update(float dt)
	{
		for (auto pair : PlayerHelper::list) {
			auto player = pair.second;
			sf::Vector2f target;
			if (player->position.y > 1000) {
				target = { player->position.x, HEIGHT / 2 };
			}
			else if (player->position.x > 2100 && player->position.x < 4756 && player->position.y > -3600 && player->position.y < -3240) {
				target = { player->position.x, (player->position.y - (HEIGHT / 5)) };
			}
			else if (player->position.x > 1050 && player->position.x < 1657 && player->position.y > -3723 && player->position.y < -1616) {
				target = { player->position.x, (player->position.y - (HEIGHT / 6)) };
				
			}
			else if (player->position.x > 3434 && player->position.x < 5055 && player->position.y > -1570 && player->position.y < -871) {
				target = { player->position.x, (player->position.y - (HEIGHT / 6)) };
				for (auto pair : InvisLayerHelper::list) {
					auto layer = pair.second;
					layer->disable();
				}
				BossEvent::BossFight_00();
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