#include "cMain.h"
#include "Map.h"
#include "GameSetup.h"

#define id_panel 100
wxBEGIN_EVENT_TABLE(cMain, wxFrame)
//EVT_BUTTON(tmID_CONTINUE, OnContinue)// temporary
EVT_MENU(wxID_EXIT, OnExit)  // file>exit
EVT_MENU(tmID_SOUNDOPTIONS, OnSoundOptions)
EVT_MENU(tmID_SOUNDOFF, OnSoundOnOff)
EVT_MEDIA_LOADED(tmID_MUSICLOADED, OnWAVLoaded)
EVT_MEDIA_FINISHED(tmID_MUSICLOADED, OnWAVFinished)
EVT_IDLE(OnIdle)

wxEND_EVENT_TABLE()

double gdMusicVolume;
cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Town Hall Text Adventure - episode one:  The hunt for Henry", wxDefaultPosition, wxSize(800, 600), wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER & ~wxMAXIMIZE_BOX)
{
	// set the initial music volume - eventually will read the value from a wxConfig

	double dReadVal = -1.0;
	bool bSoundOn = true;
	// create a wxConfig object - in this case an ini file
	IniConfig = new wxFileConfig(wxT(""), wxT(""), wxT("tha.ini"), wxT(""), wxCONFIG_USE_RELATIVE_PATH);
	wxConfigBase::Set(IniConfig);
	IniConfig->EnableAutoSave();
	IniConfig->SetPath(wxT("/Sound"));
	dReadVal = IniConfig->ReadDouble(wxT("MusicVol"), dReadVal);
	if (dReadVal < 0.0)  //not changed.  write the default value
	{
		IniConfig->Write(wxT("MusicVol"), 0.5);
		gdMusicVolume = 0.5;
	}
	else
		gdMusicVolume = dReadVal;

	panel = new wxPanel(this, id_panel, wxPoint(0, 0), wxSize(800, 500));
	panel->SetBackgroundColour(wxColour(120, 120, 120));
	Music = new wxMediaCtrl(this, tmID_MUSICLOADED, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxMEDIABACKEND_WMP10);

	Music->SetVolume(0.0);
	Music->Load(wxT("game.wav"));
	SetMusicVol(gdMusicVolume);

	Centre();
	CreateMenu();
	if (IniConfig->Exists(wxT("SoundOn")))
	{
		bSoundOn = IniConfig->ReadBool(wxT("SoundOn"), bSoundOn);
		soundMenu->Check(tmID_SOUNDOFF, !bSoundOn);
		if (bSoundOn)// the music shouldn't be running

			Music->Play();

		else
			Music->Stop();
	}
	else
		IniConfig->Write(wxT("SoundOn"), true);  // No entry in ini file
	
	txtTitle = new wxTextCtrl(panel, tmID_TITLE, "", wxPoint(250, 20), wxSize(300, 50), wxTE_CENTRE | wxTE_READONLY);
	txtDesc = new wxTextCtrl(panel, tmID_DESCRIPTION, "", wxPoint(100, 100), wxSize(600, 300), wxTE_MULTILINE | wxTE_READONLY);

	fntTitle = new wxFont(26, wxFONTFAMILY_DECORATIVE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Arial");
	fntTitle->AddPrivateFont("England.ttf");
	fntTitle->SetFaceName("England Hand DB");
	txtTitle->SetFont(*fntTitle);
	txtTitle->SetValue(wxT("Test Text"));

	fntDesc = new wxFont(12, wxFONTFAMILY_DECORATIVE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Arial");
	//bool bIsFontAdded = fntDesc->AddPrivateFont("ArchivoNarrow-regular.otf");
	//bool bIsFontUsable = fntDesc->SetFaceName("Archivo Narrow Regular");
	txtDesc->SetFont(*fntDesc);

	txtDesc->SetValue("To begin at the beginning.  It is spring, moonless night in the small town.  Starless, and Bible-black.");
	std::unique_ptr<GameSetup> gSetup(new GameSetup);  // trying out smart pointers
	 //Do all the map stuff
	map = new Map();
	map->LoadMap("tha.map");
	gSetup->InitFirstRun(*map);
}

cMain::~cMain()
{
	if (map != nullptr)
		delete map;
	/*if(IniConfig != nullptr)
		delete IniConfig;*/
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

void cMain::OnSoundOnOff(wxCommandEvent& evt)
{//Switch sounds globally on or off
	if (soundMenu->IsChecked(tmID_SOUNDOFF)) // the item is checked
	{
		Music->Stop();
		IniConfig->Write(wxT("SoundOn"), false);
	}
	else
	{
		Music->Play();
		IniConfig->Write(wxT("SoundOn"), true);
	}
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

void cMain::OnIdle(wxIdleEvent& evt)
{	// music volume
	double ldMusicVolume = Music->GetVolume();
	if (fabs(ldMusicVolume - gdMusicVolume) > 0.05)
	{
		Music->SetVolume(gdMusicVolume);
		// save the value to the ini file
		IniConfig->Write(wxT("MusicVol"), gdMusicVolume);
	}
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
	while (!bComplete)
	{ // the entire game should happen here
		wxSafeYield();
	}
	return bComplete;
}