///////////////////////////////////////////////////////////////////////////////
//								  PlayerNode.cpp                             //
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
//    This file defines the PlayerNode. which can be thought of as the       //
//    Player equivalent to the MapNode class.                                //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
#include "PlayerNode.h"

PlayerNode::PlayerNode()
{
	numItems = 0;
}

PlayerNode::~PlayerNode()
{
}

bool PlayerNode::AddItem(const Item& item)
{
	ItemsInNode.push_back(item);
	numItems++;
	return true;
}

bool PlayerNode::DropItem(Item& item)
{
	for (std::vector<Item>::iterator it = ItemsInNode.begin(); it != ItemsInNode.end(); ++it)
	{
		if (it->GetID() == item.GetID())
		{
			ItemsInNode.erase(it);
			numItems--;
			return true;
		}
	}
	return false;

}

uint16_t PlayerNode::GetActions(uint16_t id)
{
	uint16_t uActions = 0;

	for (auto item : ItemsInNode)
	{
		if (item.GetID() == id)
			return item.GetProperties();
	}
	return uActions;
}
