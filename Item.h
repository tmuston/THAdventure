#pragma once
#include <iostream>

static uint16_t ItemID = 0;

enum ItemProperty
{
	Eatable		= 1,
	Drinkable	= 2,
	Killable	= 4,
	Movable		= 8,
	Destroyable	= 16,
	Carryable	= 32,
	Usable		= 64,
	Talkable = 128
};

#define INVALID_LOCATION 65535
class Item
{
public:
	Item(std::string name, std::string desc, uint16_t weight, uint8_t props = 0);
	~Item();
	
	inline std::string GetName() { return Name; }
	inline std::string GetDescription() { return Description; }
	inline void SetCurrentLocation(uint16_t loc) { CurrentLocation = loc; }
	inline uint16_t GetCurrentLocation() { return CurrentLocation; }
	bool SetLocation(uint16_t loc);
	inline uint16_t GetLocation() { return CurrentLocation; }
	inline uint8_t GetProperties() { return Properties; }  // get all properties
	// get individual properties
	inline bool GetEdible() { return Properties & Eatable; }
	inline bool GetDrinkable() { return Properties & Drinkable; }
	inline bool GetKillable() { return Properties & Killable; }
	inline bool GetMovable() { return Properties & Movable; }
	inline bool GetDestroyable() { return Properties & Destroyable; }
	inline bool GetCarryable() { return Properties & Carryable; }
	inline bool GetUsable() { return Properties & Usable; }
	inline bool GetTalkable() { return Properties & Talkable; }
	inline std::string GetConversation() { return Conversation; }
	inline void SetConversation(std::string conv) { Conversation = conv; }

	bool SetProperty(uint8_t prop);
private:
	uint16_t ID;  // set in the constructor
	std::string Name;
	std::string Description;
	// not really weight, but needed because there needs to be a means of not 
	// allowing the player to carry every item - a weight limit, like at the airport
	uint16_t Weight; 
	uint8_t Properties = 0;
	std::string Conversation = "";
	// Which room is the item currently in (zero means it's being carried by the player)
	uint16_t CurrentLocation;

};

