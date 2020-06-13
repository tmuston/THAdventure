#include "PlayerNode.h"

PlayerNode::PlayerNode()
{
	numItems = 0;
}

PlayerNode::~PlayerNode()
{
}

bool PlayerNode::AddItem(const Item& item)
{
	ItemsInNode.push_back(item);
	numItems++;
	return true;
}

bool PlayerNode::DropItem(Item& item)
{
	for (std::vector<Item>::iterator it = ItemsInNode.begin(); it != ItemsInNode.end(); ++it)
	{
		if (it->GetID() == item.GetID())
		{
			ItemsInNode.erase(it);
			numItems--;
			return true;
		}
	}
	return false;
	
}
