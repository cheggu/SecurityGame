#pragma once
#include "Entity.h"
#include "Player.h"
#include "Platform.h"
#include "AIEntity.h"

#include "PhysicsSystem.h"
#include "CollisionHandler.h"

#include "Includes.h"

#include "ui_Element.h"
#include "ui_Health.h"
#include "ui_Button.h"
#include "ui_Toolbox.h"

#include "obj_Handler.h"
#include "obj_Base.h"
#include "obj_Ladder.h"

#include "Font.h"

#include "Camera.h"

//handles collisions and movement
void simulate() {

    if (sf::IntRect({ 0, 0, (int)WIDTH, (int)HEIGHT }).contains(sf::Mouse::getPosition(window))) {
        Collisions::simulateAll();
        AIHelper::simulateAll();
        PlayerHelper::simulateAll();
        Camera::update(physics::dt); //0.003
        ObjectHandler::simulateAll();
    }
    
    if (EndCondition) {
        for (auto pair : PlayerHelper::list) {
            auto p = pair.second;
            p->reset(); 
            BossEvent::boss01.health = BossEvent::boss01.maxHealth;
            BossEvent::boss02.health = BossEvent::boss02.maxHealth;
            BossEvent::boss03.health = BossEvent::boss03.maxHealth;

            GateObjectHelper::list[Map::gate_boss_02_rightright]->disable();
            GateObjectHelper::list[Map::gate_boss_03_right]->disable();
        }
        EndCondition = false;
    }


    
}