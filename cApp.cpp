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
{
	// if another instance is running, bail out pronto
	checker = new wxSingleInstanceChecker;
	if (checker->IsAnotherRunning())
	{
		wxMessageBox("Another instance of the program is already running!", "Ooops");
		delete checker;
		checker = nullptr;
		return false;
	}
	
// add a splash screen  id NOSPLASH isn't defined in cApp.h  Less of a pain during testing to not have to wait
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

int cApp::OnExit()
{
	delete checker;
	checker = nullptr;
	return 0;
}
