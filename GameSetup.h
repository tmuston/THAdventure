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
#include "map.h"
#include "BuildOptions.h"
//#include "cMain.h"

class GameSetup
{// create all the items, and place them in their initial positions
 // This should be the only file that needs modifying for future games
 // there should be exactly one GameObjects object per game
public:
	GameSetup();
	~GameSetup();
	bool InitFirstRun(Map& GameMap);
	void AddInfoToMap(Map& theMap, std::string title, std::string desc, uint16_t weight, uint16_t location, uint8_t props = 0);
	inline std::string GetSplashImage() { return SplashImage; }
	inline std::string GetMusicFile() { return MusicFile; }
	inline std::string GetMapName() { return MapName; }
	inline std::string GetIniFileName() { return IniFileName; }
	inline std::string GetTitleFont() { return TitleFont; }
	inline std::string GetTitleFaceName() { return TitleFaceName; }
	std::vector<std::string> Prologue();//  these two functions need to be re-engineered so as to not require cMain pointers
	std::vector<std::string> Epilogue();
	//bool InitFromSavedGame(GameObjects& game, std::string fName);
private:
	std::string SplashImage; //  both of thses strings need to be set in the constructor
	std::string MusicFile;
	std::string MapName;
	std::string GameTitle;
	std::string IniFileName;
	std::string TitleFont;
	std::string TitleFaceName;
};
#endif // GAMESETUP_H
