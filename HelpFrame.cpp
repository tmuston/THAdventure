#include "HelpFrame.h"

wxBEGIN_EVENT_TABLE(HelpFrame, wxFrame)

	EVT_BUTTON(tmHELPOK, OnHelpOk)
wxEND_EVENT_TABLE()


HelpFrame::HelpFrame() : wxFrame(nullptr,
	wxID_ANY,
	"Programme Help",
	wxDefaultPosition,
	wxSize(800, 600),
	wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER & ~wxMAXIMIZE_BOX)
{
	Centre();
	wxRichTextCtrl* TextBox = new wxRichTextCtrl(this, wxID_ANY, "", wxPoint(0, 0), wxSize(787, 500),wxTE_MULTILINE |wxTE_BESTWRAP | wxTE_AUTO_URL | wxTE_READONLY);
	wxButton* btnHelpOK = new wxButton(this, tmHELPOK, "OK", wxPoint(360, 510), wxSize(80, 35));
	TextBox->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
	TextBox->LoadFile("MapMaker.txt", wxRICHTEXT_TYPE_TEXT);
	TextBox->SetEditable(false);
}


HelpFrame::~HelpFrame()
{
}

void HelpFrame::OnHelpOk(wxCommandEvent& evt)
{
	Close();
}
