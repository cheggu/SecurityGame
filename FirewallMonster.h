#pragma once
#include "Entity.h"


class FirewallMonster : public Entity {

private:
	sf::Text healthText;
	bool attacking;
	bool targeting;

	sf::RectangleShape shape;
	sf::Sprite sprite;
	sf::Texture texture00, texture01, texture02, texture03, texture04;
	sf::Texture texture00_f, texture01_f, texture02_f, texture03_f;

	sf::Texture texture00_g, texture01_g, texture02_g, texture03_g;
	sf::Texture texture00_g_f, texture01_g_f, texture02_g_f, texture03_g_f;

	direction side;
	float currentSweepYLevel;

	sf::Clock sweepClock;
	sf::Clock targetClock;

	bool dead = true;


public:
	float maxHealth = 1000.f;

	std::map<int, sf::Drawable*> drawableList = {};

	FirewallMonster() {
		boss01id = id;
		health = 1000;
		texture00.loadFromFile("Content/Sprites/Icons/FirewallBoss/orig/firewall_00.png");
		texture01.loadFromFile("Content/Sprites/Icons/FirewallBoss/orig/firewall_01.png");
		texture02.loadFromFile("Content/Sprites/Icons/FirewallBoss/orig/firewall_02.png");
		texture03.loadFromFile("Content/Sprites/Icons/FirewallBoss/orig/firewall_03.png");

		texture00_f.loadFromFile("Content/Sprites/Icons/FirewallBoss/flipped/firewall_00_flipped.png");
		texture01_f.loadFromFile("Content/Sprites/Icons/FirewallBoss/flipped/firewall_01_flipped.png");
		texture02_f.loadFromFile("Content/Sprites/Icons/FirewallBoss/flipped/firewall_02_flipped.png");
		texture03_f.loadFromFile("Content/Sprites/Icons/FirewallBoss/flipped/firewall_03_flipped.png");

		texture00_g.loadFromFile("Content/Sprites/Icons/FirewallBoss/orig/firewall_00_glow.png");
		texture01_g.loadFromFile("Content/Sprites/Icons/FirewallBoss/orig/firewall_01_glow.png");
		texture02_g.loadFromFile("Content/Sprites/Icons/FirewallBoss/orig/firewall_02_glow.png");
		texture03_g.loadFromFile("Content/Sprites/Icons/FirewallBoss/orig/firewall_03_glow.png");

		texture00_g_f.loadFromFile("Content/Sprites/Icons/FirewallBoss/flipped/firewall_00_glow_flipped.png");
		texture01_g_f.loadFromFile("Content/Sprites/Icons/FirewallBoss/flipped/firewall_01_glow_flipped.png");
		texture02_g_f.loadFromFile("Content/Sprites/Icons/FirewallBoss/flipped/firewall_02_glow_flipped.png");
		texture03_g_f.loadFromFile("Content/Sprites/Icons/FirewallBoss/flipped/firewall_03_glow_flipped.png");


		texture04.loadFromFile("Content/Sprites/Icons/FirewallBoss/firewall_04.png");

		sprite.setTexture(texture00);
		sprite.setScale(2,2);

		acceleration = { 0,0 };
		position = { 3434, -1570 };

		updateShape();

		side = LEFT;

		drawableList[0] = &sprite;
		
		shape.setPosition(sprite.getPosition());
		shape.setSize({ sprite.getGlobalBounds().width, sprite.getGlobalBounds().height });
		drawable = &shape;

		targetClock.restart();
		sweepClock.restart();
	}

	void updateShape() {
		//sprite.setPosition(position);
		healthText.setString(std::to_string((int)health) + " HP");
		healthText.setPosition(position.x, position.y - 20);
		shape.setPosition(sprite.getPosition());
		shape.setSize({ sprite.getGlobalBounds().width, sprite.getGlobalBounds().height });
	}

	void setPos(sf::Vector2f newPos) {
		position = newPos;
	}

	void setVel(sf::Vector2f v) {
		velocity = v;
	}

	bool isDead() {
		return dead;
	}

	void awaken() {
		dead = false;
	}

	void sweepRight() {
		sf::Vector2f playerLoc;
		if (targeting) {
			for (auto pair : PlayerHelper::list) {
				auto p = pair.second;

				playerLoc = p->position;
			}
		}
		else {
			for (auto pair : PlayerHelper::list) {
				auto p = pair.second;

				playerLoc = { playerLoc.x, p->position.y };

			}
		}
		targeting = false;

		if (abs((int)position.x - (int)window.mapPixelToCoords({ (int)WIDTH - 200, 0 }).x) > 100) {
			auto pixelpos = window.mapPixelToCoords({ (int)WIDTH - 200, 0 });
			pixelpos.y = playerLoc.y - (sprite.getGlobalBounds().height / 2);
			sf::Vector2f movement = (pixelpos - position);
			sprite.move(movement * (physics::dt * .1f));
			position = sprite.getPosition();
		}
		else {
			side = RIGHT;
			bossside00 = RIGHT;
			targetClock.restart();
		}

	}

