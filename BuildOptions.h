#ifndef BUILDOPTS_H
#define BUILDOPTS_H
///////////////////////////////////////////////////////////////////////////////
//								  BuildOptions.h                             //
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

//#define TIM_TESTING  //  Comment this line out for production
#ifdef TIM_TESTING
	#define NOSPLASH
	#define NOPROLOGUE
	#define NOEPILOGUE
#endif  // TIM_TESTING

#ifdef __WINDOWS__
#define MEDIA_BACKEND wxMEDIABACKEND_WMP10
#endif

#ifdef __LINUX__
#define MEDIA_BACKEND wxMEDIABACKEND_GSTREAMER
#endif
#ifdef __APPLE__
#define MEDIA_BACKEND wxMEDIABACKEND_QUICKTIME
#endif

#endif  // BUILDOPTS_H
