#pragma once
#include "Entity.h"
#include <Windows.h>
#include <iostream>
#include "Includes.h"
#include "Bullet.h"
#include "Audio.h"
#include "Inventory.h"
#include "Font.h"
#include <sstream>
#include <iomanip>
#include "Platform.h"
#include "obj_InvisibleLayer.h"

#define VK_D 0x44
#define VK_S 0x53
#define VK_A 0x41
#define VK_W 0x57

class Player : public Entity {
public:
	float default_speed = 15.0f;
	float max_speed = 256;
	float speed_mult = 1.0f;
	bool airborne = false;
	bool onSurface = false;
	bool outOfBounds = false;
	bool canSprint = true;
	sf::Vector2f defaultSize;
	float health = 100.0f;
	direction face = NONE;
	bool isRunning = false;
	bool canShoot = true;
	sf::Clock clock;
	sf::Clock hurtCooldown;
	float bulletCooldown = 100;
	sf::Vector2f lastCheckpoint;

	sf::Texture IdleTexture;
	sf::IntRect IdleRectSourceSprite;

	sf::Texture RunningTexture;
	sf::IntRect RunningRectSourceSprite;

	sf::Texture JumpingTexture;
	sf::IntRect JumpingRectSourceSprite;

	sf::Sprite sprite;
	sf::Clock spriteClock;

	sf::Text chargingText;

	sf::CircleShape scannerCircle;
	bool doImpulse = false;
	sf::Clock impulseClock;
	
	sf::RectangleShape shape;


	Player(sf::Vector2f pos) {
		position = pos;
		velocity = { 0,0 };
		acceleration = { 0, 9.81f };
		enttype = PLAYER;
		id = generateID();

		shape.setSize({ 10.f, 20.f });
		shape.setFillColor(sf::Color::Green);
		shape.setPosition(WIDTH / 2, HEIGHT / 2);

		shape.setPosition(position);
		drawable = &shape;
		drawable->setFillColor(sf::Color::Transparent);
		
		if (!IdleTexture.loadFromFile("Content/Sprites/idle48x48.png")) {
			std::cout << "Content/Sprites/idle48x48.png missing" << std::endl;
		}
		IdleRectSourceSprite = sf::IntRect(48, 0, 48, 48);


		if (!RunningTexture.loadFromFile("Content/Sprites/running48x48.png")) {
			std::cout << "Content/Sprites/running48x48.png missing" << std::endl;
		}
		RunningRectSourceSprite = sf::IntRect(48, 0, 48, 48);


		if (!JumpingTexture.loadFromFile("Content/Sprites/jump48x48.png")) {
			std::cout << "Content/Sprites/jump48x48.png missing" << std::endl;
		}
		JumpingRectSourceSprite = sf::IntRect(48, 0, 48, 48);


		sprite = sf::Sprite(IdleTexture, IdleRectSourceSprite);

		chargingText.setFont(Font::emulogic);
		chargingText.setCharacterSize(8);
		chargingText.setFillColor(sf::Color::White);
		chargingText.setString("charging");

		scannerCircle.setFillColor(sf::Color::Transparent);
		scannerCircle.setOutlineColor(sf::Color::White);
		scannerCircle.setOutlineThickness(3);
		scannerCircle.setRadius(1);
		scannerCircle.setPosition(position);

		sprite.setScale({ 1.5f,1.5f });

		defaultSize = drawable->getSize();
	}

	direction currentXDirection;
	direction currentYDirection;

	void hurt(float amount) {
		health -= amount;
		playPlayerHurt();
	}

	void impulse() {
		if (doImpulse) {
			scannerCircle.setOutlineColor(sf::Color::White);
			scannerCircle.setRadius(scannerCircle.getRadius() + physics::dt * 100);
			scannerCircle.setPosition(position.x - scannerCircle.getRadius(), position.y - scannerCircle.getRadius());

			if (scannerCircle.getRadius() > 1000) {
				scannerCircle.setRadius(0);
				doImpulse = false;
			}

			for (auto pair : InvisLayerHelper::list) {
				auto layer = pair.second;
				layer->disable();
			}
		}
		else {
			scannerCircle.setOutlineColor(sf::Color::Transparent);
			for (auto pair : InvisLayerHelper::list) {
				auto layer = pair.second;
				layer->enable();
			}
		}
	}

