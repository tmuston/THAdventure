#ifndef MAPNODE_H
#define MAPNODE_H
///////////////////////////////////////////////////////////////////////////////
//								  MapNode.h                                  //
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
//    This file declares the MapNode. which can be thought of as the         //
//    rooms or locations within a game map.                                  //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
#include <cstdint>
#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <array>
#include "Item.h"

static uint16_t NodeID = 0;
// non member function Sue me!
void ZeroNodeId();	//  resets the NodeID static variable to zero.  Has to be here, as a static variable
					//  can't be altered from within another file.
void SetNodeID(uint16_t id);
enum Directions
{
	North = 1,
	East = 2,
	South = 4,
	West = 8,
	Up = 16,
	Down = 32
};

struct Nodes
{
public:
	Nodes();
	~Nodes();
	uint16_t n;
	uint16_t e;
	uint16_t s;
	uint16_t w;
	uint16_t u;
	uint16_t d;
};
class MapNode
{
public:
	MapNode();
	MapNode(Nodes& n, std::string Title, std::string Desc, bool won = false);
	MapNode(uint16_t id, Nodes& n, std::string Title, std::string Desc, bool won = false);
	MapNode(const MapNode& obj);
	~MapNode();

	bool AddItem(const Item& item);
	bool DropItem(Item& item);
	//bool Leave(Directions d);
	inline uint16_t GetID() { return ID; }
	inline std::string GetTitle() { return Title; }
	std::string GetDesc();
	inline void SetTitle(std::string t) { Title = t; }
	inline void SetDescription(std::string d) { Description = d; }
	std::string NodeToString();
	uint16_t GetExit(int n);
	bool SetExit(uint16_t exit, uint16_t value);
	bool GetItems(std::vector<Item>& Items);
	uint16_t GetItemIdFromName(std::string str);
	
	void SetExits(Nodes& node);
	uint16_t GetAllExits();
	
	std::vector<Item> ItemsInNode;	// whatever items happen to be in the room

private:
	std::string Title;
	std::string Description;
	
	uint16_t ID = 0;
	std::array<uint16_t, 6> ExitIDs;
	//uint16_t ExitIDs[6];				// needs to be populated by the class
										// an ID of zero indicates no exit
										// ExitIDs[0] = North
										// ExitIDs[1] = East
										// ExitIDs[2] = South
										// ExitIDs[3] = West
										// ExitIDs[4] = Up
										// ExitIDs[5] = Down
};

#endif // MAPNODE_H
