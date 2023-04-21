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

#include "mini_Base.h"

#include "obj_Handler.h"
#include "obj_Base.h"
#include "obj_Ladder.h"

#include "Font.h"

#include "Camera.h"



//handles collisions and movement
void simulate() {
    Collisions::simulateAll();
    AIHelper::simulateAll();
    PlayerHelper::simulateAll();
    Camera::update(physics::dt); //0.003
    ObjectHandler::simulateAll();
    if (EndCondition) {
        for (auto pair : PlayerHelper::list) {
            auto p = pair.second;
            p->reset(); 
        }
        EndCondition = false;
    }


    
}