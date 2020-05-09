#include "GameObjects.h"

GameObjects::GameObjects()
{
}

GameObjects::~GameObjects()
{
}

void GameObjects::AddItem(const Item& i)
{// adds an item to the vector, Victor
	
	Objects.push_back(i);
	
}
