#include "cApp.h"
#include "cMain.h"
#include "wx/splash.h"
#include "wx/bitmap.h"
#include "wx/icon.h"


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
	if (bitmap.LoadFile(wxT("splash.png"), wxBITMAP_TYPE_PNG))
	{
		wxSplashScreen* splash = new wxSplashScreen(bitmap,
			wxSPLASH_CENTRE_ON_SCREEN | wxSPLASH_TIMEOUT,
			4000, NULL, -1, wxDefaultPosition, wxDefaultSize,
			wxBORDER_SIMPLE | wxSTAY_ON_TOP);
	}
	
	::wxSleep(4);
#endif

	m_frame1 = new cMain();

	m_frame1->Show();
	return true;
}
