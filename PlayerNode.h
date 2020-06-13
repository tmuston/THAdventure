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
//    Released as open source under the GPL license (See license.txt)        //
//                                                                           //
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
private:
	uint16_t numItems;
	std::vector<Item> ItemsInNode;

};

#endif // PLAYERNODE_H