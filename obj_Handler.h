#pragma once
#include "obj_Base.h"
#include "obj_Ladder.h"
#include "obj_Item.h"
#include "obj_Checkpoint.h"

namespace ObjectHandler {

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
	}
}