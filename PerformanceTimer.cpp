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
//    Released as open source under the GPL v3 license (See COPYING file)    //  
//    This program is free software: you can redistribute it and/or modify   //
//    it under the terms of the GNU General Public License as published by   //
//    the Free Software Foundation, either version 3 of the License, or      //
//    (at your option) any later version.                                    //
//                                                                           //
//    This program is distributed in the hope that it will be useful,        //
//    but WITHOUT ANY WARRANTY; without even the implied warranty of         //
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the            //
//    GNU General Public License for more details.                           //
//                                                                           //
//    You should have received a copy of the GNU General Public License      //
//    along with this program.If not, see < https://www.gnu.org/licenses/>.  //
//                                                                           //
//                     Tim Muston  tim@tmuston.co.uk                         //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
//                                                                           //                                                                           //
//         This file defines a performance timimg class                      //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
#include "PerformanceTimer.h"

PerformanceTimer::PerformanceTimer()
{
	using namespace std::chrono;
	t1 = high_resolution_clock::now();
	// next line only needed to stop the pedantic compiler from complaining about an uninitialized value of time_span
	time_span = duration_cast<duration<double>>(t1 - t1);  
}

PerformanceTimer::~PerformanceTimer()
{
	using namespace std::chrono;
	t2 = high_resolution_clock::now();
	time_span = duration_cast<duration<double>>(t2 - t1);
	std::cout << "It took me " << time_span.count() << " seconds.";
}
