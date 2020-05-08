#pragma once
#include <iostream>

class Item
{
public:
	Item();
	~Item();
private:
	unsigned int ID;
	std::string Name;
	std::string Description;
	// not really weight, but needed because there needs to be a means of not 
	// allowing the player to carry every item - a weight limit, like at the airport
	unsigned int weight; 
	bool bCanBeUsed = false;
	bool bCanBeMoved = false;
	bool bCanBeDestroyed = false;

};

