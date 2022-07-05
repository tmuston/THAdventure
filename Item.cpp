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
//    Released as open source under the GPL v3 license (See COPYING file)    //  
//    This program is free software: you can redistribute it and/or modify   //
//    it under the terms of the GNU General Public License as published by   //
//    the Free Software Foundation, either version 3 of the License, or      //
//    (at your option) any later version.                                    //
//                                                                           //
//    This program is distributed in the hope that it will be useful,        //
//    but WITHOUT ANY WARRANTY; without even the implied warranty of         //
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the            //
//    GNU General Public License for more details.                           //
//                                                                           //
//    You should have received a copy of the GNU General Public License      //
//    along with this program.If not, see < https://www.gnu.org/licenses/>.  //
//                                                                           //
//                     Tim Muston  tim@tmuston.co.uk                         //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
//                                                                           //                                                                           //
//    This file defines the properties of the Items which are usable         //
//    within the game.  Note that the items themselves are declared and      //
//    defined within GameSetup.h and GameSetup.cpp.                          //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
#include "Item.h"

Item::Item()
{
}

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
	f = i.f;
	KeepItemAfterUse = i.KeepItemAfterUse;
	
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

void ZeroItemID()
{
	ItemID = 0;
}
