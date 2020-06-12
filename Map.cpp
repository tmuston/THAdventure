///////////////////////////////////////////////////////////////////////////////
//								  Map.cpp                                    //
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
//    This file defines the game map. which is simply a collection of       //
//    MapNode objects.  It also handles loading and saving of the map.       //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
#include "Map.h"
#include <sstream>

Map::Map()
{
	NodesInMap.reserve(20);
}

Map::Map(const Map& obj)
{// copy constructor
	NodesInMap = obj.NodesInMap;
}

Map::~Map()
{
	//ZeroNodeId();
}
void Map::Add(MapNode m)
{
	NodesInMap.push_back(m);
}
bool Map::Replace(MapNode m)
{// find a MapNode in the current map that has the same ID, then replace all other data with that from m
	bool bFound = false;
	uint16_t FindID = m.GetID();
	for (uint16_t i = 0; i < GetMapSize(); i++)
	{
		if (NodesInMap[i].GetID() == FindID)
		{// found the right MapNode to modify
			NodesInMap[i].SetTitle(m.GetTitle());
			NodesInMap[i].SetDescription(m.GetDesc());
			for (int j = 0; j < 6; j++)
				NodesInMap[i].SetExit(j, m.GetExit(j));
			NodesInMap[i].ItemsInNode = m.ItemsInNode;
			bFound = true;
		}
		if (bFound)
			break;
	}
	return bFound;
}

bool Map::SaveMap(std::string fName)
{
	std::ofstream file;
	file.exceptions(std::ofstream::failbit | std::ofstream::badbit);
	try
	{
		file.open(fName);

		file << "THAMap\n";  // file header

		// save all of the MapNodes
		for (unsigned int i = 0; i < NodesInMap.size(); i++)
		{
			std::string s = NodesInMap[i].NodeToString();
			file << s;
		}
	}
	catch (...)
	{
		file.close();
		return false;
	}
	file.close();
	return true;
}

bool Map::LoadMap(std::string fName)
{
	std::ifstream file;
	std::string line; // the line to be read in
	file.open(fName);
	if (!file.is_open())
		return false;

	// the file is now open
	std::getline(file, line);

	if (line != "THAMap")
	{// the first line is the header.  If it isn't THAMap, this isn't a proper map file
		file.close();
		return false;
	}

	while (file.peek() != EOF && std::getline(file, line))
	{// read the rest of the file
		bool err = StringToMapNode(line);
		if (false == err)
		{
			file.close();

			return false;
		}
	}

	file.close();
	return true;
}

MapNode Map::GetMapNode(uint16_t n)
{  /// might crash
	return this->NodesInMap[n];
}

MapNode* Map::GetMapNodeByID(uint16_t n)
{
	std::vector<MapNode>::iterator it;
	for (it = NodesInMap.begin(); it != NodesInMap.end(); ++it)
	{
		uint16_t id = it->GetID();
		if (id == n)
		{
			//return &it;
			return &(*it);
		}
	}
	return nullptr;
	// not found
}

bool Map::PlaceItemInNode(Item& item, uint16_t node)
{
	bool bAnswer = false;
	for (uint16_t i = 0; i < NodesInMap.size(); i++)
	{
		uint16_t NodeID = NodesInMap[i].GetID();
		if (NodeID == node)
		{//  should be at the right MapNode
			NodesInMap[i].AddItem(item);
			bAnswer = true;
		}
		if (true == bAnswer)
			break;
	}
	return bAnswer;
}

uint16_t Map::GetMapSize()
{
	uint16_t size = (uint16_t)NodesInMap.size();

	return(size);
}

bool Map::StringToMapNode(std::string s)
{
	// a line of a map file takes the following form
	// firstly there are two tilde characters
	// then the NodeID
	// a tilde
	// the caption
	// a tilde
	// the description
	// a tilde
	// then the nodeIDs for North, East, South, West, Up and down, delimited by tildes
	// eg. ~~1~A Test Room~You find yourself in an open corridor.  The wind howls.~0~2~0~0~0~0
	// any nodeID that is set to zero is an unavailable exit
	// we can also check here for obviously corrupt nodes

	uint16_t id;
	std::string caption;
	std::string description;

	std::stringstream s_stream(s);
	std::vector<std::string> vec;

	while (s_stream.good())
	{
		std::string substr;
		std::getline(s_stream, substr, '~'); //get first string delimited by comma
		vec.push_back(substr);
	}

	// create a new MapNode
	Nodes n;
	//set the Nodes structure internal members
	n.n = std::stoi(vec[5]);
	n.e = std::stoi(vec[6]);
	n.s = std::stoi(vec[7]);
	n.w = std::stoi(vec[8]);
	n.u = std::stoi(vec[9]);
	n.d = std::stoi(vec[10]);
	// set ID
	id = std::stoi(vec[2]);
	caption = vec[3];
	description = vec[4];

	MapNode node(id, n, caption, description);
	//MapNode node(n, caption, description);
	this->Add(node);  // Add the node to the map
	return true;
}

std::ostream& operator<<(std::ostream& out, const Map& obj)
{// only need to store  item locations
	Map tempMap = obj;
	uint16_t NodesInMap = tempMap.GetMapSize();
	for (uint16_t i = 0; i < NodesInMap; i++)
	{
		MapNode tempNode = tempMap.GetMapNode(i);
		// Get all six exits of a MapNode as one uint16_t
		//out << '\n' << '(' << tempNode.GetAllExits() << ')';
		size_t numItems = tempNode.ItemsInNode.size();
		if (numItems > 0)// there are items
		{
			out << '\n' << tempNode.GetID();  // node id
			for (uint16_t j = 0; j < numItems; j++)
			{
				out << ':' << tempNode.ItemsInNode[j].GetID();  // items
			}
		}
	}
	return out;
}

std::istream& operator>>(std::istream& is, Map& m)  // load
{
	std::vector<Item> tmpItems;
	// remove every item from the map, after copying it to the tmpItems vector
	for (uint16_t i = 1; i < m.GetMapSize(); i++)
	{
		bool bHasItems = false;
		MapNode* mn = m.GetMapNodeByID(i);
		for (uint16_t j = 0; j < mn->ItemsInNode.size(); j++)
		{
			bHasItems = true;
			Item tmpI = mn->ItemsInNode[j];
			tmpItems.push_back(tmpI);
		}
		if (bHasItems)
		{  // only needed if there is at least one item in the node
			mn->ItemsInNode.clear();
			mn->ItemsInNode.shrink_to_fit();
		}
	}

	std::string tmpMapString;
	uint16_t tmpMapNodeID, tmpItemID;
	std::getline(is, tmpMapString);  // the first line read is empty for some reason
	uint16_t NodeID = 1;
	while (std::getline(is, tmpMapString))
	{ // break up the line and store its contents
		tmpMapNodeID = std::stoi(tmpMapString);
		while (size_t pos = tmpMapString.find(":") != std::string::npos)
		{
			tmpMapString = tmpMapString.substr(pos + 1);  // chop the beginning
			tmpItemID = std::stoi(tmpMapString);
			MapNode* mn = m.GetMapNodeByID(tmpMapNodeID);
			std::vector<Item>::iterator it;
			for (it = tmpItems.begin(); it != tmpItems.end(); ++it)
			{
				uint16_t tmpInt = it->GetID();
				if (tmpInt == tmpItemID)
				{
					it->SetLocation(tmpInt);
					mn->ItemsInNode.push_back(*it);
					
					
				}
				
			}
		}
	}

	return is;
}