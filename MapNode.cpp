///////////////////////////////////////////////////////////////////////////////
//								  MapNode.cpp                                //
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
//    This file defines the MapNode. which can be thought of as the          //
//    rooms or locations within a game map.                                  //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
#include "MapNode.h"

Nodes::Nodes()
{
	// set all directions to zero
	this->n = this->e = this->s = this->w = this->u = this->d = 0;
}

Nodes::~Nodes()
{
}

////////////////////////////////////////////////////////////////////////////
///////////////////////////////MapNode Class////////////////////////////////
////////////////////////////////////////////////////////////////////////////

MapNode::MapNode()
{// Do nowt, as the default constructor makes no sense.
	ID = ++NodeID;
}

MapNode::MapNode(Nodes& n, std::string Caption, std::string Desc, bool won)
{
	Title = Caption;
	Description = Desc;
	ID = ++NodeID;				// Create a unique Node ID (starting at 1)
	SetExits(n);
}
MapNode::MapNode(uint16_t id, Nodes& n, std::string Caption, std::string Desc, bool won)
{
	Title = Caption;
	Description = Desc;
	ID = id;				// Create a unique Node ID (starting at 1)
	NodeID = ID;
	SetExits(n);
}

MapNode::MapNode(const MapNode& obj)
{// copy constructor
	ID = obj.ID;
	Title = obj.Title;
	Description = obj.Description;
	for (int i = 0; i < 6; i++)
		ExitIDs[i] = obj.ExitIDs[i];
}

MapNode::~MapNode()
{// do nowt - for the moment
}

bool MapNode::AddItem(const Item& item)
{// Add an item to the vector.  Could be on initialisation, or when a player drops it
	ItemsInNode.push_back(item);
	return true;
}

bool MapNode::DropItem(const Item& item)
{// remove an item, and leave it in the current room
	return false;
}

void MapNode::SetExits(Nodes& node)
{
	ExitIDs[0] = node.n; // North
	ExitIDs[1] = node.e; // East
	ExitIDs[2] = node.s; // South
	ExitIDs[3] = node.w; // West
	ExitIDs[4] = node.u; // Up
	ExitIDs[5] = node.d; // Down
}

uint16_t MapNode::GetAllExits()
{
	uint16_t RetVal = 0;
	
	for (int i = 0; i < 6; i++)
	{
		if (ExitIDs[i] != 0)// a valid exit
			RetVal += (uint16_t)pow(2,i);
	}
	return RetVal;
}

std::string MapNode::GetDesc()
{//  This needs to replace any occurrence of <newline> with \n
	size_t pos = 0;
	std::string search = "<newline>";
	std::string replace = "\n";
	
	while ((pos = Description.find(search, pos)) != std::string::npos)
	{
		Description.replace(pos, search.length(), replace);
		pos += replace.length();
	}
	return Description;
}

std::string MapNode::NodeToString()
{
	using std::string;
	using std::to_string;

	string s;
	s = "~~";
	s.append(to_string(ID));
	s.append("~");
	s.append(Title);
	s.append("~");
	s.append(Description);
	for (auto i = 0; i < 6; i++)
	{
		s.append("~");
		uint16_t ex = ExitIDs[i];
		s.append(to_string(ex));
	}
	s.append("\n");

	return s;
}

uint16_t MapNode::GetExit(int n)
{
	if ((n >= 0) && (n <= 5))
		return ExitIDs[n];
	return -1;  // error
}

bool MapNode::SetExit(uint16_t exit, uint16_t value)
{// check if the exit number is invalid
	if ((exit < 0) || (exit > 5))
		return false;
	ExitIDs[exit] = value;
	return true;
}

bool MapNode::GetItems(std::vector<Item>& Items)
{// get all the items in the node.  Return true if there are any items, false otherwise
	if(ItemsInNode.size()  == 0 )
		return false;
	
	for (std::vector<Item>::iterator it = ItemsInNode.begin(); it != ItemsInNode.end(); ++it)
	{
		Items.push_back(*it);
	}
	return true;
}

/////////////////////////////////////////////////////////////////////
/////////////////////////// Not member functions ////////////////////
/////////////////////////////////////////////////////////////////////
void ZeroNodeId()
{// revert the static NodeId to its original value.
	NodeID = 0;
}

void SetNodeID(uint16_t id)
{
	NodeID = id;
}