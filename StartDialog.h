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
//    Released as open source under the GPL license (See license.txt)        //
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

private:
	wxButton* btnOK = nullptr;
	wxTextCtrl* txtName = nullptr;
	wxStaticText* lblBlurb = nullptr;
	wxString Answer = "";
	wxDECLARE_EVENT_TABLE();
};
#endif  //NEWGAME_H

