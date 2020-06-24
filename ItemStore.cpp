#include "ItemStore.h"

ItemStore::ItemStore()
{
}

ItemStore::~ItemStore()
{  // destructor - obviously
}

bool ItemStore::Add(Item& newitem)
{
	uint16_t id = newitem.GetID();
	for (auto theItem : AllItems)
	{
		if (theItem.GetID() == id)  // already there, don't add
			return false;
	}
	AllItems.push_back(newitem);

	return true;
}

bool ItemStore::Remove(Item& item)
{
	uint16_t id = item.GetID();
	uint16_t uCount = 0;
	for (auto theItem : AllItems)
	{
		if (theItem.GetID() == id)  
		{
			AllItems.erase(AllItems.begin() + uCount);
			return true;
			uCount++;
		}
	}
	return false;
}

Item ItemStore::Get(uint16_t ID)
{
	for (auto theItem : AllItems)
	{
		if (theItem.GetID() == ID)
		{
			return theItem;
		}
	}
	
}
