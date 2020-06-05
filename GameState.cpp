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


GameState::GameState(Player& p, Map& m)
{
	localPlayer = &p;
	localMap = &m;
}
GameState::~GameState()
{
}

bool GameState::SaveToFile(uint16_t NodeID)
{
	std::string outfName = localPlayer->GetName() + ".sav";
	std::ofstream outfile(outfName);
	outfile << NodeID << '\n';
	outfile << *localPlayer;
	outfile << *localMap;
	outfile.close();
	return false;
}

bool GameState::LoadFromFile(std::string fName, uint16_t *nodeId)
{
	
	
	std::ifstream ifs(fName);
	if (!ifs.is_open())
	{
		wxMessageBox(wxT("Cannot open the file !"), wxT("Ooops!"));
		return false;
	}
	ifs >> *nodeId;
	ifs >> *localPlayer;
	ifs >> *localMap;
	ifs.close();
	
	return true;
}




