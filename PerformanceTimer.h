#ifndef PERFORMANCETIMER_H
#define PERFORMANCETIMER_H 
///////////////////////////////////////////////////////////////////////////////
//					        PerformanceTimer.h                               //
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
//            This file declares a performance timimg class                  //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
#include <chrono>
#include <iostream>
class PerformanceTimer
{
public:
	PerformanceTimer();
	~PerformanceTimer();
private:
	std::chrono::high_resolution_clock::time_point t1, t2;
	std::chrono::duration<double> time_span;
};

#endif //PERFORMANCETIMER_H
