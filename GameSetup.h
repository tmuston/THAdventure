#pragma once
#include "GameObjects.h"
#include "MapNode.h"
#include "map.h"

class GameSetup
{// create all the items, and place them in their initial positions
 // This should be the only file that needs modifying for future games
 // there should be exactly one GameObjects object per game
public:
	GameSetup();
	~GameSetup();
	bool InitFirstRun();
	bool InitFromSavedGame(GameObjects& game, std::string fName);
private:
	GameObjects* gamestate = nullptr;
	Item* thing = nullptr;

};

