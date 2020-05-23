#ifndef ITEM_H
#define ITEM_H
///////////////////////////////////////////////////////////////////////////////
//								  Item.h                                     //
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
//    This file declares the properties of the Items which are usable        //
//    within the game.  Note that the items themselves are declared and      //
//    defined within GameSetup.h and GameSetup.cpp.                          //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
#include <iostream>

static uint16_t ItemID = 0;

enum ItemProperty
{
	Eatable		= 1,
	Drinkable	= 2,
	Takeable	= 4,
	Droppable	= 8,
	Usable		= 16,
	Talkable	= 32,
	Killable	= 64,
};

#define INVALID_LOCATION 65535
#define CARRIED_BY_PLAYER 0
#define INVALID_ITEM 65535
class Item
{
public:
	Item(std::string name, std::string desc, uint16_t weight, uint8_t props = 0);
	~Item();
	inline std::string GetName() { return Name; }
	inline uint16_t GetID() { return ID; }
	inline void SetID(uint16_t id) { ID = id; }
	inline std::string GetDescription() { return Description; }
	inline uint16_t GetLocation() { return CurrentLocation; }
	bool SetLocation(uint16_t loc);
	inline uint8_t GetProperties() { return Properties; }  // get all properties
	
	// get individual properties
	/*inline bool GetEdible() { return Properties & Eatable; }
	inline bool GetDrinkable() { return Properties & Drinkable; }
	inline bool GetTakeable() { return Properties & Takeable; }
	inline bool GetDroppable() { return Properties & Droppable; }
	inline bool GetUsable() { return Properties & Usable; }
	inline bool GetTalkable() { return Properties & Talkable; }
	inline bool GetKillable() { return Properties & Killable; }*/
	inline std::string GetConversation() { return Conversation; }
	inline void SetConversation(std::string conv) { Conversation = conv; }

	bool SetProperty(uint8_t prop);
private:
	uint16_t ID = 0;  // set in the constructor
	std::string Name;
	std::string Description;
	// not really weight, but needed because there needs to be a means of not 
	// allowing the player to carry every item - a weight limit, like at the airport
	uint16_t Weight = 0; 
	uint8_t Properties = 0;
	std::string Conversation = "";
	// Which room is the item currently in (zero means it's being carried by the player)
	uint16_t CurrentLocation = 0;

};
#endif // ITEM_H
