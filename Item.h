#ifndef ITEM_H
#define ITEM_H
///////////////////////////////////////////////////////////////////////////////
//								  Item.h                                     //
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
//    This file declares the properties of the Items which are usable        //
//    within the game.  Note that the items themselves are declared and      //
//    defined within GameSetup.h and GameSetup.cpp.                          //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#include "wx/wx.h"
//#include "Map.h"
//#include "cMain.h"
#include <iostream>


static uint16_t ItemID = 0;

enum ItemProperty
{
	Eatable		= 1,
	Drinkable	= 2,
	Takeable	= 4,
	Droppable	= 8,
	Usable		= 16,
	Talkable	= 32,
	Killable	= 64,
};

#define INVALID_LOCATION 65535
#define CARRIED_BY_PLAYER 0
#define INVALID_ITEM 65535
#define MAXWEIGHT 10
void ZeroItemID();
class Item
{
public:
	Item();
	Item(std::string name, std::string desc, uint16_t weight, uint8_t props = 0);
	Item(const Item& i);
	~Item();
	inline std::string GetName() { return Name; }
	inline uint16_t GetID() { return ID; }
	inline void SetID(uint16_t id) { ID = id; }
	inline uint16_t GetWeight() { return Weight; }
	inline std::string GetDescription() { return Description; }
	inline uint16_t GetLocation() { return CurrentLocation; }
	bool SetLocation(uint16_t loc);
	inline uint8_t GetProperties() { return Properties; }  // get all properties
	
	inline std::string GetConversation() { return Conversation; }
	inline void SetConversation(std::string conv) { Conversation = conv; }

	bool SetProperty(uint8_t prop);
	// function pointer for use. take, kill etc.
	void(*f)(void* mainwin) = nullptr;
	
private:
	uint16_t ID = 0;  // set in the constructor
	std::string Name;
	std::string Description;
	// not really weight, but needed because there needs to be a means of not 
	// allowing the player to carry every item - a weight limit, like at the airport
	uint16_t Weight = 0; 
	uint8_t Properties = 0;
	std::string Conversation = "";
	// Which room is the item currently in (zero means it's being carried by the player)
	uint16_t CurrentLocation = 0;
	

};
#endif // ITEM_H
