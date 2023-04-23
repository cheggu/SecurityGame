#pragma once
#include "Entity.h"
#include "Includes.h"
#include "Bullet.h"

class BrainMonster : public Entity {

private:
	sf::Text healthText;
	bool attacking;
	bool targeting;
	bool distracted;
	float cos_counter;

	sf::Vector2f distractionPoint;
	sf::Clock distractionClock;
	sf::Clock attackClock;

	direction side;

	sf::RectangleShape shape;
	sf::Sprite sprite;
	sf::Texture texture01, texture02, texture03, texture04;
	sf::Texture texture01_l, texture02_l, texture03_l;
	sf::Texture texture01_r, texture02_r, texture03_r;

	bool dead = true;
	bool mutex = false;

public:
	float maxHealth = 1000.f;

	std::map<int, sf::Drawable*> drawableList = {};

	BrainMonster() {
		boss02id = id;
		health = 1000;
		texture01.loadFromFile("Content/Sprites/Icons/BrainBoss/brain_01.png");
		texture02.loadFromFile("Content/Sprites/Icons/BrainBoss/brain_02.png");
		texture03.loadFromFile("Content/Sprites/Icons/BrainBoss/brain_03.png");

		texture01_l.loadFromFile("Content/Sprites/Icons/BrainBoss/brain_01_l.png");
		texture02_l.loadFromFile("Content/Sprites/Icons/BrainBoss/brain_02_l.png");
		texture03_l.loadFromFile("Content/Sprites/Icons/BrainBoss/brain_03_l.png");

		texture01_r.loadFromFile("Content/Sprites/Icons/BrainBoss/brain_01_r.png");
		texture02_r.loadFromFile("Content/Sprites/Icons/BrainBoss/brain_02_r.png");
		texture03_r.loadFromFile("Content/Sprites/Icons/BrainBoss/brain_03_r.png");

		texture04.loadFromFile("Content/Sprites/Icons/BrainBoss/brain_04.png");

		sprite.setTexture(texture01);
		sprite.setScale(2, 2);

		acceleration = { 0,0 };
		position = { 3210, -5000 }; //-5000

		updateShape();

		drawableList[0] = &sprite;

		std::cout << sprite.getGlobalBounds().left << " " << sprite.getGlobalBounds().top << " " << sprite.getGlobalBounds().width << " " << sprite.getGlobalBounds().height;

		shape.setPosition(sprite.getPosition());
		shape.setSize({ sprite.getGlobalBounds().width, sprite.getGlobalBounds().height });
		drawable = &shape;
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

	void hurtPlayer(float amount) {
		for (auto pair : PlayerHelper::list) {
			auto player = pair.second;
			if (player->hurtCooldown.getElapsedTime().asMilliseconds() > 100) {
				std::cout << "hurt" << std::endl;
				player->hurt(amount);
				player->hurtCooldown.restart();
				
			}
		}
	}

	void startDistraction() {

		if (distractionClock.getElapsedTime().asSeconds() > 5) {
			distracted = false;
		}
		std::cout << "distracted" << std::endl;
	}


	void nextMove() {
		if (health > 0) {

			if (!distracted) {
				for (auto pair : BulletHelper::list) {
					auto bullet = pair.second;
					if (bullet->doPersist) {
						distractionPoint = bullet->position;
						distracted = true;
						distractionClock.restart();
					}
				}

				
				if (attackClock.getElapsedTime().asSeconds() > physics::dt * 100.f) {
					for (auto pair : PlayerHelper::list) {
						sf::RectangleShape tempshape;
						sf::Vector2f origin;
						origin = { position.x + (sprite.getGlobalBounds().width / 2.f), position.y + sprite.getGlobalBounds().height + 10.f };
						tempshape.setFillColor(sf::Color::Magenta);
						tempshape.setSize({ 10,10 });
						tempshape.setPosition(origin);

						auto p = pair.second;

						BulletHelper::createCustomAngledBullet(origin, p->position, tempshape, true, id); //p->position
						playGunshot();
					}

					attackClock.restart();
				}

			}
			else {
				startDistraction();
			}

			sf::Vector2f playerLoc;

			for (auto pair : PlayerHelper::list) {
				auto p = pair.second;

				playerLoc = p->position;
			}

			auto pixelpos = window.mapPixelToCoords({ 0, 300 });
			pixelpos.x = playerLoc.x - (sprite.getGlobalBounds().width / 2);

			if (distracted) {
				pixelpos = { distractionPoint.x - (sprite.getGlobalBounds().width / 2.f), distractionPoint.y - (sprite.getGlobalBounds().height / 2.f)};
			}
			
			if (!distracted) {
				pixelpos.y += (100.f * cos(cos_counter));
			}
			if (cos_counter < (2.f * 3.14)) {
				cos_counter += physics::dt * 0.1f;
			}
			else {
				cos_counter = 0.f;
			}

			sf::Vector2f movement = (pixelpos - position);
			sprite.move(movement * (physics::dt * .1f));
			position = sprite.getPosition();


			
			if (movement.x > 100) {
				//looking right
				side = LEFT;
			}
			else if (movement.x < -100) {
				//looking left
				side = RIGHT;
			}
			else {
				//center
				side = NONE;
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
			if (!mutex) {
				//playFirewallDeath();
			}
			mutex = true;
			auto pixelpos = window.mapPixelToCoords({ (int)WIDTH / 2, (int)HEIGHT + 500 });
			sf::Vector2f movement = (pixelpos - position);
			sprite.move(movement * (physics::dt * .025f));
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
		dead = true;
	}

	void animate() {
		if (health <= 1000 && health > 666) {
			switch (side) {
			case LEFT:
				sprite.setTexture(texture01_r);
				break;
			case RIGHT:
				sprite.setTexture(texture01_l);
				break;
			case NONE:
				sprite.setTexture(texture01);
				break;
			}
			
		}
		else if (health <= 666 && health > 333) {
			switch (side) {
			case LEFT:
				sprite.setTexture(texture02_r);
				break;
			case RIGHT:
				sprite.setTexture(texture02_l);
				break;
			case NONE:
				sprite.setTexture(texture02);
				break;
			}
		}
		else if (health <= 333 && health > 0) {
			switch (side) {
			case LEFT:
				sprite.setTexture(texture03_r);
				break;
			case RIGHT:
				sprite.setTexture(texture03_l);
				break;
			case NONE:
				sprite.setTexture(texture03);
				break;
			}
		}
		else {
			sprite.setTexture(texture04);
		}

	}
};