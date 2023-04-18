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



//handles collisions and movement
void simulate() {
    
    if (!EndCondition) {
        Collisions::simulateAll();
        AIHelper::simulateAll();
        PlayerHelper::simulateAll();
        ObjectHandler::simulateAll();
    }
    else {
        Collisions::simulateAll();
        
    }


    
}