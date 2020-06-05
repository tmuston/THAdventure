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
//    Released as open source under the GPL license (See license.txt)        //
//                                                                           //
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

void Player::AddItemID(const uint16_t& itemID)
{
	CarriedItemIDs.push_back(itemID);
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
std::istream& operator>>(std::istream& is, Player& p)
{
	std::string delimiter;  // this gets thrown away
	// read in individual members of p
	is >> p.PlayerName >> p.health >> p.weight;
		
	is >> delimiter;  // if no carried items, will be  "/p"
	
	while (delimiter != "/p")
	{
		// need to somehow get the required item, check that it's not already there, and if not, add it.
		uint16_t ItemID = std::stoi(delimiter);
		p.CarriedItemIDs.push_back(ItemID);
		is >> delimiter;
	}
	return is;
}