	void shoot() {
		switch (Inventory::currentyEquippedItem) {
		case InventoryItem::DOSGUN:
			bulletCooldown = 100;
			break;
		case InventoryItem::PORTGUN:
			bulletCooldown = 1750;
			break;
		case InventoryItem::CRYPTOGUN:
			bulletCooldown = 3500;
			break;
		case InventoryItem::BRUTEFORCE:
			bulletCooldown = 7500;
			break;
		}

		if (Cheats::SuperGun) {
			bulletCooldown *= (1.f / Cheats::SuperGunCooldown);
		}

		//unlockText.setPosition(rect.left + (rect.width / 2.0f) - (unlockText.getGlobalBounds().width / 2.f), rect.top - 20);
		chargingText.setPosition(position.x - (chargingText.getGlobalBounds().width / 2), position.y + 50);

		chargingText.setString((std::string)m_round_str(clock.getElapsedTime() / sf::milliseconds(bulletCooldown) * 100) + "%");

		
		if (clock.getElapsedTime() > sf::milliseconds(bulletCooldown)) {
			auto pixelpos = sf::Mouse::getPosition(window);
			
			if (Inventory::currentyEquippedItem == InventoryItem::CRYPTOGUN) {
				sf::RectangleShape tempRect;
				tempRect.setFillColor(sf::Color::Green);
				tempRect.setSize({ 10,10 });
				BulletHelper::createCustomAngledBullet(position, window.mapPixelToCoords(pixelpos), tempRect, 5);
			}
			else if (Inventory::currentyEquippedItem == InventoryItem::BRUTEFORCE) {
				sf::RectangleShape tempRect;
				tempRect.setFillColor(sf::Color(0xFF760DFF));
				tempRect.setSize({ 50,50 });
				BulletHelper::createCustomAngledBullet_Brute({ position.x, position.y - 50 }, window.mapPixelToCoords(pixelpos), tempRect);
			}
			else if (Inventory::currentyEquippedItem == InventoryItem::PORTGUN) {
				doImpulse = true;
				impulseClock.restart();
			}
			else {
				BulletHelper::createAngledBullet(position, window.mapPixelToCoords(pixelpos));
			}

			playGunshot();

			clock.restart();
		}
		else {
			if (Inventory::currentyEquippedItem != InventoryItem::DOSGUN) {
				chargingText.setFillColor(sf::Color::White);
			}
			//doImpulse = false;
		}
	}

	void jump() {
		//std::cout << "jump" << std::endl;
		acceleration = { 0, 9.81f };
		airborne = true;


		if (Cheats::SuperJump) {
			velocity.y -= Cheats::SuperJumpValue;
		}
		else {
			velocity.y -= 50;
		}
	}

	void duck() {
		//std::cout << "duck" << std::endl;
		drawable->setSize({ defaultSize.x, defaultSize.y - 5 });
		updateShape();
		
	}

	void unduck() {
		drawable->setSize(defaultSize);
		updateShape();
	}

	void move() {
		chargingText.setFillColor(sf::Color::Transparent);

		if (Cheats::SuperSpeed) {
			default_speed = Cheats::SuperSpeedValue;
		}


		velocity.x = 0;
		if (GetAsyncKeyState(VK_SHIFT) && canSprint) {
			if (!airborne) {
				speed_mult = 2.0f;
			}
		}
		else {
			speed_mult = 1.0f;
		}

		if (GetAsyncKeyState(VK_LBUTTON)) {
			if (onSurface) {
				speed_mult = 1.0f; 
				canSprint = false;
			}
			shoot();
		}
		else {
			canSprint = true;
		}

		if (GetAsyncKeyState(VK_D)) {
			
			velocity.x = default_speed * speed_mult;
			isRunning = true;
			
			face = RIGHT;
		}
		else if (GetAsyncKeyState(VK_A)) {
			
			velocity.x = -default_speed * speed_mult;
			isRunning = true;
			face = LEFT;
		}
		else {
			isRunning = false;
		}

		if (GetAsyncKeyState(VK_W)) {

		}
		if (GetAsyncKeyState(VK_S)) {
			
			if (!airborne) {
				duck();
			}
		}

		if (GetAsyncKeyState(VK_SPACE)) {
			if (!airborne) {
				jump();
			}	
		}

		currentXDirection = determineXDirection();
		currentYDirection = determineYDirection();
	}

	direction determineXDirection() {
		if (velocity.x < 0) {
			return LEFT;
		}
		else if (velocity.x > 0) {
			return RIGHT;
		}
		return NONE;
	}

