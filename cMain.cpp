#include "cMain.h"
#include "Map.h"
#define id_panel 100
wxBEGIN_EVENT_TABLE(cMain, wxFrame)
	EVT_BUTTON(tmID_CONTINUE, OnContinue)
	EVT_MENU(wxID_EXIT, OnExit)


wxEND_EVENT_TABLE()

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Town Hall Text Adventure - episode one:  The hunt for Henry", wxDefaultPosition, wxSize(800, 600), wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER & ~wxMAXIMIZE_BOX)
{
	panel = new wxPanel(this, id_panel,wxPoint(0,0),wxSize(800,500));
	panel->SetBackgroundColour(wxColour(120, 120, 120));
	
	map = new Map();

	Centre();
	CreateMenu();
	btnContinue = new wxButton(panel, tmID_CONTINUE, "Continue", wxPoint(360, 451), wxSize(80, 35));
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

void cMain::OnExit(wxCommandEvent& evt)
{
	Close();
}

void cMain::CreateMenu()
{
	menuBar = new wxMenuBar();

	fileMenu = new wxMenu();
	// add items in the file menu
	fileMenu->Append(wxID_NEW, _T("&New game"));
	fileMenu->Append(wxID_OPEN, _T("&Open"));
	fileMenu->AppendSeparator();
	fileMenu->Append(wxID_SAVE, _T("&Save"));
	fileMenu->Append(wxID_SAVEAS, _T("Save &As"));
	fileMenu->AppendSeparator();
	
	fileMenu->Append(wxID_EXIT, _T("E&xit"));

	menuBar->Append(fileMenu, _T("&File"));
	SetMenuBar(menuBar);
}