	void sweepLeft() {
		sf::Vector2f playerLoc;
		if (targeting) {
			for (auto pair : PlayerHelper::list) {
				auto p = pair.second;

				playerLoc = p->position;
			}
		}
		else {
			for (auto pair : PlayerHelper::list) {
				auto p = pair.second;

				playerLoc = { playerLoc.x, p->position.y };

			}
		}
		targeting = false;

		if (abs((int)position.x - (int)window.mapPixelToCoords({ 200, 0 }).x) > 100) {
			auto pixelpos = window.mapPixelToCoords({ 200, 0 });
			pixelpos.y = playerLoc.y - (sprite.getGlobalBounds().height / 2);
			sf::Vector2f movement = (pixelpos - position);
			sprite.move(movement * (physics::dt * .1f));
			position = sprite.getPosition();
		}
		else {
			side = LEFT;
			bossside00 = LEFT;
			targetClock.restart();
		}
	}

	void target() {
		attacking = false;
		targeting = true;

		sf::Vector2f playerLoc;

		for (auto pair : PlayerHelper::list) {
			auto p = pair.second;

			playerLoc = p->position;
		}

		if (side == LEFT) {
			auto pixelpos = window.mapPixelToCoords({ 200, 0 });
			pixelpos.y = playerLoc.y - (sprite.getGlobalBounds().height / 2);
			sf::Vector2f movement = (pixelpos - position);
			sprite.move(movement * (physics::dt * .2f));
			position = sprite.getPosition();
		}
		else {
			auto pixelpos = window.mapPixelToCoords({ (int)WIDTH - 200, 0 });
			pixelpos.y = playerLoc.y - (sprite.getGlobalBounds().height / 2);
			sf::Vector2f movement = (pixelpos - position);
			sprite.move(movement * (physics::dt * .2f));
			position = sprite.getPosition();
		}
		playFirewallAttack();
	}

	void nextMove() {
		if (health > 0) {
			if (targetClock.getElapsedTime().asSeconds() > 10) {
				
				if (side == LEFT) {
					sweepRight();
				}
				else {
					sweepLeft();
				}

			}
			else {
				if (side == LEFT) {
					shape.setScale(-1, -1);
				}
				else {
					shape.setScale(1, 1);
				}
				target();
			}

			for (auto pair : PlayerHelper::list) {
				auto player = pair.second;

				if (player->hurtCooldown.getElapsedTime().asMilliseconds() > 250) {

					physics::AABB playerbox = { player->position, player->position + player->drawable->getSize() };
					physics::AABB bossbox = { position, position + drawable->getSize() };

					if (physics::AABBvsAABB(playerbox, bossbox)) {
						player->hurt(10);
					}
					player->hurtCooldown.restart();
				}

			}

			
		}
		else {
			
			auto pixelpos = window.mapPixelToCoords({ (int)WIDTH / 2, (int)HEIGHT + 500 });
			sf::Vector2f movement = (pixelpos - position);
			sprite.move(movement * (physics::dt * .05f));
			position = sprite.getPosition();
			if (abs(position.y - pixelpos.y) < 300) {
				die();
			}
		}
		
		if (!dead) {
			updateShape();
			animate();
		}
		
	}

	void die() {
		if (!dead) {
			playFirewallDeath();
		}
		dead = true;
	}

	void animate() {
		bool glow;
		for (auto pair : PlayerHelper::list) {
			auto player = pair.second;

			glow = player->doImpulse;

		}
		
		if (health <= 1000 && health > 750) {
			if (side == LEFT && !glow) {
				sprite.setTexture(texture00);
			}
			else if (side == RIGHT && !glow) {
				sprite.setTexture(texture00_f);
			}
			else if (side == LEFT && glow) {
				
				sprite.setTexture(texture00_g);
			}
			else if (side == RIGHT && glow) {

				sprite.setTexture(texture00_g_f);
			}	
		}
		else if (health <= 750 && health > 500) {
			if (side == LEFT && !glow) {
				sprite.setTexture(texture01);
			}
			else if (side == RIGHT && !glow) {
				sprite.setTexture(texture01_f);
			}
			else if (side == LEFT && glow) {

				sprite.setTexture(texture01_g);
			}
			else if (side == RIGHT && glow) {

				sprite.setTexture(texture01_g_f);
			}
		}
		else if (health <= 500 && health > 250) {
			if (side == LEFT && !glow) {
				sprite.setTexture(texture02);
			}
			else if (side == RIGHT && !glow) {
				sprite.setTexture(texture02_f);
			}
			else if (side == LEFT && glow) {

				sprite.setTexture(texture02_g);
			}
			else if (side == RIGHT && glow) {

				sprite.setTexture(texture02_g_f);
			}
		}
		else if (health <= 250 && health > 0) {
			if (side == LEFT && !glow) {
				sprite.setTexture(texture03);
			}
			else if (side == RIGHT && !glow) {
				sprite.setTexture(texture03_f);
			}
			else if (side == LEFT && glow) {

				sprite.setTexture(texture03_g);
			}
			else if (side == RIGHT && glow) {

				sprite.setTexture(texture03_g_f);
			}
		}
		else {
			sprite.setTexture(texture04);
		}

	}
};