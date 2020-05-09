#include "Item.h"


Item::Item(std::string name, std::string desc, uint16_t weight, uint8_t props)
{// mainly just populating the item with values
	ID = ++ItemID;
	Name = name;
	Description = desc;
	Weight = weight;
	Properties = props;
	CurrentLocation = INVALID_LOCATION;  // needs to be set elsewhere in the game
}

Item::~Item()
{// Kill 'em all
}

bool Item::SetLocation(uint16_t loc)
{
	if(loc == INVALID_LOCATION)
		return false;
	CurrentLocation = loc;
	return true;
}

bool Item::SetProperty(uint8_t prop)
{// sets an individual property
	if (0 == prop)
		return false;
	Properties = Properties | prop;
	return true;
}
