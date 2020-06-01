///////////////////////////////////////////////////////////////////////////////
//								  Item.cpp                                   //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                       Part of the EGM cross-platform                      //
//                         Text adventure game engine                        //
//                       Copyright (c)  Tim Muston 2020                      //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//    Released as open source under the GPL license (See license.txt)        //
//                                                                           //
//    This file defines the properties of the Items which are usable         //
//    within the game.  Note that the items themselves are declared and      //
//    defined within GameSetup.h and GameSetup.cpp.                          //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
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

Item::Item(const Item& i)
{ // copy constructor
	ID = i.ID;
	Name = i.Name;
	Description = i.Description;
	Weight = i.Weight;
	Properties = i.Properties;
	Conversation = i.Conversation;
	CurrentLocation = i.CurrentLocation;
}

Item::~Item()
{// Kill 'em all
}

bool Item::SetLocation(uint16_t loc)
{
	if (loc == INVALID_LOCATION)
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