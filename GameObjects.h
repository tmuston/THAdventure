#pragma once
#include <iostream>
#include <vector>
#include "Item.h"
class GameObjects
{  //a list of objects in a player's possession or in a room
public:
	GameObjects();
	~GameObjects();

private:
	std::vector<Item> Objects;
	
	
};

