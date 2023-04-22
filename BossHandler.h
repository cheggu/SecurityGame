#pragma once
#include "FirewallMonster.h"
#include "map_Base.h"




namespace BossEvent {
	FirewallMonster boss01 = FirewallMonster();




	sf::RectangleShape healthbar_inner;
	sf::RectangleShape healthbar_outer;
	sf::Text boss_name;
	float padding = 5.f;
	float healthValue = 1.f;
	bool inBattle = false;

	bool drawBossHealthbar = false;

	void initHealthbar(std::string name, float max_health) {
		healthbar_inner.setFillColor(sf::Color::Red);
		healthbar_outer.setFillColor(sf::Color(0xffa3a3a3));

		healthbar_inner.setSize({ 300, 25 });
		healthbar_outer.setSize({ 300.f + (padding * 2), 25 + (padding * 2)});

		

		healthbar_inner.setPosition(window.mapPixelToCoords({ (int)WIDTH / 2 - (int)(healthbar_inner.getGlobalBounds().width / 2) - 10, 130 + (int)padding }));
		healthbar_outer.setPosition(window.mapPixelToCoords({ (int)WIDTH / 2 - (int)(healthbar_outer.getGlobalBounds().width / 2) - 10, 130 }));

		boss_name.setFont(Font::emulogic);
		boss_name.setFillColor(sf::Color::Red);
		boss_name.setString(name);
		boss_name.setCharacterSize(16);

		boss_name.setPosition(healthbar_outer.getPosition().x, healthbar_outer.getPosition().y + healthbar_outer.getGlobalBounds().height + padding );
	}

	void setHealthbarValue(float originalHealth, float value) {
		healthbar_inner.setSize({ 300.f * (value / originalHealth), 25 });
		//std::cout << healthbar_inner.getSize().x << std::endl;
	}

	void updateHealthbar() {
		healthbar_inner.setPosition(window.mapPixelToCoords({ (int)WIDTH / 2 - (int)(healthbar_inner.getGlobalBounds().width / 2) - 10, 130 + (int)padding }));
		healthbar_outer.setPosition(window.mapPixelToCoords({ (int)WIDTH / 2 - (int)(healthbar_outer.getGlobalBounds().width / 2) - 10, 130 }));
		boss_name.setPosition(healthbar_outer.getPosition().x, healthbar_outer.getPosition().y + healthbar_outer.getGlobalBounds().height + padding);

		setHealthbarValue(boss01.maxHealth, boss01.health);
	}

	void hideHealthbar() {
		healthbar_inner.setFillColor(sf::Color::Transparent);
		healthbar_outer.setFillColor(sf::Color::Transparent);
		boss_name.setFillColor(sf::Color::Transparent);
	}

	void showHealthbar() {
		healthbar_inner.setFillColor(sf::Color::Red);
		healthbar_outer.setFillColor(sf::Color(0xffa3a3a3));
		boss_name.setFillColor(sf::Color::Red);
	}

	void BossFight_00() {
		boss01.awaken();
		EntityHelper::list[boss01.id] = &boss01;
		drawBossHealthbar = true;
		boss01.nextMove();

		updateHealthbar();

		if (boss01.health < 0) {
			GateObjectHelper::list.at(Map::gate_boss_01_left)->disable();
			GateObjectHelper::list.at(Map::gate_boss_01_right)->disable();
			
			EntityHelper::list.erase(boss01.id);
			

			drawBossHealthbar = false;
			inBattle = false;
		}
		else {
			if (!inBattle) {
				initHealthbar(" Glog, the Firewall", boss01.maxHealth);
			}
			inBattle = true;
			

			GateObjectHelper::list.at(Map::gate_boss_01_left)->enable();
			GateObjectHelper::list.at(Map::gate_boss_01_right)->enable();
			GateObjectHelper::list.at(Map::gate_boss_01_left)->disableBullets();
			GateObjectHelper::list.at(Map::gate_boss_01_right)->disableBullets();
		}


	}


}

