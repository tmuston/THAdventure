///////////////////////////////////////////////////////////////////////////////
//								  cApp.cpp                                   //
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
//    This file defines a wxWidgets application object.                      //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#include "wx/splash.h"
#include "wx/bitmap.h"
#include "wx/icon.h"
#include "GameSetup.h"
#include "cMain.h"
#include "cApp.h"

wxIMPLEMENT_APP(cApp);

cApp::cApp()
{
}

cApp::~cApp()
{
}

bool cApp::OnInit()
{// add a splash screen  id NOSPLASH isn't defined in cApp.h  Less of a pain during testing to not have to wait
#ifndef NOSPLASH
	wxImage::AddHandler(new wxPNGHandler);
	wxBitmap bitmap;
	wxSplashScreen* splash = nullptr;
	GameSetup *setup =new GameSetup();  
	if (bitmap.LoadFile(setup->GetSplashImage(), wxBITMAP_TYPE_PNG))
	{
		splash = new wxSplashScreen(bitmap,
			wxSPLASH_CENTRE_ON_SCREEN | wxSPLASH_TIMEOUT,
			4000, NULL, -1, wxDefaultPosition, wxDefaultSize,
			wxBORDER_SIMPLE | wxSTAY_ON_TOP);


		::wxSleep(4);
		splash->Close(true);
		delete splash;
		delete setup;
	}
#endif
	
	m_frame1 = new cMain();

	m_frame1->Show();
	return true;
}