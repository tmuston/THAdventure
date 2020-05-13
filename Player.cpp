#include "Player.h"

Player::Player(std::string name)
{// will need to checkthat some dweeb hasn't initialised name to NULL 
	if((name != ""))
		PlayerName = name;
}

Player::~Player()
{
}
