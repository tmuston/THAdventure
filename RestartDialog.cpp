///////////////////////////////////////////////////////////////////////////////
//								  RestartDialog.cpp                          //
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
//    This file defines the window that gets the player name                 //
//                                                                           //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
#include "RestartDialog.h"

wxBEGIN_EVENT_TABLE(RestartDialog, wxDialog)

EVT_BUTTON(wxID_OK, OnOK)
EVT_BUTTON(wxID_CANCEL, OnCancel)
EVT_TEXT(tmID_RNAME, OnTextChange)
EVT_TEXT_ENTER(tmID_RNAME, OnTextEnter)
wxEND_EVENT_TABLE()

RestartDialog::RestartDialog(wxWindow* parent, wxWindowID id, const wxString& title,
	const wxPoint& position, const wxSize& size, long style)
	: wxDialog(parent, id, title, position, size, style)
{//  construct a wxDialog to allow the player to enter their name
	Centre();
	lblBlurb = new wxStaticText(this, wxID_ANY, wxT("Please enter a player name"), wxPoint(120, 20), wxSize(150, 30));
	txtName = new wxTextCtrl(this, tmID_RNAME, "", wxPoint(80, 60), wxSize(240, 25), wxTE_CENTRE | wxTE_PROCESS_ENTER);
	txtName->SetMaxLength(15);
	txtName->SetToolTip(wxT("Enter a name (max 15 characters)"));
	btnOK = new wxButton(this, wxID_OK, "Ok", wxPoint(80, 110), wxSize(80, 35));
	
	btnCancel = new wxButton(this, wxID_CANCEL, "Exit", wxPoint(240, 110), wxSize(80, 35));
	btnOK->Enable(false);


}



RestartDialog::~RestartDialog()
{
}

wxString RestartDialog::GetText()
{
	return Answer;
}

void RestartDialog::OnOK(wxCommandEvent& evt)
{
	Answer = txtName->GetValue();
	EndModal(wxID_OK);
	evt.Skip();
}

void RestartDialog::OnCancel(wxCommandEvent& evt)
{

	EndModal(wxID_CANCEL);
	evt.Skip();
}

void RestartDialog::OnTextChange(wxCommandEvent& evt)
{  // if there's text, enable the button
	if (txtName->GetValue() != wxT(""))
		btnOK->Enable(true);
	else
		btnOK->Enable(false);

	evt.Skip();
}

void RestartDialog::OnTextEnter(wxCommandEvent& evt)
{
	if (txtName->GetValue() != wxT(""))
	{
		Answer = txtName->GetValue();
		Close();

	}
	evt.Skip();
}
