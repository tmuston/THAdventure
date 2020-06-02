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

void Player::AddItem(const Item& item)
{
	CarriedItems.push_back(item);
}

bool Player::RemoveItem(const Item& item)
{
	//uint16_t id = item.GetID();
	Item lItem = item;
	uint16_t id = lItem.GetID();
	// iterate through the CarriedItems vector to see if the required item is present
	int iCount = 0;
	std::vector<Item>::iterator it;
	for (it = CarriedItems.begin(); it != CarriedItems.end(); ++it)
	{
		if (it->GetID() == id)  //  found the item to kill
		{
			CarriedItems.erase(CarriedItems.begin() + iCount);
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

	size_t iCount = obj.CarriedItems.size();
	if (iCount > 0)  // we have at least one item
	{
		for (size_t i = 0; i < iCount; i++)
		{
			Item theItem = obj.CarriedItems[i];
			uint16_t ItemID = theItem.GetID();
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
	size_t iCount = 0;
	while (delimiter != "/p")
	{
		// need to somehow get the required item, check that it's not already thee, and if not, add it.
		uint16_t ItemID;
		is >> delimiter;
		iCount++;
	}
	return is;
}
