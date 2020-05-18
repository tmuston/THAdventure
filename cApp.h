#ifndef APP_H  // guard
#define APP_H
///////////////////////////////////////////////////////////////////////////////
//								  cApp.h                                     //
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
//    This file declares a wxWidgets application object.                     //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#include "wx/wx.h"
#include "cMain.h"

//#define TESTING
//#ifdef TESTING
	#define NOSPLASH
	//#define NOPROLOGUE
	#define NOEPILOGUE
//#endif

class cApp : public wxApp
{
public:
	cApp();
	~cApp();
	virtual bool OnInit();
private:
	cMain* m_frame1 = nullptr;
};
#endif //APP_H

