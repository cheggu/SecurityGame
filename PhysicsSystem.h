#pragma once
#include "Entity.h"

namespace physics {
	float dt = 0.01;


	struct AABB
	{
		sf::Vector2f min;
		sf::Vector2f max;
	};

	bool AABBvsAABB(AABB a, AABB b)
	{
		// Exit with no intersection if found separated along an axis 
		if (a.max.x < b.min.x or a.min.x > b.max.x) return false;
		if (a.max.y < b.min.y or a.min.y > b.max.y) return false;

		// No separating axis found, therefor there is at least one overlapping axis 
		return true;
	}

	void apply_gravity_to_ent(Entity& ent) {
		ent.velocity = { ent.velocity.x, ent.velocity.y + (dt * 9.81f)};
		ent.position = { ent.position.x + (ent.velocity.x * dt), ent.position.y + (ent.velocity.y * dt) };
	}

    bool isCollided(sf::RectangleShape ent1, sf::RectangleShape ent2) {
        if (ent1.getPosition().x < ent2.getPosition().x + ent2.getSize().x &&
            ent1.getPosition().x + ent1.getSize().x > ent2.getPosition().x &&
            ent1.getPosition().y < ent2.getPosition().y + ent2.getSize().y &&
            ent1.getPosition().y + ent1.getSize().y > ent2.getPosition().y)
        {
            //std::cout << ("Collision Detected");
            return true;
        }
        else {
            return false;
        }
    }

    //entity, player
    int handleCollision(sf::RectangleShape player1, sf::RectangleShape player2) {
        if (isCollided(player1, player2)) {
            // Most of this stuff would probably be good to keep stored inside the player
            // along side their x and y position. That way it doesn't have to be recalculated
             // every collision check
            float playerHalfW = player1.getSize().x / 2.f;
            float playerHalfH = player1.getSize().y / 2.f;
            float enemyHalfW = player2.getSize().x / 2.f;
            float enemyHalfH = player2.getSize().y / 2.f;
            float playerCenterX = player1.getPosition().x + player1.getSize().x / 2.f;
            float playerCenterY = player1.getPosition().y + player1.getSize().y / 2;
            float enemyCenterX = player2.getPosition().x + player2.getSize().x / 2.f;
            float enemyCenterY = player2.getPosition().y + player2.getSize().y / 2.f;

            // Calculate the distance between centers
            float diffX = playerCenterX - enemyCenterX;
            float diffY = playerCenterY - enemyCenterY;

            // Calculate the minimum distance to separate along X and Y
            float minXDist = playerHalfW + enemyHalfW;
            float minYDist = playerHalfH + enemyHalfH;

            // Calculate the depth of collision for both the X and Y axis
            float depthX = diffX > 0 ? minXDist - diffX : -minXDist - diffX;
            float depthY = diffY > 0 ? minYDist - diffY : -minYDist - diffY;

            // Now that you have the depth, you can pick the smaller depth and move
            // along that axis.
            if (depthX != 0 && depthY != 0) {
                if (std::abs(depthX) < std::abs(depthY)) {
                    // Collision along the X axis. React accordingly
                    if (depthX > 0) {
                        return 1; // Left side collision
                    }
                    else {
                        return 2;// Right side collision
                    }
                }
                else {
                    // Collision along the Y axis.
                    if (depthY > 0) {
                        return 3;// Top side collision
                    }
                    else {
                        return 4;// Bottom side collision
                    }
                }
            }
        }
        else {
            return 0; //No collision
        }
    }

    std::string resolveCollision(Entity& ent1, Entity& ent2, int coll) {

        //brick = ent1
        //player1 = ent2

        std::string collLocation;
        //int coll = physics::handleCollision(*ent1.drawable, *ent2.drawable);
        sf::Vector2f newLoc;
        switch (coll) {
        case 0:
            collLocation = "Nowhere";
            break;
        case 1:
            collLocation = "Left";
            newLoc.x = ent1.drawable->getPosition().x - ent2.drawable->getSize().x - 1;
            newLoc.y = ent2.drawable->getPosition().y;

            ent2.drawable->setPosition(newLoc);
            ent2.position = newLoc;
            break;
        case 2:
            collLocation = "Right";
            newLoc.x = ent1.drawable->getPosition().x + ent1.drawable->getSize().x + 1;
            newLoc.y = ent2.drawable->getPosition().y;

            ent2.drawable->setPosition(newLoc);
            ent2.position = newLoc;
            break;
        case 3:
            collLocation = "Top";
            newLoc.x = ent2.drawable->getPosition().x;
            newLoc.y = ent1.drawable->getPosition().y - ent2.drawable->getSize().y - 1;

            ent2.drawable->setPosition(newLoc);
            ent2.position = newLoc;
            break;
        case 4:
            collLocation = "Bottom";
            newLoc.x = ent2.drawable->getPosition().x;
            newLoc.y = ent1.drawable->getPosition().y + ent1.drawable->getSize().y + 3;

            ent2.drawable->setPosition(newLoc);
            ent2.position = newLoc;
            break;
        }

        return collLocation;
    }

}