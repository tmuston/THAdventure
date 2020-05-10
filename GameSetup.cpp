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

bool GameSetup::InitFirstRun()
{// allocates the default Items to the default rooms - called at the start of the game
	// test code for Items
	
	std::unique_ptr<GameObjects> gObj(new GameObjects());
	Item* newItem = new Item("Sandwich", "A shiny tool", LIGHTWEIGHT, Movable | Carryable | Usable | Eatable);
	newItem->SetLocation(INNER_FOYER);
	gObj->AddItem(*newItem);	
	delete newItem;

	newItem = new Item("Lady behind the counter", "A very pleasant lady in the prime of her life.  Always ready with a smile.", WEIGHTLESS, Talkable);
	newItem->SetLocation(TIC);
	gObj->AddItem(*newItem);
	delete newItem;

	newItem = new Item("Door Button", "A metal button marked 'Open Door'", WEIGHTLESS, Usable);
	newItem->SetLocation(INNER_FOYER);
	gObj->AddItem(*newItem);
	delete newItem;

	newItem = new Item("Walking stick", "A rather battered tubular metal folding walking stick", MIDDLEWEIGHT, Usable | Carryable);
	newItem->SetLocation(INNER_FOYER);
	gObj->AddItem(*newItem);
	delete newItem;
		
	return true;
}

bool GameSetup::InitFromSavedGame(GameObjects& game, std::string fName)
{
	return false;
}
