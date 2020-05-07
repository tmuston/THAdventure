#pragma once
#include "wx/wx.h"
#include "wx/frame.h"

enum
{
	tmID_MUSICSLIDER = 1,
	tmID_SFXSLIDER,
	tmID_CLOSEFORM
};
class SoundOptions : public wxFrame
{
public:
	SoundOptions();
	~SoundOptions();
	
	void SetMusicVolume();

	void OnClose(wxCommandEvent& evt);
	void OnChangeMusicSlider(wxCommandEvent& evt);

private:
	
	wxPanel* panel = nullptr;
	wxSlider* MusicSlider = nullptr;
	wxSlider* SfxSlider = nullptr;
	wxStaticText* lblMusic = nullptr;
	wxStaticText* lblSFX = nullptr;
	wxButton* btnClose = nullptr;
	double MusicVolume = 0.5;
	

	wxDECLARE_EVENT_TABLE();
};

