#include "cMain.h"
#include "Map.h"
#define id_panel 100
wxBEGIN_EVENT_TABLE(cMain, wxFrame)
	EVT_BUTTON(tmID_CONTINUE, OnContinue)// temporary
	EVT_MENU(wxID_EXIT, OnExit)  // file>exit
	EVT_MENU(tmID_SOUNDOPTIONS, OnSoundOptions)
	EVT_MEDIA_LOADED(tmID_MUSIC, OnWAVLoaded)
	
wxEND_EVENT_TABLE()

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Town Hall Text Adventure - episode one:  The hunt for Henry", wxDefaultPosition, wxSize(800, 600), wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER & ~wxMAXIMIZE_BOX)
{
	panel = new wxPanel(this, id_panel,wxPoint(0,0),wxSize(800,500));
	panel->SetBackgroundColour(wxColour(120, 120, 120));
	
	map = new Map();
	Music = new wxMediaCtrl(this, tmID_MUSIC,wxEmptyString,wxDefaultPosition,wxDefaultSize, 0,wxMEDIABACKEND_DIRECTSHOW);
	Music->Load(wxT("game.wav"));
	//wxSound Sound;
	//Sound.Play(wxT("game.wav"));

	
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

void cMain::OnSoundOptions(wxCommandEvent& evt)
{//  Create a new SoundOptions wxFrame
	soundWindow = new SoundOptions();
	soundWindow->Show();
	evt.Skip();
}

void cMain::OnWAVLoaded(wxMediaEvent& evt)
{
	
	Music->Play();
	evt.Skip();
}

void cMain::OnWAVFinished(wxMediaEvent& evt)
{
//	Music->Play();
	evt.Skip();
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
	soundMenu = new wxMenu();
	soundMenu->Append(tmID_SOUNDOPTIONS, _T("Sound &Options"));
	soundMenu->AppendSeparator();
	soundMenu->AppendCheckItem(tmID_SOUNDOFF, _T("Silent Mode"));
	menuBar->Append(soundMenu, _T("Sounds"));
	SetMenuBar(menuBar);
}
