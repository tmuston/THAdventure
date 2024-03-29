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
//    This file, along with GameSetup.h, are the two files needed in         //
//    order to create your own unique game.                                  //
//    All other files can be left untouched.                                 //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
#include "GameSetup.h"
#include <cstdlib>

// various rooms
enum
{
	ENTRANCE = 1,	
	TIC,	
	OUTER_FOYER,		
	INNER_FOYER,		
	FIRSTAID_ROOM,	
	LOWER_STAIRS,	
	UPPER_STAIRS,	
	BOGS_CORRIDOR,	
	FRONT_BOGS,		
	FRONT_DISABLED,	
	BAR_AREA,		
	MAIN_HALL,		
	TOP_CORRIDOR,
	TOP_CORRIDOR_STEPS,
	BALCONY_TOP,
	LIFT_ROOM,
	KITCHEN,
	BALCONY_WEST,
	BALCONY_EAST,
	UPSTAIRS_BOG,
	LIFT_FLOOR_2,
	REAR_STAIRCASE,
	LOADING_BAY,
	REAR_STORE,
	MAIN_BOG_CORRIDOR,
	MAIN_GENTS,
	MAIN_LADIES,
	MAIN_BOG_CORRIDOR_STEPS,
	DUMPING_GROUND,
	REAR_ENTRANCE_CORRIDOR,
	REAR_OFFICE_STAIRCASE,
	REAR_OFFICE_CORRIDOR,
	CLOCK_TOWER,
	MAGISTRATES_COURT,
	MAGISTRATES_CHAMBER,
	OLD_CORRIDOR,
	OLD_STONE_STEPS,
	OLD_STAIRCASE,
	OLD_STAIRCASE_BOTTOM,
	GRAND_GALLERY,
	CAMPBELL_SUITE

};

// weights of carryable objects
#define WEIGHTLESS		0  // things that can't be picked up.
#define LIGHTWEIGHT		2
#define MIDDLEWEIGHT	4
#define HEAVYWEIGHT		6


GameSetup::GameSetup()
{// constructor
	wxString DataPath = wxStandardPaths::Get().GetUserLocalDataDir();
	
	if (!wxFileName::Mkdir(DataPath, wxS_DIR_DEFAULT, wxPATH_MKDIR_FULL))
		 wxMessageBox("Can't create the data folder", "Oops");
	MapName = "Tha.Map";
#ifdef __WINDOWS__
	IniFileName = DataPath + "\\tha.ini";  //Windows build
#endif
#ifdef __LINUX__
	IniFileName = DataPath + "./tha.ini";  //linux build
#endif
#ifdef __WXOSX_MAC__
	IniFileName = DataPath + "./tha.ini";  //Mac build
#endif
	MusicFile = "game.wav";
	EndChimeFile = "game_end.wav";
	GameLostFile = "game_lose.wav";
	SplashImage = "splash.png";
	TitleFont = "england.ttf";
	TitleFaceName = "England Hand DB";
	GameTitle = "Town Hall Text Adventure - episode one: The hunt for Henry";
	
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
	// NOTE:  In general, any Item that is Takeable should also be Droppable
	AddInfoToMap(GameMap, "Sandwich", "A Cheese and pickle sandwich - slightly curled", LIGHTWEIGHT, INNER_FOYER, Eatable | Takeable | Droppable, EatFood);
	AddInfoAndConversationToMap(GameMap, 
		"Lady behind the counter", 
		"A very pleasant lady in the prime of her life.  Always ready with a smile.", 
		WEIGHTLESS, 
		TIC, 
		Talkable, 
		"\n\nThe lady behind the counter says \n\t\"Hello.\nLong time no see.\nI\'ll let you into the Town Hall through the TIC\"\n\n", 
		GainEntryToTownHall);

	AddInfoAndConversationToMap(GameMap,
		"A small boy",
		"a scruffy young boy of about ten years old.  \n\nHe looks like he doesn't get much to eat.",
		WEIGHTLESS,
		CLOCK_TOWER,
		Talkable,
		"\n\nNervously, the frightened young boy says \n\t\"Hello, sir.\nPlease don't tell Darius that I'm hiding here.\"\n\n",
		BoyConversation1);


	AddInfoToMap(GameMap, "Door Button", "A metal button marked 'Open Door'", WEIGHTLESS, INNER_FOYER, Usable, PressFrontDoorButton);
	AddInfoToMap(GameMap, "Walking stick", "A rather battered tubular metal folding walking stick", MIDDLEWEIGHT, FIRSTAID_ROOM, Usable | Takeable | Droppable, UseWalkingStick);
	AddInfoToMap(GameMap, "Drink can", "A can of fizzy energy drink", LIGHTWEIGHT, INNER_FOYER, Takeable | Droppable | Drinkable, Drink);
	AddInfoToMap(GameMap, "Rubbish sack", "A heavy sack of something awful", HEAVYWEIGHT, BAR_AREA, Takeable | Droppable);
	AddInfoToMap(GameMap, "Brandy bottle", "A bottle of brandy, containing little more than a mouthful of liquor", LIGHTWEIGHT, MAGISTRATES_CHAMBER, Takeable | Droppable | Drinkable, Drink2);
	AddInfoToMap(GameMap, "Brass key", "A dull brass key that looks like it hasn't been cleaned this century.", LIGHTWEIGHT, TOP_CORRIDOR, Usable | Takeable | Droppable, UseKey, true);
	AddInfoToMap(GameMap, "Vacuum cleaner hose", "A black, curly hose that is essential if you want to use the vacuum cleaner", LIGHTWEIGHT, INVALID_LOCATION, Takeable | Droppable);
	AddInfoToMap(GameMap, "Vacuum cleaner top", "The top of the vacuum cleaner.  ", MIDDLEWEIGHT, REAR_STORE,  Takeable | Droppable);
	AddInfoToMap(GameMap, "Vacuum cleaner base", "The base of the vacuum cleaner.  ", MIDDLEWEIGHT, INVALID_LOCATION, Usable | Takeable | Droppable, AssembleVacuum, true);
	AddInfoAndConversationToMap(GameMap,
		"Darius",
		"An intensely evil presence \n\nHe has kept the poor boy captive since 1885, and now he \n\nwants to do the same to you.",
		WEIGHTLESS,
		CAMPBELL_SUITE,
		Talkable | Killable,
		"\n\nDarius hisses\n\t\"This is MY domain.\nYou have violated it with your presence, and you must die!\n\n",
		DariusConversation);
	return true;
	
}

