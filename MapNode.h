#pragma once
#include <cstdint>
#include <string>
#include <iostream>
#include <vector>



static uint16_t NodeID = 0;
// non member function Sue me!
void ZeroNodeId();	//  resets the NodeID static variable to zero.  Has to be here, as a static variable
					//  can't be altered from within another file.
//enum Directions
//{
//	North = 1,
//	East = 2,
//	South = 4,
//	West = 8,
//	Up = 16,
//	Down = 32
//};

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
	MapNode( Nodes & n, std::string Title, std::string Desc, bool won = false);
	MapNode(uint16_t id, Nodes& n, std::string Title, std::string Desc, bool won = false);
	MapNode(const MapNode& obj);
	~MapNode();

	/*bool AddItem();
	bool DropItem();
	bool Leave(Directions d);*/
	void DescribeNode();
	inline uint16_t GetID() { return ID; }
	inline std::string GetTitle() { return Title; }
	inline std::string GetDesc() { return Description; }
	inline void SetTitle(std::string t) { Title = t; }
	inline void SetDescription(std::string d) { Description = d; }
	std::string NodeToString();
	uint16_t GetExit(int n);
	bool SetExit(uint16_t exit, uint16_t value);
	void SetExits(Nodes& node);
	
private:
	std::string Title;
	std::string Description;
	//std::vector<uint8_t> ItemsInNode;	// whatever items happen to be in the room
	uint16_t ID;
	uint16_t ExitIDs[6];				// needs to be populated by the class
										// an ID of zero indicates no exit
										// ExitIDs[0] = North
										// ExitIDs[1] = East
										// ExitIDs[2] = South
										// ExitIDs[3] = West
										// ExitIDs[4] = Up
										// ExitIDs[5] = Down
};

