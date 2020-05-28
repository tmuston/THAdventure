///////////////////////////////////////////////////////////////////////////////
//								  GameState.cpp                                //
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
//    This file defines a GameState object, which is used as an area to      //         
//    store any configuration changes as a delta from the original state     //
//    Also handles loading and saving of game (.sav) files                   //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
#include "GameState.h"

GameState::GameState()
{
}

GameState::~GameState()
{
}

bool GameState::SaveToFile(std::string fName)
{
	return false;
}

bool GameState::LoadFromFile(std::string fName)
{
	return false;
}

bool GameState::MakePlayerSection( Player& pl)
{//  get the player name, health, weight and IDs of any carried items, and put them into a string
 // all uint16_t data should be stored as 4 bytes of hexadecimal
	std::stringstream stream;
	stream << "/pl/" << pl.GetName() << "/" << std::hex << std::setfill('0') << std::setw(4) << pl.GetHealth() << std::hex << std::setfill('0') << std::setw(4) << pl.GetWeight() << "/pl/";
	
	return false;
}
