#include "Map.h"
#include <sstream>

Map::Map()
{

}

Map::Map(const Map& obj)
{// copy constructor
	currNode = obj.currNode;
}

Map::~Map()
{
	//ZeroNodeId();
}
void Map::Add(MapNode m)
{
	currNode.push_back(m);
}
bool Map::Replace(MapNode m)
{// find a MapNode in the current map that has the same ID, then replace all other data with that from m
	bool bFound = false;
	uint16_t FindID = m.GetID();
	for (uint16_t i = 0; i < GetMapSize(); i++)
	{
		if (currNode[i].GetID() == FindID)
		{// found the right MapNode to modify

			currNode[i].SetTitle(m.GetTitle());
			currNode[i].SetDescription(m.GetDesc());
			for (int j = 0; j < 6; j++)
				currNode[i].SetExit(j, m.GetExit(j));
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
		for (unsigned int i = 0; i < currNode.size(); i++)
		{
			std::string s = currNode[i].NodeToString();
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
{  // needs more work - possible crash

	return this->currNode[n];

}

bool Map::GetMapNodeByID(MapNode& node, uint16_t n)
{
	bool bAnswer = false;
	for (uint16_t i = 0; i< currNode.size(); i++ )
	{
		if (currNode[i].GetID() == n)
		{
			node = currNode[i];
			bAnswer = true;
		}
		if (true == bAnswer)
			break;
	}
	return bAnswer;  // of there isn't a MapNode with the right ID
}

uint16_t Map::GetMapSize()
{
	uint16_t size = (uint16_t)currNode.size();

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
	//uint16_t exits[6];

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
