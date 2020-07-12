#ifndef GAMESTATE_H
#define GAMESTATE_H
///////////////////////////////////////////////////////////////////////////////
//								  GameState.h                                //
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
//    This file declares a GameState object, which is used as an area to     //         
//    store any configuration changes as a delta from the original state     //
//    Also handles loading and saving of game (.sav) files                   //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#include "wx/wx.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <sstream>
#include "Player.h"

#include "Map.h"

class GameState
{// this class  handles any changes to the state of the MapNode and Item objects from
 // their original states.  It also handles load and save.
public:
	GameState(Player& p, Map& m);
	~GameState();
	bool SaveToFile( uint16_t NodeID);
	bool LoadFromFile(std::string fName, uint16_t* nodeId);
	
private:
	
	
	Player* localPlayer = nullptr;
	Map* localMap = nullptr;
};
#endif //GAMESTATE_H

