#pragma once
#include "Entity.h"
#include <Windows.h>
#include <iostream>
#include "Includes.h"

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
	sf::Vector2f defaultSize;
	float health = 100.0f;

	Player(sf::Vector2f pos, sf::RectangleShape& shape) {
		position = pos;
		velocity = { 0,0 };
		acceleration = { 0, 9.81f };

		shape.setPosition(position);
		drawable = &shape;
		
		defaultSize = drawable->getSize();
	}

	direction currentXDirection;
	direction currentYDirection;

	// 0 none
	// 1 left
	// 2 right
	// 3 up
	// 4 down

	void jump() {
		std::cout << "jump" << std::endl;
		acceleration = { 0, 9.81f };
		airborne = true;
		velocity.y -= 50;
	}

	void duck() {
		std::cout << "duck" << std::endl;
		drawable->setSize({ defaultSize.x, defaultSize.y - 5 });
		updateShape();
		
	}

	void unduck() {
		drawable->setSize(defaultSize);
		updateShape();
	}

	void move() {
		velocity.x = 0;
		if (GetAsyncKeyState(VK_SHIFT)) {
			if (!airborne) {
				speed_mult = 2.0f;
			}

		}
		else {
			speed_mult = 1.0f;
		}
		if (GetAsyncKeyState(VK_D)) {
			//std::cout << "right" << std::endl;
			velocity.x = default_speed * speed_mult;
		}
		if (GetAsyncKeyState(VK_A)) {
			//std::cout << "left" << std::endl;
			velocity.x = -default_speed * speed_mult;
		}
		if (GetAsyncKeyState(VK_W)) {
			//std::cout << "up" << std::endl;
		}
		if (GetAsyncKeyState(VK_S)) {
			//std::cout << "down" << std::endl;
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
	}

};

namespace PlayerHelper {
	std::map<int, Player*> list;

	int createPlayer(sf::Vector2f pos, sf::RectangleShape& shape) {
		auto tempPlayer = new Player(pos, shape);

		EntityHelper::list[tempPlayer->id] = tempPlayer;
		list[tempPlayer->id] = tempPlayer;

		return tempPlayer->id;
	}
};