#pragma once
#include "Entity.h"
#include "PhysicsSystem.h"
#include <iostream>
#include "Utils.h"

class Bullet : public Entity {
public:
	sf::Clock clock;
	bool doPersist = false;
	int doPersistTime = 0;
	bool hasOwner;
	int ownerID;

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
		drawable->setSize({ 5, 5 });

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

	Bullet(sf::Vector2f origin, sf::Vector2f destination, sf::RectangleShape _drawable) {
		id = generateID();

		enttype = PROJECTILE;
		std::cout << "new bullet" << std::endl;
		drawable = new sf::RectangleShape(_drawable);
		/*drawable->setFillColor(sf::Color::Red);
		drawable->setSize({ 5, 5 });*/

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

	Bullet(sf::Vector2f origin, sf::Vector2f destination, sf::RectangleShape _drawable, int persistTime) {
		id = generateID();

		enttype = PROJECTILE;
		std::cout << "new bullet" << std::endl;
		drawable = new sf::RectangleShape(_drawable);
		/*drawable->setFillColor(sf::Color::Red);
		drawable->setSize({ 5, 5 });*/

		doPersist = true;
		doPersistTime = persistTime;

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

	Bullet(sf::Vector2f origin, sf::Vector2f destination, sf::RectangleShape _drawable, bool owned, int owner) {
		id = generateID();

		enttype = PROJECTILE;
		std::cout << "new bullet" << std::endl;
		drawable = new sf::RectangleShape(_drawable);
		/*drawable->setFillColor(sf::Color::Red);
		drawable->setSize({ 5, 5 });*/

		hasOwner = true;
		ownerID = owner;

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
			if (ent.second->enttype != DROPDOWN && ent.second->BulletCollisionsEnabled == true) { // && ent.second->id != 1
				physics::AABB bulletBox = { drawable->getPosition(), drawable->getPosition() + drawable->getSize() };
				physics::AABB entBox = { ent.second->drawable->getPosition(), ent.second->drawable->getPosition() + ent.second->drawable->getSize() };

				if (physics::AABBvsAABB(bulletBox, entBox) && this->id != ent.first && (ent.second->enttype != PLAYER || (ent.second->enttype == PLAYER && hasOwner)) && ent.second->enttype != PROJECTILE) {
					float damage = 1;

					if (ent.second->enttype == PLAYER) {
						std::cout << "hitplayer" << std::endl;
						signalPlayerHit = true;
						return true;
					}

					if (hasOwner && ownerID == ent.second->id) {
						damage = 0;
					}
					
					if (ent.second->id == boss01id) {
						auto collision = physics::handleCollision(*drawable, *ent.second->drawable); 
						if ((ent.second->bossside00 == LEFT && collision == 2) || (ent.second->bossside00 == RIGHT && collision == 1)) {
							damage *= 15;
						}

						std::cout << collision << std::endl;
					}
					if (ent.second->id == boss02id) {
						if (doPersist) {
							damage *= 0.05;
						}
					}

					ent.second->damage(damage);
					return true;
				}
			}
			
		}
		if (clock.getElapsedTime().asSeconds() > 10) {
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

	int createCustomAngledBullet(sf::Vector2f origin, sf::Vector2f destination, sf::RectangleShape drawable) {
		auto tempEnt = new Bullet(origin, destination, drawable);

		EntityHelper::list[tempEnt->id] = tempEnt;
		list[tempEnt->id] = tempEnt;

		return tempEnt->id;
	}

	int createCustomAngledBullet(sf::Vector2f origin, sf::Vector2f destination, sf::RectangleShape drawable, int persistTime) {
		auto tempEnt = new Bullet(origin, destination, drawable, persistTime);

		EntityHelper::list[tempEnt->id] = tempEnt;
		list[tempEnt->id] = tempEnt;

		return tempEnt->id;
	}

	int createCustomAngledBullet(sf::Vector2f origin, sf::Vector2f destination, sf::RectangleShape drawable, bool hasOwner, int ownerID) {
		auto tempEnt = new Bullet(origin, destination, drawable, hasOwner, ownerID);

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