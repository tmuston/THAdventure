#ifndef LOOPTIMER_H
#define LOOPTIMER_H
///////////////////////////////////////////////////////////////////////////////
//								  LoopTimer.h                                //
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
//    This file declares a LoopTimer object                                  //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////


#include "wx/timer.h"
class LoopTimer : public wxTimer
{
public:
	void Notify();
	void start();
};

#endif  //  LOOPTIMER_H

