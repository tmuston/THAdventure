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
class Player
{
public:
	Player(std::string name);
	~Player();
	inline std::string GetName() { return PlayerName;  }
	inline uint16_t GetWeight() { return weight; }
	inline uint16_t GetHealth() { return health; }

	inline void SetWeight(uint16_t w) { weight = w; }
	inline void SetHealth(uint16_t h) { health = h; }
private:
	std::string PlayerName = "<No Name>";
	uint16_t weight = 0;	// probably rarely used, unless you want to make a game where 
							// the player can collapse a floor or similar
	uint16_t health = 100;	// decreases over time if the player doesn't eat or drink
	std::vector<Item> CarriedItems;

};
#endif // PALYER_H

