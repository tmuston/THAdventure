///////////////////////////////////////////////////////////////////////////////
//								  Player.cpp                                 //
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
//    This file defines the game player attributes.                          //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
#include "Player.h"



Player::Player(std::string name)
{// will need to check that some dweeb hasn't initialised name to NULL 
	
	if((name != ""))
		PlayerName = name;
}

Player::~Player()
{
}



uint16_t Player::GetItemIdFromName(std::string str)
{// this function is passed a std::string with the command, a space and then the name
 //  and to return the ID we need to strip the command and space, and then search for the ID
 //  Say it quickly, and it sounds easy.
	uint16_t item = INVALID_ITEM;  // if the item can't be found, this will get returned
	size_t size = str.std::string::find_first_of(" ");  // finds the space after the action to be performed
	std::string sSubstring = str.substr(size + 1);
	for (size_t i = 0; i < pNode.ItemsInNode.size(); i++)
	{
		if (pNode.ItemsInNode[i].GetName() == sSubstring) //  Hurray!  We've found it
		{
			item = pNode.ItemsInNode[i].GetID();
			break;
		}
	}
	return item;
}

bool Player::ProcessItemAction(cMain* mainwin,uint16_t id, const std::string& action_string, uint16_t possible_actions)
{// process the item given by ID with the action mentioned in action_string 
   // if that action is allowed for that item
	
	uint16_t tmpAction = 0;
	if (action_string == "Eat")
		tmpAction = Eatable; //1
	else
	if (action_string == "Drink")
		tmpAction = Drinkable;  //2
	else
	
	if (action_string == "Drop")
		tmpAction = Droppable;  //8
	else
	if (action_string == "Use")
		tmpAction = Usable;  //16
	
	std::vector<Item>::iterator it;
	uint16_t found = 0;
	for (it = pNode.ItemsInNode.begin(); it != pNode.ItemsInNode.end(); ++it)
	{
		uint16_t x = pNode.ItemsInNode[found].GetID();
		if (x == id)
		{
			break;
		}
		found++;
	}
	void(*function)(void* mainwin);//  this function pointer sends a pointer to cMain back to GameSetup.
	if(tmpAction & possible_actions)
	{//  Now we have the Item ID and the action.  

		std::string conv;
		switch (tmpAction)
		{
		case Eatable:// remove from MapNode and increment health
			RemoveItemID(id);
			pNode.DropItem(pNode.ItemsInNode[found]);
			
			AddHealth(10);
			
			break;

		case Drinkable:
			RemoveItemID(id);
			pNode.DropItem(pNode.ItemsInNode[found]);
			
			AddHealth(20);
			break;
		
		case Usable:
			function = pNode.ItemsInNode[found].f;

			if (function)
			{
				function(mainwin);
				RemoveItemID(id);
				pNode.DropItem(pNode.ItemsInNode[found]);

			}
			break;
		case Droppable:
			RemoveItemID(id);
			pNode.DropItem(pNode.ItemsInNode[found]);
			break;
		
		default: //should never happen
			wxMessageBox("Invalid Item option", "This is embarrassing");
			break;
		}

	}
	else
		return false;

	return true;
}

void Player::AddHealth(uint16_t h)
{
	if (health < 100)  // maximum
		health += h;
	if (health > 100)
		health = 100; // so health can never exceed 100
}

uint16_t Player::RemoveHealth(uint16_t h)
{
	health -= h;
	
	return health; // so that the caller can check if we're dead
}

void Player::AddItemID(const uint16_t& itemID)
{
	CarriedItemIDs.push_back(itemID);
	Map* m = GetMap();
	// search the Map's individual MapNodes for Items that match ItemID.
	// there will only be one match or less
	uint16_t uMapSize = m->GetMapSize();
	for (auto i = 0; i < uMapSize; i++)
	{
		if (m->NodesInMap[i].ItemsInNode.size() > 0)
		{ // found a node that contains Items
			MapNode mn = m->NodesInMap[i];
			
			for(uint16_t j = 0; j < static_cast<uint16_t>(mn.ItemsInNode.size()); j++)
			{
				if (mn.ItemsInNode[j].GetID() == itemID)  
				{
					Item item = mn.ItemsInNode[j];
					pNode.AddItem(item);
				}
			}
		}
	}
}

bool Player::RemoveItemID(const uint16_t& itemID)
{
	//uint16_t id = item.GetID();
	uint16_t id = itemID;
	// iterate through the CarriedItems vector to see if the required item is present
	int iCount = 0;
	std::vector<uint16_t>::iterator it;
	for (it = CarriedItemIDs.begin(); it != CarriedItemIDs.end(); ++it)
	{
		if (*it == id)  //  found the item to kill
		{
			CarriedItemIDs.erase(CarriedItemIDs.begin() + iCount);
			return true;
		}
		iCount++;
	}
	return false;
}
std::ostream& operator << (std::ostream& out, const Player& obj)
{
	out << obj.PlayerName
		<< '\n' << obj.health
		<< '\n' << obj.weight;

	size_t iCount = obj.CarriedItemIDs.size();
	if (iCount > 0)  // we have at least one item
	{
		for (size_t i = 0; i < iCount; i++)
		{
			
			uint16_t ItemID = obj.CarriedItemIDs[i];
			out << '\n' << ItemID;
		}
	}
	

	out << "\n/p";  // end of player section

	return out;
}
std::istream& operator>>(std::istream& is, Player& p)  //load
{
	std::string delimiter;  // this gets thrown away
	// read in individual members of p
	std::string name;
	std::getline(is, name);  // don't understand why I always have to call Getline twice
	std::getline(is, name);
	p.PlayerName = name;
	is >> p.health >> p.weight;
		
	is >> delimiter;  // if no carried items, will be  "/p"
	
	while (delimiter != "/p")
	{
		// need to somehow get the required item, check that it's not already there, and if not, add it.
		uint16_t ItemID = std::stoi(delimiter);
		
		p.AddItemID(ItemID);
		is >> delimiter;
	}
	return is;
}
