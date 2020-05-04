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
{// Do nowt, as the default constructor makes no sense
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

void MapNode::SetExits(Nodes& node)
{
	ExitIDs[0] = node.n; // North
	ExitIDs[1] = node.e; // East
	ExitIDs[2] = node.s; // South
	ExitIDs[3] = node.w; // West
	ExitIDs[4] = node.u; // Up
	ExitIDs[5] = node.d; // Down
}
void MapNode::DescribeNode()
{
	using std::cout;
	cout << Title << std::endl << Description << std::endl << "Map Node " << NodeID << std::endl;
	cout << std::endl << "Exits are:\n";
	if (ExitIDs[0])
		cout << "\tNorth " << std::endl;
	if (ExitIDs[1])
		cout << "\tEast " << std::endl;
	if (ExitIDs[2])
		cout << "\tSouth " << std::endl;
	if (ExitIDs[3])
		cout << "\tWest" << std::endl;
	if (ExitIDs[4])
		cout << "\tUp" << std::endl;
	if (ExitIDs[5])
		cout << "\tDown" << std::endl;
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

/////////////////////////////////////////////////////////////////////
/////////////////////////// Not a member function ///////////////////
/////////////////////////////////////////////////////////////////////
void ZeroNodeId()
{// revert the static NodeId to its original value.
	NodeID = 0;
}