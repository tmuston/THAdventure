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
//    Released as open source under the GPL license (See license.txt)        //
//                                                                           //
//    This file declares the game player attributes.                         //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <vector>
#include "Item.h"
#include "Map.h"
#include "PlayerNode.h"

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
	bool ProcessItemAction(uint16_t id, const std::string& action_string, uint16_t possible_actions);
	inline void SetMap(const Map& m) { PlayerMap = m; }
	inline Map& GetMap() { return PlayerMap; }
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
	Map PlayerMap;
	uint16_t location = 0;
	uint16_t weight = 0;	// probably rarely used, unless you want to make a game where 
							// the player can collapse a floor or similar
	uint16_t health = 100;	// decreases over time if the player doesn't eat or drink
	std::vector<uint16_t> CarriedItemIDs;
	
	
};
#endif // PLAYER_H

