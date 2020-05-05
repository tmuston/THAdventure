#pragma once
#include "wx/wx.h"
#include "wx/frame.h"

#define tmID_MUSICSLIDER 400
#define tmID_SFXSLIDER 401
#define tmID_CLOSEFORM 402

class SoundOptions : public wxFrame
{
public:
	SoundOptions();
	~SoundOptions();

	void OnClose(wxCommandEvent& evt);
private:
	wxPanel* panel = nullptr;
	wxSlider* MusicSlider = nullptr;
	wxSlider* SfxSlider = nullptr;
	wxStaticText* lblMusic = nullptr;
	wxStaticText* lblSFX = nullptr;
	wxButton* btnClose = nullptr;

	wxDECLARE_EVENT_TABLE();
};

