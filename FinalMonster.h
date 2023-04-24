#pragma once
#include "Entity.h"
#include "Includes.h"
#include "Bullet.h"
#include "obj_Character.h"

class FinalMonster : public Entity {

private:
	sf::Text healthText;
	float cos_counter;

	bool shield_active = true;

	sf::Clock attackClock;
	sf::Clock shieldClock;
	bool shield_mutex = false;

	float attackTime = 200;

	bool stage1 = true, stage2 = false, stage3 = false; 
	bool skip = false;


	bool invulnerable = false;
	float last_x;

	direction side;

	sf::RectangleShape shape;
	sf::Sprite sprite;
	sf::Texture texture01, texture02, texture03, texture04, texture05;

	sf::Sprite shield_sprite;
	sf::Texture textureshield;

	float cur_held_health = 1000.f;

	bool dead = true;
	bool mutex = false;

public:
	float maxHealth = 1000.f;

	std::map<int, sf::Drawable*> drawableList = {};

	FinalMonster() {
		boss03id = id;
		health = 1000;
		texture01.loadFromFile("Content/Sprites/Icons/Hacker/hacker.png");
		texture02.loadFromFile("Content/Sprites/Icons/Hacker/hacker_spread.png");
		texture03.loadFromFile("Content/Sprites/Icons/Hacker/hacker_spread_glow.png");
		texture04.loadFromFile("Content/Sprites/Icons/Hacker/hacker_spread_glow_angry.png");
		texture05.loadFromFile("Content/Sprites/Icons/Hacker/hacker_death.png");
		textureshield.loadFromFile("Content/Sprites/Icons/Hacker/shield.png");

		sprite.setTexture(texture01);
		sprite.setScale(1.5, 1.5);

		shield_sprite.setTexture(textureshield);
		shield_sprite.setScale(1.5, 1.5);
		shield_sprite.setColor(sf::Color(0xffffffaa));


		acceleration = { 0,0 };
		position = { 5765, 865 }; //-5000

		updateShape();
		
		drawableList[0] = &sprite;
		drawableList[1] = &shield_sprite;

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

	sf::Sprite& getSprite() {
		return sprite;
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

	void damage(float amount) {
		if (!invulnerable) {
			health -= amount;
		}
		else {
			health -= amount / 10.f;
		}
		if (health == 0 && enttype != PLAYER) {
			EntityHelper::list.erase(this->id);
		}
	}

	void shield() {
		shield_sprite.setColor(sf::Color(0xffffffaa));
		invulnerable = true;
		last_x = position.x;
	}

	void nextMove() {
		sprite.setTexture(texture02);
		if (health > 0) {
			//std::cout << "foo" << std::endl;
			
			if (!finalBossBruteHit) {
				shield();
				if (attackClock.getElapsedTime().asMilliseconds() > attackTime) {
					for (auto pair : PlayerHelper::list) {
						auto p = pair.second;
						sf::RectangleShape tempshape;
						tempshape.setFillColor(sf::Color::Green);
						tempshape.setSize({ 10,10 });

						sf::Vector2f origin = { position.x + (sprite.getGlobalBounds().width / 2), position.y + sprite.getGlobalBounds().height + 10 };

						if (stage1) {
							origin.x += (500.f * cos(cos_counter));
							origin.y -= 500;

							auto target = p->position;
							target.x += (100.f * cos(cos_counter));
							BulletHelper::createCustomAngledBullet(origin, target, tempshape, true, id);
						}
						else if (stage2) {
							origin = window.mapPixelToCoords({ 0, (int)HEIGHT / 4 });
							origin.y += (HEIGHT / 4.f) * cos(cos_counter);


							auto target = p->position;
							target.x += (100.f * cos(cos_counter));

							BulletHelper::createCustomAngledBullet(origin, target, tempshape, true, id);
							
							origin.x = window.mapPixelToCoords({ (int)WIDTH, (int)HEIGHT / 4 }).x;

							BulletHelper::createCustomAngledBullet(origin, target, tempshape, true, id);

						}
						else if (stage3) {
							attackTime = 150;

							origin.x += (500.f * cos(cos_counter));
							origin.y -= 500;

							auto target = p->position;
							target.x += (100.f * cos(cos_counter));
							BulletHelper::createCustomAngledBullet(origin, target, tempshape, true, id);

							origin = window.mapPixelToCoords({ 0, (int)HEIGHT / 4 });
							origin.y += (HEIGHT / 4.f) * cos(cos_counter);


							target = p->position;
							target.x += (100.f * cos(cos_counter));

							BulletHelper::createCustomAngledBullet(origin, target, tempshape, true, id);

							origin.x = window.mapPixelToCoords({ (int)WIDTH, (int)HEIGHT / 4 }).x;

							BulletHelper::createCustomAngledBullet(origin, target, tempshape, true, id);
						}
						

						

						
						playGunshot();
					}
					attackClock.restart();
				}
				//perform attack patterns
			}
			else {
				invulnerable = false;
				if (!shield_mutex) {
					shieldClock.restart();
				}
				shield_mutex = true;

				if (shieldClock.getElapsedTime().asSeconds() > 10 || skip) {
					finalBossBruteHit = false;
					shield_mutex = false;
					skip = false;
				}
				else {
					//is vulnerable, no attacks, lower position
					shield_sprite.setColor(sf::Color::Transparent);
				}
			}



			sf::Vector2f playerLoc;

			for (auto pair : PlayerHelper::list) {
				auto p = pair.second;

				playerLoc = p->position;
			}
			
			auto pixelpos = window.mapPixelToCoords({ 0, 300 });
			pixelpos.x = playerLoc.x - (sprite.getGlobalBounds().width / 2);
			pixelpos.y += (100.f * cos(cos_counter));
			if (cos_counter < (2.f * 3.14)) {
				cos_counter += physics::dt * 0.1f;
			}
			else {
				cos_counter = 0.f;
			}

			if (!invulnerable) {
				pixelpos = (window.mapPixelToCoords({ 0, (int)HEIGHT - 200 }));
				pixelpos.x = last_x;
			}

			sf::Vector2f movement = (pixelpos - position);
			sprite.move(movement * (physics::dt * .1f));
			position = sprite.getPosition();
			shield_sprite.setPosition(position);

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
				side = direction::NONE;
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
		if (health <= 1000 && health > 500) {
			sprite.setTexture(texture02);
		}
		else if (health <= 500 && health > 150) {
			sprite.setTexture(texture03);
			if (!stage2) {
				stage1 = false;
				invulnerable = true;
				skip = true;
				stage2 = true;
			}
		}
		else if (health <= 150 && health > 0) {
			sprite.setTexture(texture04);
			if (!stage3) {
				stage2 = false;
				invulnerable = true;
				skip = true;
				stage3 = true;
			}
		}
		else {
			sprite.setTexture(texture05);
		}

	}
};