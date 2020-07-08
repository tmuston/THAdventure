#ifndef SOUNDOPTIONS_H
#define SOUNDOPTIONS_H
///////////////////////////////////////////////////////////////////////////////
//								  SoundOptions.h                             //
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
//    This file declares the SoundOptions class, which displays a            //
//    custom dialog to allow setting of sound and music volume.              //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

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
	void OnChangeSfxSlider(wxCommandEvent& evt);
	
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

