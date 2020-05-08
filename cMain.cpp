#include "cMain.h"
#include "Map.h"
#define id_panel 100
wxBEGIN_EVENT_TABLE(cMain, wxFrame)
EVT_BUTTON(tmID_CONTINUE, OnContinue)// temporary
EVT_MENU(wxID_EXIT, OnExit)  // file>exit
EVT_MENU(tmID_SOUNDOPTIONS, OnSoundOptions)
EVT_MEDIA_LOADED(tmID_MUSICLOADED, OnWAVLoaded)
EVT_MEDIA_FINISHED(tmID_MUSICLOADED, OnWAVFinished)


wxEND_EVENT_TABLE()
double gdMusicVolume;
cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Town Hall Text Adventure - episode one:  The hunt for Henry", wxDefaultPosition, wxSize(800, 600), wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER & ~wxMAXIMIZE_BOX)
{
	// set the initial music volume - eventually will read the value from a wxConfig
	gdMusicVolume = 0.2;
	panel = new wxPanel(this, id_panel,wxPoint(0,0),wxSize(800,500));
	panel->SetBackgroundColour(wxColour(120, 120, 120));
	SetIcon(wxIcon("icon.ico"));
	
	map = new Map();
	Music = new wxMediaCtrl(this, tmID_MUSICLOADED,wxEmptyString,wxDefaultPosition,wxDefaultSize, 0,wxMEDIABACKEND_WMP10);
		
	Music->SetVolume(0.0);
	Music->Load(wxT("game.wav"));
	SetMusicVol(gdMusicVolume);
		
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
	GameLoop();
	evt.Skip();
}

void cMain::OnExit(wxCommandEvent& evt)
{
	bComplete = true;  // exit the game loop
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
	Music->SetVolume(1.0);
	
	Music->Play();
	SetMusicVol(gdMusicVolume);
	
	evt.Skip();
}

void cMain::OnWAVFinished(wxMediaEvent& evt)
{
	Music->Play();
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

void cMain::SetMusicVol(double dVal)
{
	Music->SetVolume(dVal);
}

bool cMain::GameLoop()
{
	bComplete = false; // strictly speaking, doesn't need to be set false, but it makes the code more readable
	while(!bComplete)
	{ 
		wxYield();
		Music->SetVolume(gdMusicVolume);
	}
	return bComplete;
}