void GameSetup::AddInfoToMap(Map& theMap, 
	std::string title, 
	std::string desc, 
	uint16_t weight, 
	uint16_t location, 
	uint8_t props, 
	
	void(*func)(void* mainwin),
	bool KeepAfterUse)
{
	std::unique_ptr<Item> newItem(new Item(title, desc, weight, props));
	if (func != nullptr)
		newItem->f = func;
	if (KeepAfterUse)
		newItem->SetKeep(true);
	theMap.PlaceItemInNode(*newItem, location);
	
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
std::unique_ptr<Item> newItem(new Item(title, desc, weight, props));

if (func != nullptr)
newItem->f = func;
newItem->SetConversation(conversation);
theMap.PlaceItemInNode(*newItem, location);

//delete newItem;
}


void GameSetup::AddInfoToPlayer(Player& thePlayer,Map& theMap, std::string title, std::string desc, uint16_t weight, uint16_t location, uint8_t props)
{
	std::unique_ptr<Item> newItem(new Item(title, desc, weight, props));
	// store in the map so the Item can be found when loading
	AddInfoToMap(theMap, title, desc, weight, props); 
	thePlayer.AddItemID(newItem->GetID());
	
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

std::vector<std::string> GameSetup::FightDialogue()
{
	std::vector<std::string> line;
	line.push_back("\nDarius deals you a mighty blow");
	line.push_back("\nYou fight like a wounded tiger");
	line.push_back("\nBoth you and your enemy are beginning to weaken");
	line.push_back("\nOuch!");
	line.push_back("\nThe fight is getting messy");
	line.push_back("\nThe red mist of anger descends");
	line.push_back("\nAaaargh!!");
	line.push_back("\nBlow after blow rain down on you");
	line.push_back("\nYou are both breathing heavily");
	line.push_back("\nThe battle is long and tiring");
	line.push_back("\nYou are almost worn down");
	line.push_back("\nThis could have been a quiet day");
	return line;
}

//////////////////////////////////////////////////////////////////////////////
//  functions that are specific to each game.  Used as function pointers passed
// to AddItemToMap calls as optional function pointers.  Must return void and 
// accept only the void* mainwin argument
//////////////////////////////////////////////////////////////////////////////



void UseWalkingStick(void* mainwin)
{
	cMain* c = (cMain*)mainwin;
	if (c->CurrentMapNode.GetID() == CAMPBELL_SUITE)
	{ // use the walking stick as a weapon
		c->ClearDesc();
		c->AddToDesc("\nYou attack the evil Darius with the walking stick,\nIt breaks, but causes a lot of damage to Darius's head.\n\n");
		c->ReduceEnemyHealth(50);
		
		Player* p = c->GetPlayer();
		p->RemoveHealth(15);
	}
	else
	{
		c->PlaySFX("break.wav");
		c->FlashPanel();
		
		c->ClearDesc();
		c->AddToDesc("\nYou lean on the walking stick,\nIt breaks, leaving you looking foolish on the floor\n\n");


		c->AddToDesc("Ouch!\n\n");
		Player* p = c->GetPlayer();
		p->RemoveHealth(15);
	}
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
	c->EnableCurrentMapNodeExit(North, OUTER_FOYER);
	c->Refresh();
	
}

void PressFrontDoorButton(void* mainwin)
{
	cMain* c = (cMain*)mainwin;
	c->PlaySFX("door.wav");
	c->FlashPanelBlack();
	c->ClearDesc();

	c->AddToDesc("\nYou press the button.  Slowly the doors start to open,\nand then there is a loud bang and the doors slam shut.\n\n");


	c->AddToDesc("That's torn it!\n\n");
	

	c->WaitForAnyKey();
}

void AssembleVacuum(void* mainwin)
{
	cMain* c = (cMain*)mainwin;
	
	c->ClearDesc();
	// need to check that all pieces of the vacuum are in the current location
	bool bBase = false;
	bool bHose = false;
	bool bTop = false;
	for (auto items : c->CurrentMapNode.ItemsInNode)
	{
		if (items.GetName() == "Vacuum cleaner hose")
			bHose = true;
		if (items.GetName() == "Vacuum cleaner base")
			bBase = true;
		if (items.GetName() == "Vacuum cleaner top")
			bTop = true;
	}
	if (bHose && bBase && bTop)  // all three elements in the same room
	{
		c->AddToDesc("\nYou see before you the pieces of the vacuum cleaner.\nWith an expertise borne of great experience, you assemble the vacuum and begin work on cleaning the Main Hall.\n\n");


		c->ShowEpilogue();
		// ask to start a new game or exit
		c->StartNewGame();
		return;
	}
	else
	c->AddToDesc("\nSorry, you haven't got all the pieces of the vacuum cleaner yet.");
	{

		c->WaitForAnyKey();
	}
}

void UseKey(void* mainwin)
{// use the key.  It does nothing if not in the correct location
	cMain* c = (cMain*)mainwin;
	c->ClearDesc();
	uint16_t MapNodeID = c->CurrentMapNode.GetID();
	if (MapNodeID == REAR_STAIRCASE)
	{
		c->AddToDesc("The ancient door opens slowly, with an ominous creak\n\nSuddenly you feel faint.\n\nYou pass out briefly\n\n");
		c->AddToDesc("You feel disoriented\n\n");
		
		c->SetCurrentRoom(CLOCK_TOWER);
		bool found = false;
		for (auto& ItemID : c->CurrentMapNode.ItemsInNode)
		{// find the item in the current MapNode that matches the Key's ID
			if (ItemID.GetName() == "Brass key")
			{
				ItemID.SetKeep(false);
				found = true;
			}
		}
		if (!found)
		{ // the item should be among the player's carried items
			for (auto& ItemID : c->player->pNode.ItemsInNode )
			{// find the item in the current MapNode that matches the Key's ID
				if (ItemID.GetName() == "Brass key")
				{
					ItemID.SetKeep(false);
					found = true;
				}
			}

		}
			
	}
	else
	{
		c->AddToDesc("There aren't any locks that fit this key here.\n\n");
	}
	c->WaitForAnyKey();
}

void EatFood(void* mainwin)
{
	cMain* c = (cMain*)mainwin;
	c->PlaySFX("yum.wav");
}

void Drink(void* mainwin)
{
	cMain* c = (cMain*)mainwin;

	c->PlaySFX("drink1.wav");

}

void Drink2(void* mainwin)
{
	cMain* c = (cMain*)mainwin;

	c->PlaySFX("drink2.wav");
}

void BoyConversation1(void* mainwin)
{
	cMain* c = (cMain*)mainwin;

}
void BoyConversation2(void* mainwin)
{
	cMain* c = (cMain*)mainwin;
}
void BoyConversation3(void* mainwin)
{
	cMain* c = (cMain*)mainwin;
}

void DariusConversation(void* mainwin)
{
	cMain* c = (cMain*)mainwin;

	//  move the remaining piece of the vacuum cleaner to a random room
	MapNode* mn = c->map->GetMapNodeByID(INVALID_LOCATION);
	
	
	
	if (c->bBossKilled)  // Darius is dead
	{

		int iRandVal = (std::rand() % MAIN_LADIES) + 4;
		c->SetCurrentRoom((uint16_t)iRandVal);
		return;

	}
	for (auto i : mn->ItemsInNode)
	{  // place all of the items in the hidden node somewhere in the map
		int iRandVal = (std::rand() % MAIN_LADIES) + 4;
		c->map->PlaceItemInNode(i, iRandVal);
		
		MapNode* mnNew = c->map->GetMapNodeByID(iRandVal);

		c->map->Replace(*mnNew);

	}
	
}

