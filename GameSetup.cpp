#include "GameSetup.h"

// various rooms

#define ENTRANCE		1 
#define	TIC				2
#define	OUTER_FOYER		3
#define INNER_FOYER		4
#define FIRSTAID_ROOM	5
#define	LOWER_STAIRS	6
#define	UPPER_STAIRS	7
#define BOGS_CORRIDOR	8
#define FRONT_BOGS		9
#define FRONT_DISABLED	10
#define BAR_AREA		11
#define MAIN_HALL		12
#define	TOP_CORRIDOR	13

// weights of carryable objects
#define WEIGHTLESS		0  // things that can't be picked up.
#define LIGHTWEIGHT		2
#define MIDDLEWEIGHT	4
#define HEAVYWEIGHT		6


GameSetup::GameSetup()
{// constructor
}

GameSetup::~GameSetup()
{
}

bool GameSetup::InitFirstRun(Map& GameMap)
{// allocates the default Items to the default rooms - called at the start of the game
	AddInfoToMap(GameMap, "Sandwich", "A shiny tool", LIGHTWEIGHT, INNER_FOYER, Movable | Carryable | Usable | Eatable);
	AddInfoToMap(GameMap, "Lady behind the counter", "A very pleasant lady in the prime of her life.  Always ready with a smile.", WEIGHTLESS, TIC, Talkable);
	AddInfoToMap(GameMap, "Door Button", "A metal button marked 'Open Door'", WEIGHTLESS, INNER_FOYER, Usable);
	AddInfoToMap(GameMap, "Walking stick", "A rather battered tubular metal folding walking stick", MIDDLEWEIGHT, FIRSTAID_ROOM, Usable | Carryable);
	return true;
}

void GameSetup::AddInfoToMap(Map& theMap, std::string title, std::string desc, uint16_t weight, uint16_t location, uint8_t props)
{
	Item* newItem = new Item(title, desc, weight,props);
	theMap.PlaceItemInNode(*newItem, location);
	delete newItem;
	
}

//bool GameSetup::InitFromSavedGame(GameObjects& game, std::string fName)
//{
//	return false;
//}
