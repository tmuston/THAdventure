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
//    Released as open source under the GPL license (See license.txt)        //
//                                                                           //
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
	
	//bool MakeNodeSection();
	/*std::string PlayerName = "";
	uint16_t PlayerWeight = 0;
	uint16_t PlayerHealth = 0;
	std::vector<uint16_t> PlayerItemIDs;
	std::string PlayerSection = "";
	std::string NodeSection = "";*/
	Player* localPlayer = nullptr;
	Map* localMap = nullptr;
};
#endif //GAMESTATE_H

