#ifndef BUILDOPTS_H
#define BUILDOPTS_H
///////////////////////////////////////////////////////////////////////////////
//								  BuildOpts.h                                  //
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
//    This file declares the build options.                                  //
//                                                                           //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#define TIM_TESTING  //  Comment this line out for production
#ifdef TIM_TESTING
	#define NOSPLASH
	#define NOPROLOGUE
	#define NOEPILOGUE
#endif
#endif
