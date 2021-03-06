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
	for (auto i = 0; i < 6; i++)
		ExitIDs[i] = 0; 
	// the above 2 lines stop a warning about the default constructor (which is never called)
	// not setting ExitIDs.  Grrrr
}

MapNode::MapNode(Nodes& n, std::string Caption, std::string Desc, bool won)
{
	Title = Caption;
	Description = Desc;
	ID = ++NodeID;				// Create a unique Node ID (starting at 1)
	ItemsInNode.reserve(5);
	SetExits(n);
}
MapNode::MapNode(uint16_t id, Nodes& n, std::string Caption, std::string Desc, bool won)
{
	Title = Caption;
	Description = Desc;
	ID = id;				// Create a unique Node ID (starting at 1)
	NodeID = ID;
	ItemsInNode.reserve(5);
	SetExits(n);
}

MapNode::MapNode(const MapNode& obj)
{// copy constructor
	ID = obj.ID;
	Title = obj.Title;
	Description = obj.Description;
	for (int i = 0; i < 6; i++)
		ExitIDs[i] = obj.ExitIDs[i];
	
	ItemsInNode = obj.ItemsInNode;
	
}

MapNode::~MapNode()
{// do nowt - for the moment
}

bool MapNode::AddItem(const Item& item)
{// Add an item to the vector.  Could be on initialisation, or when a player drops it
	
	ItemsInNode.push_back(item);
	return true;
}

bool MapNode::DropItem(Item& item)
{// remove an item, and leave it in the current room
	for (std::vector<Item>::iterator it = ItemsInNode.begin(); it != ItemsInNode.end(); ++it)
	{
		if (it->GetID() == item.GetID())
		{
			ItemsInNode.erase(it);
			return true;
		}
	}
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

uint16_t MapNode::GetItemIdFromName(std::string str)
{// this function is passed a std::string with the command, a space and then the name
 //  and to return the ID we need to strip the command and space, and then search for the ID
 //  Say it quickly, and it sounds easy.
	uint16_t item = INVALID_ITEM;  // if the item can't be found, this will get returned
	size_t size = str.std::string::find_first_of(" ");  // finds the space after the action to be performed
	std::string sSubstring = str.substr(size + 1);
	for (size_t i = 0; i < ItemsInNode.size(); i++)
	{
		if (ItemsInNode[i].GetName() == sSubstring) //  Hurray!  We've found it
		{
			item = ItemsInNode[i].GetID();
			break;
		}
	}
	return item;
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