///////////////////////////////////////////////////////////////////////////////
//					        PerformanceTimer.cpp                             //
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
//         This file defines a performance timimg class                      //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
#include "PerformanceTimer.h"

PerformanceTimer::PerformanceTimer()
{
	using namespace std::chrono;
	t1 = high_resolution_clock::now();
}

PerformanceTimer::~PerformanceTimer()
{
	using namespace std::chrono;
	t2 = high_resolution_clock::now();
	time_span = duration_cast<duration<double>>(t2 - t1);
	std::cout << "It took me " << time_span.count() << " seconds.";
}
