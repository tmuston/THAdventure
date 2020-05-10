#ifndef SOUNDOPTIONS_H
#define SOUNDOPTIONS_H

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
	
	void OnClose(wxCommandEvent& evt);
	void OnChangeMusicSlider(wxCommandEvent& evt);
	
private:
	wxPanel* panel = nullptr;
	wxSlider* MusicSlider = nullptr;
	wxSlider* SfxSlider = nullptr;
	wxStaticText* lblMusic = nullptr;
	wxStaticText* lblSFX = nullptr;
	wxButton* btnClose = nullptr;
	
	wxDECLARE_EVENT_TABLE();
};
#endif // SOUNDOPTIONS_H

