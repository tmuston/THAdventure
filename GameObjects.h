#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H
#include <iostream>
#include <vector>
#include "Item.h"

class GameObjects
{  //a list of objects in a player's possession or in a room
public:
	GameObjects();
	~GameObjects();
	void AddItem(const Item& i);
private:
	std::vector<Item> Objects;
	
	
};
#endif // GAMEOBJECTS_H

