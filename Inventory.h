#pragma once
#include "ui_Inventory.h"

namespace Inventory {

	InventoryItem currentyEquippedItem;
	std::map<InventoryItem, bool> unlockedItemList = { {InventoryItem::DOSGUN, true},{InventoryItem::PORTGUN, false}, {InventoryItem::CRYPTOGUN, false},{InventoryItem::BRUTEFORCE, false} };

	bool equipItem(InventoryItem item) {
		std::map<InventoryItem, bool>::iterator it = unlockedItemList.find(item);
		if (it != unlockedItemList.end() && it->second == true) {
			currentyEquippedItem = item;
			return true;
		}
		return false;
	}

	InventoryItem getEquippedItem() {
		return currentyEquippedItem;
	}

	void unlockItem(InventoryItem item) {
		std::map<InventoryItem, bool>::iterator it = unlockedItemList.find(item);
		if (it != unlockedItemList.end()) {
			it->second = true;
		}
	}
}