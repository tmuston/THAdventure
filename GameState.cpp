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
//    This file defines a GameState object, which is used as an area to      //         
//    store any configuration changes as a delta from the original state     //
//    Also handles loading and saving of game (.sav) files                   //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
#include "GameState.h"
#include "wx/stdpaths.h"
#include "wx/filename.h"


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
	wxString DataPath = wxStandardPaths::Get().GetUserLocalDataDir();
	std::string outfName = DataPath.ToStdString() + "\\" + localPlayer->GetName() + ".sav";
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




