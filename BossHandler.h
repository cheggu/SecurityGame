#pragma once
#include "FirewallMonster.h"
#include "BrainMonster.h"
#include "FinalMonster.h"
#include "map_Base.h"

namespace BossEvent {
	FirewallMonster boss01 = FirewallMonster();
	bool boss01beaten = false;

	BrainMonster boss02 = BrainMonster();
	bool boss02beaten = false;

	FinalMonster boss03 = FinalMonster();
	bool boss03beaten = false;

	sf::RectangleShape healthbar_inner;
	sf::RectangleShape healthbar_outer;
	sf::Text boss_name;
	float padding = 5.f;
	float healthValue = 1.f;
	bool inBattle = false;

	bool ihatemutexlocks = false;

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

	void updateHealthbar(float health) {
		healthbar_inner.setPosition(window.mapPixelToCoords({ (int)WIDTH / 2 - (int)(healthbar_inner.getGlobalBounds().width / 2) - 10, 130 + (int)padding }));
		healthbar_outer.setPosition(window.mapPixelToCoords({ (int)WIDTH / 2 - (int)(healthbar_outer.getGlobalBounds().width / 2) - 10, 130 }));
		boss_name.setPosition(healthbar_outer.getPosition().x, healthbar_outer.getPosition().y + healthbar_outer.getGlobalBounds().height + padding);

		setHealthbarValue(1000.f, health);
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

	void BossFight_01() {
		boss01.awaken();
		EntityHelper::list[boss01.id] = &boss01;
		drawBossHealthbar = true;
		boss01.nextMove();

		updateHealthbar(boss01.health);

		if (boss01.health < 0) {
			GateObjectHelper::list.at(Map::gate_boss_01_left)->disable();
			GateObjectHelper::list.at(Map::gate_boss_01_right)->disable();
			
			EntityHelper::list.erase(boss01.id);
			Audio::sound_boss_default.stop();

			drawBossHealthbar = false;
			inBattle = false;
			boss01beaten = true;
			
		}
		else {
			if (!inBattle) {
				initHealthbar(" Glog, the Firewall", boss01.maxHealth);
				Audio::sound_boss_default.play();
			}
			inBattle = true;
			Audio::sound_grungy.stop();
			GateObjectHelper::list.at(Map::gate_boss_01_left)->enable();
			GateObjectHelper::list.at(Map::gate_boss_01_right)->enable();
			GateObjectHelper::list.at(Map::gate_boss_01_left)->disableBullets();
			GateObjectHelper::list.at(Map::gate_boss_01_right)->disableBullets();
		}
	}

	void BossFight_02() {
		boss02.awaken();
		EntityHelper::list[boss02.id] = &boss02;
		drawBossHealthbar = true;
		boss02.nextMove();

		updateHealthbar(boss02.health);

		if (boss02.health < 0 && boss02.isDead()) {
			//EntityHelper::list.erase(boss02.id);

			drawBossHealthbar = false;
			inBattle = false;
			boss02beaten = true;
			Audio::sound_boss_default.stop();

			GateObjectHelper::list.at(Map::gate_boss_02_left)->disable();
			GateObjectHelper::list.at(Map::gate_boss_02_rightright)->disable();

			GateObjectHelper::list.at(Map::gate_boss_03_left)->disable();
			GateObjectHelper::list.at(Map::gate_boss_03_right)->disable();
			//GateObjectHelper::list.at(Map::gate_castle)->disable();
		}
		else {
			if (!inBattle) {
				initHealthbar(" The Big Brain", boss02.maxHealth);
				Audio::sound_boss_default.play();
			}
			inBattle = true;
			Audio::sound_grungy.stop();

			GateObjectHelper::list.at(Map::gate_boss_02_left)->enable();
			GateObjectHelper::list.at(Map::gate_boss_02_rightright)->enable();
			
			GateObjectHelper::list.at(Map::gate_boss_02_left)->disableBullets();
			GateObjectHelper::list.at(Map::gate_boss_02_rightright)->disableBullets();
		}
	}

	void BossFight_03() {
		boss03.awaken();
		EntityHelper::list[boss03.id] = &boss03;
		drawBossHealthbar = true;
		boss03.nextMove();

		updateHealthbar(boss03.health);

		if (boss03.health < 0 && boss03.isDead()) {
			//EntityHelper::list.erase(boss02.id);

			drawBossHealthbar = false;
			inBattle = false;
			boss02beaten = true;
			Audio::sound_boss_default.stop();

			GateObjectHelper::list.at(Map::gate_boss_03_right)->disable();

			drawCredits = true;
		}
		else {
			if (!inBattle) {
				initHealthbar("sudo", boss03.maxHealth);
				Audio::sound_boss_default.play();
			}
			inBattle = true;
			Audio::sound_grungy.stop();
			GateObjectHelper::list.at(Map::gate_boss_03_right)->enable();
			GateObjectHelper::list.at(Map::gate_boss_03_right)->disableBullets();
		}
	}


}

