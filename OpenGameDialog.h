///////////////////////////////////////////////////////////////////////////////
//								  OpenGameDialog.h                           //
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
//    This file declares the window that gets the saved games                //
//                                                                           //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
#include "wx/dialog.h"
#ifndef OPENGAME_H
#define OPENGAME_H
class OpenGameDialog : public wxDialog
{
public:
	OpenGameDialog(wxWindow* parent, wxWindowID id, const wxString& title,
		const wxPoint& position = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxDEFAULT_DIALOG_STYLE);
	~OpenGameDialog();
};
#endif //OPENGAME_H

