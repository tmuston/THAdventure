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
