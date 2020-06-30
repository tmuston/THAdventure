///////////////////////////////////////////////////////////////////////////////
//								  SoundOptions.cpp                           //
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
//    This file defines the SoundOptions class, which displays a             //
//    custom dialog to allow setting of sound and music volume.              //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
#include "SoundOptions.h"

wxBEGIN_EVENT_TABLE(SoundOptions, wxFrame)
EVT_BUTTON(tmID_CLOSEFORM, OnClose)
EVT_SLIDER(tmID_MUSICSLIDER, OnChangeMusicSlider)
EVT_SLIDER(tmID_SFXSLIDER, OnChangeSfxSlider)

wxEND_EVENT_TABLE()
extern double gdMusicVolume;
extern double  gdSfxVolume;
SoundOptions::SoundOptions() : wxFrame(nullptr,
	wxID_ANY,
	"Sound Options",
	wxDefaultPosition,
	wxSize(320, 240),
	wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER & ~wxMAXIMIZE_BOX)
{//  display a wxFrame with options for music and sound effect volume
	int iMusicSliderValue = (int)(gdMusicVolume * 10);
	int iSFXSliderValue = (int)(gdSfxVolume * 10);

	Centre();
	panel = new wxPanel(this);
	panel->SetBackgroundColour(wxColour(120, 120, 120));
	lblMusic = new wxStaticText(panel, wxID_ANY, "Music Volume", wxPoint(15, 40), wxSize(40, 45));
	MusicSlider = new wxSlider(panel, tmID_MUSICSLIDER, iMusicSliderValue, 0, 10, wxPoint(60, 40), wxSize(200, 50), wxSL_HORIZONTAL | wxSL_MIN_MAX_LABELS | wxSL_TOP);

	lblSFX = new wxStaticText(panel, wxID_ANY, "Sounds Volume", wxPoint(15, 90), wxSize(40, 45));
	SfxSlider = new wxSlider(panel, tmID_SFXSLIDER, iSFXSliderValue, 0, 10, wxPoint(60, 90), wxSize(200, 50), wxSL_HORIZONTAL | wxSL_MIN_MAX_LABELS | wxSL_TOP);

	btnClose = new wxButton(panel, tmID_CLOSEFORM, "&Close", wxPoint(120, 150), wxSize(80, 35));
}

SoundOptions::~SoundOptions()
{
}

void SoundOptions::OnClose(wxCommandEvent& evt)
{
	Close();
	evt.Skip();
}

void SoundOptions::OnChangeMusicSlider(wxCommandEvent& evt)
{
	int iSliderPos = MusicSlider->GetValue();
	double v = (double)iSliderPos / 10;
	if (v < 0.01)
		v = 0.0;
	if (v > 0.95)
		v = 1.0;
	gdMusicVolume = v;
	evt.Skip();
}

void SoundOptions::OnChangeSfxSlider(wxCommandEvent& evt)
{
	int iSliderPos = SfxSlider->GetValue();
	double v = (double)iSliderPos / 10;
	if (v < 0.01)
		v = 0.0;
	if (v > 0.95)
		v = 1.0;
	gdSfxVolume = v;
	evt.Skip();
}
