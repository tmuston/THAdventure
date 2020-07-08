///////////////////////////////////////////////////////////////////////////////
//								  StartDialog.h                              //
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
//                                                                           //
//    This file declares the window that gets the player name                //
//                                                                           //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
#ifndef NEWGAME_H
#define NEWGAME_H
#include "wx/wx.h"
#include "wx/dialog.h"

enum
{
	tmID_NAME = 1,
	tmID_CANCEL,
	tmID_LOAD
};
class StartDialog : public wxDialog
{
public:
	StartDialog(wxWindow* parent, wxWindowID id, const wxString& title,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxDEFAULT_DIALOG_STYLE);
	~StartDialog();
	wxString GetText();
	void OnOK(wxCommandEvent& evt);
	void OnTextChange(wxCommandEvent& evt);
	void OnTextEnter(wxCommandEvent& evt);

private:
	wxButton* btnOK = nullptr;
	wxTextCtrl* txtName = nullptr;
	wxStaticText* lblBlurb = nullptr;
	wxString Answer = "";
	wxDECLARE_EVENT_TABLE();
};
#endif  //NEWGAME_H

