#pragma once
#include "obj_Base.h"
#include "obj_Ladder.h"
#include "obj_Item.h"
#include "obj_Checkpoint.h"
#include "obj_InvisibleLayer.h"
#include "obj_Character.h"
#include "map_Base.h"

namespace ObjectHandler {

	bool riddle0, riddle1, riddle2;

	void simulateAll() {
		for (auto pair : LadderObjectHelper::list) {
			auto ladder = pair.second;

			ladder->simulate();

		}
		for (auto pair : ItemHelper::list) {
			auto item = pair.second;

			item->simulate();
		}

		for (auto pair : CheckpointHelper::list) {
			auto checkpoint = pair.second;

			checkpoint->simulate();
		}

		for (auto pair : CharacterHelper::list) {
			auto character = pair.second;

			character->simulate();

			if (character->isQuestGiver && character->isCipherSolved()) {
				switch (character->_character) {
				case bird0:
					riddle0 = true;
					break;
				case bird1:
					riddle1 = true;
					break;
				case bird2:
					riddle2 = true;
					break;
				}
				character->updateText("good job!");
			}
		}

		if (riddle0 && riddle1 && riddle2) {
			GateObjectHelper::list[Map::gate_crypto_puzzle]->disable();
			GateObjectHelper::list[Map::gate_boss_02_right]->disable();
		}
		
	}
}