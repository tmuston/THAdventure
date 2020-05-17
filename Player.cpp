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
{// will need to checkthat some dweeb hasn't initialised name to NULL 
	if((name != ""))
		PlayerName = name;
}

Player::~Player()
{
}
