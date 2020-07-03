///////////////////////////////////////////////////////////////////////////////
//								  GameSetup.cpp                              //
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
//    This file, along with GameSetup.h, are the two files needed in         //
//    order to create your own unique game.  The only other modification     //
//    necessary is to change the title in the constructor of the cMain       //
//    object in cMain.cpp.  All other files can be left untouched.           //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
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
	MapName = "THA.MAP";
	IniFileName = "tha.ini";
	MusicFile = "Game.wav";
	SplashImage = "Splash.png";
	TitleFont = "England.ttf";
	TitleFaceName = "England Hand DB";
	
}

GameSetup::~GameSetup()
{
}	

//  Options for items:
//	Eatable
//	Drinkable
//	Takeable
//	Droppable
//	Usable
//	Talkable
//	Killable

bool GameSetup::InitFirstRun(Map& GameMap, Player& GamePlayer)
{// allocates the default Items to the default rooms - called at the start of the game
	// NOTE:  In general, alny Item that is Takeable should also be Droppable
	AddInfoToMap(GameMap, "Sandwich", "A Cheese and pickle sandwich - slightly curled", LIGHTWEIGHT, INNER_FOYER, Eatable | Takeable | Droppable);
	AddInfoAndConversationToMap(GameMap, 
		"Lady behind the counter", 
		"A very pleasant lady in the prime of her life.  Always ready with a smile.", 
		WEIGHTLESS, 
		TIC, 
		Talkable, 
		"\n\tHello.\nLong time no see.\nWould you like me to let you into the Town Hall through the TIC?\n\n", 
		GainEntryToTownHall);
	AddInfoToMap(GameMap, "Door Button", "A metal button marked 'Open Door'", WEIGHTLESS, INNER_FOYER, Usable);
	AddInfoToMap(GameMap, "Walking stick", "A rather battered tubular metal folding walking stick", MIDDLEWEIGHT, FIRSTAID_ROOM, Usable | Takeable | Droppable, UseWalkingStick);
	AddInfoToMap(GameMap, "Sewing machine", "An old Singer treddle sewing machine", HEAVYWEIGHT, INNER_FOYER, Takeable | Droppable);
	AddInfoToMap(GameMap, "Rubbish sack", "A heavy sack of something awful", HEAVYWEIGHT, BAR_AREA, Takeable | Droppable);
	return true;
	
}

void GameSetup::AddInfoToMap(Map& theMap, 
	std::string title, 
	std::string desc, 
	uint16_t weight, 
	uint16_t location, 
	uint8_t props, 
	
	void(*func)(void* mainwin))
{
	Item* newItem = new Item(title, desc, weight,props);
	
	if (func != nullptr)
		newItem->f = func;
	theMap.PlaceItemInNode(*newItem, location);
	delete newItem;
	
}

void GameSetup::AddInfoAndConversationToMap(
	Map& theMap, 
	std::string title, 
	std::string desc, 
	uint16_t weight, 
	uint16_t location, 
	uint8_t props, 
	std::string conversation, 
	void(*func)(void* mainwin))
{
Item* newItem = new Item(title, desc, weight, props);

if (func != nullptr)
newItem->f = func;
newItem->SetConversation(conversation);
theMap.PlaceItemInNode(*newItem, location);

delete newItem;
}


void GameSetup::AddInfoToPlayer(Player& thePlayer,Map& theMap, std::string title, std::string desc, uint16_t weight, uint16_t location, uint8_t props)
{
	Item* newItem = new Item(title, desc, weight, props);
	// store in the map so the Item can be found when loading
	AddInfoToMap(theMap, title, desc, weight, props); 
	thePlayer.AddItemID(newItem->GetID());
	delete newItem;
}

std::vector<std::string> GameSetup::Prologue()
{//  Generate the story for the user
	
	std::vector<std::string> line;
	line.reserve(10);
	
	line.push_back("It is a beautiful crisp Saturday morning, around 9:23 AM\n");
	line.push_back("However, you have little time to admire the singing of the sparrows\n");
	line.push_back("\nYou have a job to do.\n\n");
	line.push_back("You are a caretaker at the Town Hall, and today your job\n");
	line.push_back("is to tidy up after last night's party and prepare the hall\n");
	line.push_back("for a wedding.  \n\nEverything must be perfect!\n\n");
	line.push_back("First things first.  You haven't got your keyfob, so you might need get a little creative ");
	line.push_back("in finding a way to get into the building\n\n");
	line.push_back("Best of luck with that.  \n\nMaybe the Tourist Information Centre can help.\n");

	return line;
}

std::vector<std::string> GameSetup::Epilogue()
{//
	std::vector<std::string> line;

	line.push_back("CONGRATULATIONS !  You completed the task.\n\n");
	line.push_back("Time for a brew and a biscuit.\n\n");
	
	return line;
}

std::vector<std::string> GameSetup::GameOver()
{
	std::vector<std::string> line;
	line.push_back("\n\n\t\t\t   GAME OVER!\n\n");
	line.push_back("\t\t        Unfortunately, you lost this time.\n\n");
	line.push_back("\t\t                     Please try again");
	return line;
}

//////////////////////////////////////////////////////////////////////////////
//  functions that are specific to each game.  Used as function pointers passed
// to AddItemToMap calls as optional function pointers.  Must return void and accept no arguments
//////////////////////////////////////////////////////////////////////////////



void UseWalkingStick(void* mainwin)
{
	cMain* c = (cMain*)mainwin;
	c->PlaySFX("weird.wav");
	c->FlashPanel();
	
	c->ClearDesc();
	c->AddToDesc("\nYou lean on the walking stick,\nIt breaks, leaving you looking foolish on the floor\n\n");
	

	c->AddToDesc("Ouch!\n\n");
	Player* p = c->GetPlayer();
	p->RemoveHealth(15);
	
	c->WaitForAnyKey();
		
	
}

void TriggerGhosts(void* mainwin)
{
	cMain* c = (cMain*)mainwin;
	
	c->PlaySFX("weird.wav");
	c->FlashPanelBlack();
	c->AddToDesc("\nYou lean on the walking stick,\nIt breaks, leaving you looking foolish on the floor\n\n");


	c->AddToDesc("Ouch!\n\n");
	Player* p = c->GetPlayer();
	p->RemoveHealth(15);

	c->WaitForAnyKey();


}

void GainEntryToTownHall(void* mainwin)
{ // this function alters the map to allow a door to open
	cMain* c = (cMain*)mainwin;
	// the current MapNode needs it's first exit opening
	c->EnableCurrentMapNodeExit(0, OUTER_FOYER);
	c->Refresh();
	
}
