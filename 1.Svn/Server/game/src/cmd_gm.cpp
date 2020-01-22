//Find in : ACMD(do_item)
		iCount = MINMAX(1, iCount, ITEM_MAX_COUNT);
		
///Change
		iCount = MAX(1, abs(iCount));
		
//Find
	LPITEM item = ITEM_MANAGER::instance().CreateItem(dwVnum, iCount, 0, true);

	if (item)
	{
		....
		....
		....
	}
	else
	{
		ch->ChatPacket(CHAT_TYPE_INFO, "#%u item not exist by that vnum.", dwVnum);
	}
	
///Change All
	while (iCount > 0) {
		const auto& item = ITEM_MANAGER::instance().CreateItem(dwVnum, iCount, 0, true);
		if (!item) {
			ch->ChatPacket(CHAT_TYPE_INFO, "#%u item not exist by that vnum.", dwVnum);
			return;
		}
		const auto iEmptyPos = item->IsDragonSoul() ? ch->GetEmptyDragonSoulInventory(item) : ch->GetEmptyInventory(item->GetSize());
		if (iEmptyPos == -1) {
			ch->ChatPacket(CHAT_TYPE_INFO, "Not enough %s space.", item->IsDragonSoul() ? "dragonsoul" : "inventory");
			ITEM_MANAGER::instance().DestroyItem(item);
			return;
		}
		item->AddToCharacter(ch, TItemPos(item->IsDragonSoul() ? DRAGON_SOUL_INVENTORY : INVENTORY, iEmptyPos));
		LogManager::instance().ItemLog(ch, item, "GM", item->GetName());
		iCount -= item->IsStackable() ? ITEM_MAX_COUNT : 1;
	}