#ifndef PLAYERNODE_H
#define PLAYERNODE_H
///////////////////////////////////////////////////////////////////////////////
//								  PlayerNode.h                               //
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
//    This file declares the PlayerNode. which can be thought of as the      //
//    Player equivalent to the MapNode class.                                //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
#include <vector>
#include "Item.h"
#include "MapNode.h"

class PlayerNode
{
public:
	PlayerNode();
	~PlayerNode();
	bool AddItem(const Item& item);
	bool DropItem(Item& item);
	inline uint16_t GetNumItems() { return numItems; }
	uint16_t GetActions(uint16_t id);
	uint16_t GetCombinedItemWeight();
	std::vector<Item> ItemsInNode;
private:
	uint16_t numItems;
	

};

#endif // PLAYERNODE_H