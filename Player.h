#ifndef PLAYER_H
#define PLAYER_H
///////////////////////////////////////////////////////////////////////////////
//								  Player.h                                   //
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
//    This file declares the game player attributes.                         //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <vector>
//#include "cMain.h"
#include "Item.h"
#include "Map.h"
#include "PlayerNode.h"

class cMain;  // forward declaration so that ProcessItemAction can use the cMain object

class Player
{
public:
	Player(std::string name);
	~Player();
	inline void SetName(const std::string& name) { PlayerName = name; }
	inline std::string GetName() { return PlayerName;  }
	inline uint16_t GetWeight() { return weight; }
	inline uint16_t GetHealth() { return health; }
	uint16_t GetItemIdFromName(std::string str);
	bool ProcessItemAction(cMain* mainwin,  uint16_t id, const std::string& action_string, uint16_t possible_actions);
	inline void SetMap(Map* m) { PlayerMap = m; }
	inline Map* GetMap() { return PlayerMap; }
	inline void SetWeight(uint16_t w) { weight = w; }
	inline void SetHealth(uint16_t h) { health = h; }
	void AddHealth(uint16_t h);
	uint16_t RemoveHealth(uint16_t h);
	void AddItemID(const uint16_t& itemID);
	bool RemoveItemID(const uint16_t& itemID);
	friend std::ostream& operator << (std::ostream& out, const Player& obj);
	friend std::istream& operator>>(std::istream& is, Player& p);
	PlayerNode pNode;  // an abbreviated version of MapNode, to store items carried by the player
	std::vector<std::tuple<uint16_t, uint16_t>> vPlayerItemInfo; // stores the ID and action for
	// each Item carried by the player.  Used by the player listbox and action button.
private:
	std::string PlayerName = "<No Name>";
	Map* PlayerMap = nullptr;
	uint16_t location = 0;
	uint16_t weight = 0;	// probably rarely used, unless you want to make a game where 
							// the player can collapse a floor or similar
	uint16_t health = 100;	// decreases over time if the player doesn't eat or drink
	std::vector<uint16_t> CarriedItemIDs;
	
	
};
#endif // PLAYER_H

