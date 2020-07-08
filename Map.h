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
	MapNode* GetMapNodeByID(uint16_t n);
	bool PlaceItemInNode(Item& i, uint16_t node);
	uint16_t GetMapSize();
	std::vector<MapNode> NodesInMap;
	friend std::ostream& operator << (std::ostream& out, const Map& obj);
	friend std::istream& operator>>(std::istream& is, Map& m);
	
private:
	
	bool StringToMapNode(std::string s);
};
#endif //MAP_H
