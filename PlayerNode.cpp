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

uint16_t PlayerNode::GetCombinedItemWeight()
{
	uint16_t TotalWeight = 0;
	for (auto item : ItemsInNode)
	{
		TotalWeight += item.GetWeight();
	}
	return TotalWeight;
}
