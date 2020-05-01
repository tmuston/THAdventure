#pragma once
#include <iostream>
#include <fstream>
#include "MapNode.h"



class Map
{
public:
	Map();
	Map(const Map& obj);
	~Map();
	void Add( MapNode  m); // add a MapNode to the Map
	bool Replace(MapNode m);
	bool SaveMap(std::string fName);
	bool LoadMap(std::string fName);
	MapNode GetMapNode(uint16_t n);
	uint16_t GetMapSize();
	
	

private:
	std::vector<MapNode> currNode;
	bool StringToMapNode(std::string s);
};

