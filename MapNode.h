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
//    Released as open source under the GPL license (See license.txt)        //
//                                                                           //
//    This file declares the MapNode. which can be thought of as the         //
//    rooms or locations within a game map.                                  //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
#include <cstdint>
#include <string>
#include <iostream>
#include <vector>
#include <memory>
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
	bool DropItem(const Item& item);
	//bool Leave(Directions d);
	inline uint16_t GetID() { return ID; }
	inline std::string GetTitle() { return Title; }
	std::string GetDesc();
	inline void SetTitle(std::string t) { Title = t; }
	inline void SetDescription(std::string d) { Description = d; }
	std::string NodeToString();
	uint16_t GetExit(int n);
	bool SetExit(uint16_t exit, uint16_t value);
	void SetExits(Nodes& node);
	uint16_t GetAllExits();

private:
	std::string Title;
	std::string Description;
	std::vector<Item> ItemsInNode;	// whatever items happen to be in the room
	uint16_t ID = 0;
	uint16_t ExitIDs[6];				// needs to be populated by the class
										// an ID of zero indicates no exit
										// ExitIDs[0] = North
										// ExitIDs[1] = East
										// ExitIDs[2] = South
										// ExitIDs[3] = West
										// ExitIDs[4] = Up
										// ExitIDs[5] = Down
};

#endif // MAPNODE_H
