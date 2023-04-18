#pragma once
#include "obj_Base.h"
#include "obj_Ladder.h"

namespace ObjectHandler {

	void simulateAll() {
		for (auto pair : LadderObjectHelper::list) {
			auto ladder = pair.second;

			ladder->simulate();

		}
	}
}