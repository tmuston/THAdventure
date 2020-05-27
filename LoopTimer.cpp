///////////////////////////////////////////////////////////////////////////////
//								  LoopTimer.cpp                              //
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
//    This file defines a LoopTimer object                                   //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
#include "LoopTimer.h"

void LoopTimer::Notify()
{// do some witchcraft
}

void LoopTimer::start()
{//Start the timer
	wxTimer::Start(30);  // 30 milliseconds
}
