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
//    Released as open source under the GPL license (See license.txt)        //
//                                                                           //
//    This file, along with GameSetup.cpp, are the two files needed in       //
//    order to create your own unique game.  The only other modification     //
//    necessary is to change the title in the constructor of the cMain       //
//    object in cMain.cpp.  All other files can be left untouched.           //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////


#include "wx/wx.h"
#include "wx/utils.h"
#include <iostream>
#include "map.h"
#include "BuildOptions.h"
//#include <functional>
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
		
		//void(*func)(std::string msg) = nullptr);
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
	std::vector<std::string> Prologue();
	std::vector<std::string> Epilogue();
	
private:
	std::string SplashImage; 
	std::string MusicFile;
	std::string MapName;
	std::string GameTitle;
	std::string IniFileName;
	std::string TitleFont;
	std::string TitleFaceName;

	
	
};
//////////////////////////////////////////////////////////////////////////////
// functions that are specific to each game.  Used as function pointers passed
// to AddItemToMap calls as optional function pointers.  Must return void and accept no arguments
//////////////////////////////////////////////////////////////////////////////

void UseWalkingStick(void* mainwin);

#endif // GAMESETUP_H
