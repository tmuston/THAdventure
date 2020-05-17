#ifndef MAP_H
#define MAP_H
///////////////////////////////////////////////////////////////////////////////
//								  Map.h                                      //
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
//    This file declares the game map. which is simply a collection of       //
//    MapNode objects.  It also handles loading and saving of the map.       //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <algorithm>
#include "MapNode.h"

class Map
{
public:
	Map();
	Map(const Map& obj);
	~Map();
	void Add(MapNode  m); // add a MapNode to the Map
	bool Replace(MapNode m);
	bool SaveMap(std::string fName);
	bool LoadMap(std::string fName);
	MapNode GetMapNode(uint16_t n);
	bool PlaceItemInNode(Item& i, uint16_t n);
	uint16_t GetMapSize();

private:
	std::vector<MapNode> currNode;
	bool StringToMapNode(std::string s);
};
#endif //MAP_H
