#pragma once
#include "Entity.h"
#include "PhysicsSystem.h"
#include <iostream>
#include "Utils.h"

class Bullet : public Entity {
public:
	sf::Clock clock;

	Bullet(direction direction, sf::Vector2f origin) {
		enttype = PROJECTILE;
		std::cout << "new bullet" << std::endl;
		drawable = new sf::RectangleShape();
		drawable->setFillColor(sf::Color::Red);
		drawable->setSize({ 10, 5 });
		
		switch (direction) {
		case (LEFT):
			velocity = { -50.0f, 0.0f };
			position = { origin.x - (drawable->getSize().x * 2) - 10.0f, origin.y + 10 };
			break;
		case (RIGHT):
			velocity = { 50.0f, 0.0f };
			position = { origin.x + 10.0f + (drawable->getSize().x * 2), origin.y + 10 };
			break;
		}
	}

	Bullet(sf::Vector2f origin, sf::Vector2f destination) {
		id = generateID();

		enttype = PROJECTILE;
		std::cout << "new bullet" << std::endl;
		drawable = new sf::RectangleShape();
		drawable->setFillColor(sf::Color::Red);
		drawable->setSize({ 10, 5 });

		velocity = destination - origin;
		float slope = velocity.y / velocity.x;
		position = origin;		

		auto theta = atan(velocity.y / velocity.x);

		auto vx = 1.0f, vy = 1.0f;

		if (destination.x < origin.x) {
			theta *= -1;
		}

		vx = 100.0f * cos(theta);
		vy = 100.0f * sin(theta);

		if (destination.x < origin.x) {
			vx *= -1;
		}

		acceleration = { 0, 2 };

		velocity = { vx,vy };

		clock.restart();
	}


	bool checkForHit() {
		for (auto ent : EntityHelper::list) {
			physics::AABB bulletBox = { drawable->getPosition(), drawable->getPosition() + drawable->getSize() };
			physics::AABB entBox = { ent.second->drawable->getPosition(), ent.second->drawable->getPosition() + ent.second->drawable->getSize() };
			
			if (physics::AABBvsAABB(bulletBox, entBox) && this->id != ent.first && ent.second->enttype != PLAYER && ent.second->enttype != PROJECTILE) {
				std::cout << "bullet hit some shit" <<std::endl;
				ent.second->damage(10);
				return true;
			}
		}
		if (clock.getElapsedTime().asSeconds() > 10) {
			std::cout << "despawning bullet" << std::endl;
			return true;
		}
		return false;
	}

	sf::Vector2f simStep(float step) {
		setVel(velocity + (acceleration * step));
		setPos(position + (velocity * step));


		updateShape();

		return position;
	}

	void setPos(sf::Vector2f newPos) {
		position = newPos;
	}

	void setVel(sf::Vector2f v) {
		velocity = v;
	}

	void updateShape() {
		drawable->setPosition(position);
	}

	~Bullet() {
		std::cout << "bullet says goodbye!" << std::endl;
	}

};



namespace BulletHelper {
	std::map<int, Bullet*> list;

	int createAngledBullet(sf::Vector2f origin, sf::Vector2f destination) {
		auto tempEnt = new Bullet(origin, destination);

		EntityHelper::list[tempEnt->id] = tempEnt;
		list[tempEnt->id] = tempEnt;

		return tempEnt->id;
	}

	int createBullet(direction direction, sf::Vector2f origin) {
		auto tempEnt = new Bullet(direction, origin);

		EntityHelper::list[tempEnt->id] = tempEnt;
		list[tempEnt->id] = tempEnt;

		return tempEnt->id;
	}

	void simulateAll();
}