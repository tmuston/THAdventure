///////////////////////////////////////////////////////////////////////////////
//								  StartDialog.cpp                            //
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
//    This file defines the window that gets the player name                 //
//                                                                           //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
#include "StartDialog.h"

wxBEGIN_EVENT_TABLE(StartDialog, wxDialog)

EVT_BUTTON(wxID_OK, OnOK)
EVT_TEXT(tmID_NAME, OnTextChange)
EVT_TEXT_ENTER(tmID_NAME, OnTextEnter)
wxEND_EVENT_TABLE()

StartDialog::StartDialog(wxWindow* parent, wxWindowID id, const wxString& title,
	const wxPoint& position, const wxSize& size, long style)
	: wxDialog(parent, id, title, position, size, style)
{//  construct a wxDialog to allow the player to enter their name
	Centre();
	lblBlurb = new wxStaticText(this, wxID_ANY, wxT("Please enter a player name"), wxPoint(120, 20), wxSize(150,30));
	txtName = new wxTextCtrl(this, tmID_NAME, "", wxPoint(80,60), wxSize(240, 25), wxTE_CENTRE | wxTE_PROCESS_ENTER);
	txtName->SetMaxLength(15);
	btnOK = new wxButton(this, wxID_OK, "&Ok", wxPoint(160, 110), wxSize(80, 35));
	btnOK->Enable(false);
	
	
}



StartDialog::~StartDialog()
{
}

wxString StartDialog::GetText()
{
	return Answer;
}

void StartDialog::OnOK(wxCommandEvent& evt)
{
	Answer = txtName->GetValue();
	Close();
	evt.Skip();
}

void StartDialog::OnTextChange(wxCommandEvent& evt)
{  // if there's text, enable the button
	if (txtName->GetValue() != wxT(""))
		btnOK->Enable(true);
	else
		btnOK->Enable(false);
	
	evt.Skip();
}

void StartDialog::OnTextEnter(wxCommandEvent& evt)
{
	if (txtName->GetValue() != wxT(""))
	{
		Answer = txtName->GetValue();
		Close();
		
	}
	evt.Skip();
}
