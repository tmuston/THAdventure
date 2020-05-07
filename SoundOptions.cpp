#include "SoundOptions.h"

wxBEGIN_EVENT_TABLE(SoundOptions,wxFrame)
	EVT_BUTTON(tmID_CLOSEFORM, OnClose)
	EVT_SLIDER(tmID_MUSICSLIDER, OnChangeMusicSlider)
	
wxEND_EVENT_TABLE()

SoundOptions::SoundOptions() : wxFrame(nullptr, 
								wxID_ANY, 
								"Sound Options",	
								wxDefaultPosition, 
								wxSize(320, 240), 
								wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER & ~wxMAXIMIZE_BOX)
{//  display a wxFrame with options for music and sound effect volume
	
	
	Centre();
	panel = new wxPanel(this);
	panel->SetBackgroundColour(wxColour(120, 120, 120));
	lblMusic = new wxStaticText(panel, wxID_ANY, "Music Volume", wxPoint(15, 40), wxSize(40,45));
	MusicSlider = new wxSlider(panel, tmID_MUSICSLIDER, 5, 0, 10, wxPoint(60, 40), wxSize(200, 50),wxSL_HORIZONTAL | wxSL_MIN_MAX_LABELS | wxSL_TOP);
	
	lblSFX = new wxStaticText(panel, wxID_ANY, "Sounds Volume", wxPoint(15, 90), wxSize(40, 45));
	SfxSlider = new wxSlider(panel, tmID_SFXSLIDER, 5, 0, 10, wxPoint(60, 90), wxSize(200, 50), wxSL_HORIZONTAL | wxSL_MIN_MAX_LABELS | wxSL_TOP);
	//MusicSlider->Show();
	
	btnClose = new wxButton(panel, tmID_CLOSEFORM, "&Close", wxPoint(120, 150), wxSize(80, 35));

}

SoundOptions::~SoundOptions()
{// destructor
	
}

void SoundOptions::SetMusicVolume()
{// friend
	
	int iSliderPos = MusicSlider->GetValue();
	double v = (double)iSliderPos / 10;
		if (v < 0.01)
			v = 0.0;
		if (v > 0.95)
			v = 1.0;
		dMusicVol = v;

}



void SoundOptions::OnClose(wxCommandEvent& evt)
{
	
	Close();
	evt.Skip();
}

void SoundOptions::OnChangeMusicSlider(wxCommandEvent& evt)
{
	SetMusicVolume();
	evt.Skip();
}
