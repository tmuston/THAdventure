///////////////////////////////////////////////////////////////////////////////
//								  GameState.h                                //
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
//    This file declares a GameState object, which is used as an area to     //         
//    store any configuration changes as a delta from the original state     //
//    Also handles loading and saving of game (.sav) files                   //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
#ifndef GAMESTATE_H
#define GAMESTATE_H
class GameState
{// this class  handles any changes to the state of the MapNode and Item objects from
 // their original states.  It also handles load and save.
public:
	GameState();
	~GameState();
private:

};
#endif //GAMESTATE_H

