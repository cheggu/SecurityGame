#pragma once
#include "Entity.h"
#include "Font.h"
#include <iostream>

enum EntityID {
	FIREWALLGRUNT,
	FIREWALLBOSS,
	STALKERGRUNT,
	HACKERGRUNT,
	BRAINBOSS

};


class AIEntity : public Entity {
public:
	bool airborne = false;
	direction currentXDirection;
	direction currentYDirection;
	bool onSurface = false;
	bool isRunning = false;

	sf::Texture IdleTexture;
	sf::IntRect IdleRectSourceSprite;

	sf::Texture RunningTexture;
	sf::IntRect RunningRectSourceSprite;

	sf::Sprite sprite;
	sf::Clock spriteClock;

	sf::Vector2f TextureRectSize = {};
	float individualFrameSize = 0.0f;

	sf::Text healthText;
	

	AIEntity() {
		id = generateRandomNumberRange(100, 199);
		position = { 0,0 };
		velocity = { 0,0 };
		acceleration = { 0, 9.81f };
		enttype = AI;
		drawable = new sf::RectangleShape({ 10,10 });

		healthText.setFont(Font::arial);
		healthText.setCharacterSize(13);
	}

	AIEntity(sf::Vector2f pos, sf::RectangleShape& shape) {
		id = generateRandomNumberRange(100, 199);
		position = pos;
		velocity = { 0,0 };
		acceleration = { 0, 9.81f };
		enttype = AI;
		shape.setPosition(position);
		drawable = &shape;

		healthText.setFont(Font::arial);
		healthText.setCharacterSize(13);
	}

	void nextMove() {
		for (auto ent : EntityHelper::list) {
			if (ent.second->enttype == PLAYER) {
				auto player = ent.second;

				auto playerPos = player->position;
				if (abs((playerPos - position).x) < (WIDTH - (WIDTH / 2)) && abs((playerPos - position).y) < (HEIGHT - (HEIGHT / 2))) {
					//std::cout << "distance: x" << abs((playerPos - position).x) << " y" << abs((playerPos - position).y) << std::endl;
					if (playerPos.x < position.x) {
						//move left
						velocity.x = -10.0f;
						isRunning = true;
					}
					else {
						//move right
						velocity.x = 10.0f;
						isRunning = true;
					}
				}
				else {
					velocity.x = 0.0f;
					isRunning = false;
				}
				
			}

			if (ent.second->enttype == OBJECT) {
				auto obstacle = ent.second;

				if ((abs(obstacle->position.x - position.x) < 30  && obstacle->position.x > position.x) || (abs(obstacle->position.x + obstacle->drawable->getSize().x - position.x) < 30 && obstacle->position.x < position.x)) {
					if (!airborne) {
						jump();
					}
					
					if (abs(obstacle->position.y - position.y) > 30) { // && obstacle->position.y < position.y
						if (!airborne) {
							jump();
						}
					}
				}

			}
		}

		simStep(physics::dt);

		currentXDirection = determineXDirection();
		currentYDirection = determineYDirection();
	}
	sf::Vector2f simStep(float step) {
		setVel(velocity + (acceleration * step));
		setPos(position + (velocity * step));


		updateShape();

		return position;
	}
	void updateShape() {
		drawable->setPosition(position);
		sprite.setPosition(position.x, position.y + 5);
		healthText.setString(std::to_string((int)health) + " HP");
		healthText.setPosition(position.x, position.y - 20);


	}
	void jump() {
		std::cout << "jump" << std::endl;
		acceleration = { 0, 9.81f };
		airborne = true;
		velocity.y -= 50;
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
	void animate() {
		if (isRunning) {
			sprite.setTexture(RunningTexture);
			sprite.setTextureRect(RunningRectSourceSprite);

			if (spriteClock.getElapsedTime().asSeconds() > 0.1f) {
				if (RunningRectSourceSprite.left == (TextureRectSize.x - individualFrameSize))
				{
					RunningRectSourceSprite.left = 0;
				}
				else
				{
					RunningRectSourceSprite.left += individualFrameSize;
				}
				sprite.setTextureRect(RunningRectSourceSprite);
				spriteClock.restart();
			}
		}
		else {
			sprite.setTexture(IdleTexture);
			sprite.setTextureRect(IdleRectSourceSprite);

			if (spriteClock.getElapsedTime().asSeconds() > 0.1f) {

				if (IdleRectSourceSprite.left == (TextureRectSize.x - (2.0f * individualFrameSize)))
				{
					IdleRectSourceSprite.left = 0;
				}
				else
				{
					IdleRectSourceSprite.left += individualFrameSize;
				}
				sprite.setTextureRect(IdleRectSourceSprite);
				spriteClock.restart();
			}
		}
	}

};

namespace AIHelper {
	std::map<int, AIEntity*> list;
	sf::RectangleShape tempShape({ 10,10 });

	int createAI(EntityID ent, sf::Vector2f pos) {
		auto tempPlayer = new AIEntity(pos, tempShape);

		switch (ent) {
		case FIREWALLGRUNT:
			tempShape.setSize({ 50,90 });
			tempShape.setFillColor(sf::Color::Transparent);
			tempShape.setPosition(pos);

			tempPlayer = new AIEntity(pos, tempShape);
			if (!tempPlayer->IdleTexture.loadFromFile("Content/Sprites/firewallgrunt/firewallgrunt_0.png")) {
				std::cout << "Content/Sprites/firewallgrunt/firewallgrunt_0.png" << std::endl;
			}
			tempPlayer->IdleRectSourceSprite = sf::IntRect(0, 0, 50, 90);


			if (!tempPlayer->RunningTexture.loadFromFile("Content/Sprites/firewallgrunt/firewallgrunt_0.png")) {
				std::cout << "Content/Sprites/firewallgrunt/firewallgrunt_0.png" << std::endl;
			}
			tempPlayer->RunningRectSourceSprite = sf::IntRect(0, 0, 50, 90);


			tempPlayer->sprite = sf::Sprite(tempPlayer->IdleTexture, tempPlayer->IdleRectSourceSprite);

			tempPlayer->individualFrameSize = 50;
			tempPlayer->TextureRectSize = { 100,90 };

			tempPlayer->health = 50;
		}
		

		EntityHelper::list[tempPlayer->id] = tempPlayer;
		list[tempPlayer->id] = tempPlayer;

		return tempPlayer->id;
	}

	void simulateAll() {
		//Simulate AI
		for (auto ai : AIHelper::list) {
			auto AI = ai.second;

			AI->nextMove();
			AI->animate();

			if (AI->health <= 0) {
				EntityHelper::list.erase(AI->id);
				AIHelper::list.erase(AI->id);
				delete AI;
				std::cout << "dead" << std::endl;
			}
		}
	}
};