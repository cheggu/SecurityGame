#pragma once
#include "Player.h"
#include "Platform.h"
#include "AIEntity.h"

#include "PhysicsSystem.h"
#include "Includes.h"

#include "ui_Element.h"
#include "ui_Health.h"
#include "ui_Button.h"
#include "ui_Toolbox.h"

#include "mini_Base.h"

#include "Font.h"

namespace Collisions {
    void simulateAll() {
        sf::RectangleShape surfaceCheck;
        // Player -> Platform Collisions
        int collisionCount = 0;
        for (auto ent1 : PlayerHelper::list) {
            for (auto ent2 : PlatformHelper::list) {
                if (ent2.second->isEnabled()) {
                    int collisionNumber = physics::handleCollision(*ent2.second->drawable, *ent1.second->drawable);

                    surfaceCheck.setPosition(ent1.second->position.x, ent1.second->position.y + ent1.second->drawable->getSize().y);
                    surfaceCheck.setSize({ ent1.second->drawable->getSize().x, 2 });

                    if (physics::isCollided(surfaceCheck, *ent2.second->drawable)) {
                        collisionCount++;
                        //std::cout << "player is on surface" << std::endl;
                        ent1.second->onSurface = true;
                    }

                    if (collisionNumber != 0) {
                        //std::cout << "collision " << collisionNumber << std::endl;
                        collisionCount++;

                        if (collisionNumber == 3) {
                            //std::cout << "collision top" << std::endl;
                            if ((ent1.second->velocity.y < 0.0f || (GetAsyncKeyState(VK_S)) & 0x8000) && ent2.second->isDropdown()) {
                                /*if (GetAsyncKeyState(VK_S) & 0x8000) {
                                    ent1.second->velocity.y += 10;
                                }*/
                            }
                            else {
                                ent1.second->airborne = false;
                                ent1.second->velocity = { ent1.second->velocity.x, 0 };
                                ent1.second->acceleration = { 0, 0 };
                            }
                        }

                        else if (collisionNumber == 1 || collisionNumber == 2) {
                            ent1.second->airborne = true;
                            ent1.second->velocity = { ent1.second->velocity.x, ent1.second->velocity.y };
                            ent1.second->acceleration = { 0, 9.81f };
                        }
                        else if (collisionNumber == 4) {
                            if (ent2.second->isDropdown()) {

                            }
                            else {
                                ent1.second->airborne = true;
                                ent1.second->velocity = { ent1.second->velocity.x, -ent1.second->velocity.y * 0.5f };
                                ent1.second->acceleration = { 0, 9.81f };
                            }
                        }

                        if (!ent2.second->isDropdown()) {
                            physics::resolveCollision(*ent2.second, *ent1.second, collisionNumber);
                        }
                        //apply upwards force to player equal to negative acceleration
                    }
                }
                
            }
            if (collisionCount == 0) {
                ent1.second->acceleration = { 0, 9.81f };
            }
        }



        collisionCount = 0;
        // AI -> Platform Collisions
        for (auto ent1 : AIHelper::list) {
            for (auto ent2 : PlatformHelper::list) {
                int collisionNumber = physics::handleCollision(*ent2.second->drawable, *ent1.second->drawable);

                surfaceCheck.setPosition(ent1.second->position.x, ent1.second->position.y + ent1.second->drawable->getSize().y);
                surfaceCheck.setSize({ ent1.second->drawable->getSize().x, 2 });

                if (physics::isCollided(surfaceCheck, *ent2.second->drawable)) {
                    collisionCount++;

                    ent1.second->onSurface = true;
                }

                if (collisionNumber != 0) {
                    //std::cout << "collision " << collisionNumber << std::endl;
                    collisionCount++;

                    if (collisionNumber == 3) {
                        ent1.second->airborne = false;
                        ent1.second->velocity = { ent1.second->velocity.x, 0 };
                        ent1.second->acceleration = { 0, 0 };
                        
                    }
                    else if (collisionNumber == 1 || collisionNumber == 2) {
                        ent1.second->airborne = true;
                        ent1.second->velocity = { ent1.second->velocity.x, ent1.second->velocity.y };
                        ent1.second->acceleration = { 0, 9.81f };
                    }
                    else if (collisionNumber == 4) {
                        ent1.second->airborne = true;
                        ent1.second->velocity = { ent1.second->velocity.x, -ent1.second->velocity.y * 0.5f };
                        ent1.second->acceleration = { 0, 9.81f };
                        
                    }

                    std::cout << physics::resolveCollision(*ent2.second, *ent1.second, collisionNumber) << std::endl;

                    //apply upwards force to player equal to negative acceleration
                }
            }
            if (collisionCount == 0) {
                ent1.second->acceleration = { 0, 9.81f };
            }
        }

        // AI -> AI Collisions
        for (auto ent1 : AIHelper::list) {
            for (auto ent2 : AIHelper::list) {
                if (ent1.second->id != ent2.second->id) {
                    int collisionNumber = physics::handleCollision(*ent2.second->drawable, *ent1.second->drawable);

                    surfaceCheck.setPosition(ent1.second->position.x, ent1.second->position.y + ent1.second->drawable->getSize().y);
                    surfaceCheck.setSize({ ent1.second->drawable->getSize().x, 2 });

                    if (physics::isCollided(surfaceCheck, *ent2.second->drawable)) {
                        collisionCount++;

                        ent1.second->onSurface = true;
                    }

                    if (collisionNumber != 0) {
                        std::cout << "collision " << collisionNumber << std::endl;
                        collisionCount++;

                        if (collisionNumber == 3) {
                            ent1.second->airborne = false;
                            ent1.second->velocity = { ent1.second->velocity.x, 0 };
                            ent1.second->acceleration = { 0, 0 };
                        }
                        else if (collisionNumber == 1 || collisionNumber == 2) {
                            ent1.second->airborne = true;
                            ent1.second->velocity = { ent1.second->velocity.x, ent1.second->velocity.y };
                            ent1.second->acceleration = { 0, 9.81f };
                        }
                        else if (collisionNumber == 4) {
                            ent1.second->airborne = true;
                            ent1.second->velocity = { ent1.second->velocity.x, -ent1.second->velocity.y * 0.5f };
                            ent1.second->acceleration = { 0, 9.81f };
                        }

                        std::cout << physics::resolveCollision(*ent2.second, *ent1.second, collisionNumber) << std::endl;

                        //apply upwards force to player equal to negative acceleration
                    }
                }
                if (collisionCount == 0) {
                    ent1.second->acceleration = { 0, 9.81f };
                }
            }
        }
    }
}