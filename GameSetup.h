#ifndef GAMESETUP_H
#define GAMESETUP_H
///////////////////////////////////////////////////////////////////////////////
//								  GameSetup.h                                //
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
//    This file, along with GameSetup.cpp, are the two files needed in       //
//    order to create your own unique game.  The only other modification     //
//    necessary is to change the title in the constructor of the cMain       //
//    object in cMain.cpp.  All other files can be left untouched.           //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////


#include "wx/wx.h"
#include "wx/stdpaths.h"
#include "wx/filename.h"
#include "wx/utils.h"
#include <iostream>
#include "Map.h"
#include "BuildOptions.h"
#include "Player.h"  // in some games, you might want to give the player some initial items - if you're a wuss
#include "cMain.h"



class GameSetup
{// create all the items, and place them in their initial positions
 // This should be the only file that needs modifying for future games
 // there should be exactly one GameObjects object per game
public:
	GameSetup();
	~GameSetup();
	bool InitFirstRun(Map& GameMap, Player& GamePlayer);
	void AddInfoToMap(Map& theMap, 
		std::string title, 
		std::string desc, 
		uint16_t weight, 
		uint16_t location, 
		uint8_t props = 0, 
		void(*func)(void* mainwin) = nullptr,
		bool KeepAfterUse = false);

	void AddInfoAndConversationToMap(Map& theMap,
		std::string title,
		std::string desc,
		uint16_t weight,
		uint16_t location,
		uint8_t props = 0,
		std::string conversation = nullptr,
		void(*func)(void* mainwin) = nullptr);

	void AddInfoToPlayer(Player& thePlayer,Map& theMap, std::string title, std::string desc, uint16_t weight, uint16_t location, uint8_t props = 0);
	inline std::string GetSplashImage() { return SplashImage; }
	inline void SetMap(Map* m) { gmap = m; }
	Map* gmap = nullptr;
	inline std::string GetMusicFile() { return MusicFile; }
	inline std::string GetMapName() { return MapName; }
	inline std::string GetIniFileName() { return IniFileName; }
	inline std::string GetTitleFont() { return TitleFont; }
	inline std::string GetTitleFaceName() { return TitleFaceName; }
	inline std::string GetGameTitle() { return GameTitle; }
	std::vector<std::string> Prologue();
	std::vector<std::string> Epilogue();
	std::vector<std::string> GameOver();
	
private:
	std::string SplashImage = "";
	std::string MusicFile = "";
	std::string MapName = "";
	std::string GameTitle = "";
	std::string IniFileName = "";
	std::string TitleFont = "";
	std::string TitleFaceName = "";

	
	
};
//////////////////////////////////////////////////////////////////////////////
// functions that are specific to each game.  Used as function pointers passed
// to AddItemToMap or AddItemAndConversationToMap calls as optional 
// function pointers.  Must return void and accept only a void*, which the function
// then casts to a cMain*
//////////////////////////////////////////////////////////////////////////////

void UseWalkingStick(void* mainwin);
void TriggerGhosts(void* mainwin);
void GainEntryToTownHall(void* mainwin);
void PressFrontDoorButton(void* mainwin);
void AssembleVacuum(void* mainwin);
void UseKey(void* mainwin);
void EatFood(void* mainwin);
void Drink(void* mainwin);

void BoyConversation1(void* mainwin);
void BoyConversation2(void* mainwin);
void BoyConversation3(void* mainwin);
void DariusConversation(void* mainwin);

#endif // GAMESETUP_H
