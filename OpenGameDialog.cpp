///////////////////////////////////////////////////////////////////////////////
//								  OpenGameDialog.cpp                         //
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
//    This file defines the window that gets the saved games                 //
//                                                                           //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
#include "OpenGameDialog.h"

OpenGameDialog::OpenGameDialog(wxWindow* parent, 
	wxWindowID id, 
	const wxString& title, 
	const wxPoint& position, 
	const wxSize& size, 
	long style)
	: wxDialog(parent, id, title, position, size, style)
{
}

OpenGameDialog::~OpenGameDialog()
{
}