	direction determineYDirection() {
		if (velocity.y < 0) {
			return UP;
		}
		else if (velocity.y > 0) {
			return DOWN;
		}
		return NONE;
	}


	void setPos(sf::Vector2f newPos) {
		position = newPos;
	}

	void setVel(sf::Vector2f v) {
		velocity = v;
	}

	sf::Vector2f simStep(float step) {
		setVel(velocity + (acceleration * step));
		setPos(position + (velocity * step));


		updateShape();

		return position;
	}

	void updateShape() {
		drawable->setPosition(position);
		sprite.setPosition(position.x - (sprite.getGlobalBounds().width / 2.25), position.y - (sprite.getGlobalBounds().height / 2) - 2);

		if (face == RIGHT) {
			sprite.setScale({ 1.5f, 1.5f });
		}
		if (face == LEFT) {
			sprite.setScale({ -1.5f, 1.5f });
			sprite.setPosition(sprite.getPosition().x + sprite.getGlobalBounds().width, sprite.getPosition().y);
		}
	}

	void reset() {
		setPos(lastCheckpoint);
		health = 100.f;
	}

};

namespace PlayerHelper {
	std::map<int, Player*> list;

	int createPlayer(sf::Vector2f pos) { //, sf::RectangleShape& shape
		auto tempPlayer = new Player(pos);

		EntityHelper::list[tempPlayer->id] = tempPlayer;
		list[tempPlayer->id] = tempPlayer;

		return tempPlayer->id;
	}

	void simulateAll() {
		for (auto player : PlayerHelper::list) {
			auto p = player.second;

			if (Cheats::SuperGun) {
				p->bulletCooldown = Cheats::SuperGunCooldown;
			}
			if (Cheats::GodMode) {
				p->health = Cheats::GodModeHealth;
			}

			p->simStep(physics::dt);

			auto pos = p->position;
			auto dif = pos - sf::Vector2f(WIDTH / 2, HEIGHT / 2);

			p->move();

			p->impulse();
			if (p->impulseClock.getElapsedTime().asSeconds() > 5) {
				p->doImpulse = false;
			}

			if (p->airborne) {
				//std::cout << p->velocity.y << std::endl;

				p->sprite.setTexture(p->JumpingTexture);
				p->sprite.setTextureRect(p->JumpingRectSourceSprite);

				if (p->velocity.y < -5.0) {
					//std::cout << "up" << std::endl;
					p->JumpingRectSourceSprite.left = 0;
				}
				else if (p->velocity.y > 5.0) {
					//std::cout << "down" << std::endl;
					p->JumpingRectSourceSprite.left = 96;
				}
				else {
					//std::cout << "neutral" << std::endl;
					p->JumpingRectSourceSprite.left = 48;
				}
				p->sprite.setTextureRect(p->JumpingRectSourceSprite);
			}
			else if (p->isRunning) {
				p->sprite.setTexture(p->RunningTexture);
				p->sprite.setTextureRect(p->RunningRectSourceSprite);

				if (p->spriteClock.getElapsedTime().asSeconds() > 0.1f) {
					if (p->RunningRectSourceSprite.left == (384 - 48))
					{
						p->RunningRectSourceSprite.left = 0;
					}
					else
					{
						p->RunningRectSourceSprite.left += 48;
					}
					p->sprite.setTextureRect(p->RunningRectSourceSprite);
					p->spriteClock.restart();
				}
			}
			else {
				p->sprite.setTexture(p->IdleTexture);
				p->sprite.setTextureRect(p->IdleRectSourceSprite);

				if (p->spriteClock.getElapsedTime().asSeconds() > 0.1f) {

					if (p->IdleRectSourceSprite.left == (480 - 48))
					{
						p->IdleRectSourceSprite.left = 0;
					}
					else
					{
						p->IdleRectSourceSprite.left += 48;
					}
					p->sprite.setTextureRect(player.second->IdleRectSourceSprite);
					p->spriteClock.restart();
				}
			}
			

			if (p->position.y > 1500) {
				if (!p->outOfBounds) {
					playPlayerFall();
				}

				p->outOfBounds = true;
				
				if (p->position.y > 4000) {
					p->health -= 10.0f;
					p->setPos({ WIDTH / 2, HEIGHT / 2 });
					p->updateShape();
					p->outOfBounds = false;
				}
			}
		}
	}
};