#include "cMain.h"
#include "Map.h"

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
	EVT_BUTTON(tmID_CONTINUE, OnContinue)


wxEND_EVENT_TABLE()

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Town Hall Text Adventure - episode one:  The hunt for Henry", wxDefaultPosition, wxSize(800, 600), wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER & ~wxMAXIMIZE_BOX)
{
	map = new Map();

	Centre();
	btnContinue = new wxButton(this, tmID_CONTINUE, "Continue", wxPoint(50, 451), wxSize(80, 35));
}

cMain::~cMain()
{
	if (map != nullptr)
		delete map;
}

void cMain::OnContinue(wxCommandEvent& evt)
{
	wxMessageBox("Hello there", "Message");
	evt.Skip();
}
