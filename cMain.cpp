///////////////////////////////////////////////////////////////////////////////
//								  cMain.cpp                                  //
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
//    This file defines a wxFrame object, which controls the flow of the.    //
//    Application.  This is the equivalent of int main().                    //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
#include "cMain.h"

#include "GameSetup.h"

#define id_panel 100
wxBEGIN_EVENT_TABLE(cMain, wxFrame)
EVT_MENU(wxID_EXIT, OnExit)  // file>exit
EVT_MENU(tmID_SOUNDOPTIONS, OnSoundOptions)
EVT_MENU(tmID_SOUNDOFF, OnSoundOnOff)
EVT_MEDIA_LOADED(tmID_MUSICLOADED, OnWAVLoaded)
EVT_MEDIA_FINISHED(tmID_MUSICLOADED, OnWAVFinished)
EVT_IDLE(OnIdle)
EVT_TIMER(tmID_LOOPTIMER, OnGameLoop)
// the nav buttons
EVT_BUTTON(tmID_NORTH, OnNorth)
EVT_BUTTON(tmID_EAST, OnEast)
EVT_BUTTON(tmID_SOUTH, OnSouth)
EVT_BUTTON(tmID_WEST, OnWest)
EVT_BUTTON(tmID_UP, OnUp)
EVT_BUTTON(tmID_DOWN, OnDown)
wxEND_EVENT_TABLE()

double gdMusicVolume;
cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Town Hall Text Adventure - episode one:  The hunt for Henry", wxDefaultPosition, wxSize(800, 600), wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER & ~wxMAXIMIZE_BOX)
{
	SetGameRunning(false);
	double dReadVal = -1.0;
	bool bSoundOn = true;
	std::unique_ptr<GameSetup> gSetup(new GameSetup);  // trying out smart pointers

	// create a wxConfig object - in this case an ini file
	IniConfig = new wxFileConfig(wxT(""), wxT(""), (gSetup->GetIniFileName()), wxT(""), wxCONFIG_USE_RELATIVE_PATH);

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

	panel = new wxPanel(this, id_panel, wxPoint(0, 0), wxSize(800, 600));
	panel->SetBackgroundColour(wxColour(120, 120, 120));
	Music = new wxMediaCtrl(this, tmID_MUSICLOADED, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxMEDIABACKEND_WMP10);

	Music->Load(gSetup->GetMusicFile());

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

	txtTitle = new wxTextCtrl(panel, tmID_TITLE, "", wxPoint(150, 20), wxSize(500, 50), wxTE_CENTRE | wxTE_READONLY);
	txtDesc = new wxTextCtrl(panel, tmID_DESCRIPTION, "", wxPoint(50, 100), wxSize(700, 300), wxTE_MULTILINE | wxTE_CENTRE | wxTE_READONLY);

	fntTitle = new wxFont(26, wxFONTFAMILY_DECORATIVE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Arial");
	fntTitle->AddPrivateFont(gSetup->GetTitleFont());
	fntTitle->SetFaceName(gSetup->GetTitleFaceName());
	txtTitle->SetFont(*fntTitle);
	txtTitle->SetValue(wxT("Test Text"));

	fntDesc = new wxFont(16, wxFONTFAMILY_DECORATIVE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Arial");

	txtDesc->SetFont(*fntDesc);

	btnN = new wxButton(panel, tmID_NORTH, wxT("N"), wxPoint(628, 425), wxSize(25, 25));
	btnE = new wxButton(panel, tmID_EAST, wxT("E"), wxPoint(678, 450), wxSize(25, 25));
	btnS = new wxButton(panel, tmID_SOUTH, wxT("S"), wxPoint(628, 475), wxSize(25, 25));
	btnW = new wxButton(panel, tmID_WEST, wxT("W"), wxPoint(578, 450), wxSize(25, 25));
	btnU = new wxButton(panel, tmID_UP, wxT("U"), wxPoint(725, 425), wxSize(25, 32));
	btnD = new wxButton(panel, tmID_DOWN, wxT("D"), wxPoint(725, 470), wxSize(25, 32));
	wxArrayString opts;

	opts.Add(wxT("Eat"));
	opts.Add(wxT("Drink"));
	opts.Add(wxT("Take"));
	opts.Add(wxT("Drop"));
	opts.Add(wxT("Use"));
	opts.Add(wxT("Talk"));
	opts.Add(wxT("Destroy"));
	rbOptions = new wxRadioBox(panel, tmID_RADIOBOX, wxT("Options"), wxPoint(100, 410), wxSize(450, 60), opts);

	btnGo = new wxButton(panel, tmID_GOBUTTON, wxT("&GO!"), wxPoint(100, 480), wxSize(450, 50));
	//Do all the map stuff
	map = new Map();
	map->LoadMap(gSetup->GetMapName());
	gSetup->InitFirstRun(*map);
	PrologueData = gSetup->Prologue();
	EpilogueData = gSetup->Epilogue();
	SetGameRunning(true);
	bRefresh = true;
	loopTimer = new wxTimer(this, tmID_LOOPTIMER);
	loopTimer->Start(30);
}

cMain::~cMain()
{
	if (map != nullptr)
	{
		delete map;

		map = nullptr;
	}
	if (fntDesc != nullptr)
	{
		delete fntDesc;
		fntDesc = nullptr;
	}
	if (fntTitle != nullptr)
	{
		delete fntTitle;
		fntTitle = nullptr;
	}
	if (loopTimer != nullptr)
	{
		delete loopTimer;
		loopTimer = nullptr;
	}
}

void cMain::OnExit(wxCommandEvent& evt)
{
	bComplete = true;  // exit the game loop
	SetGameRunning(false);
	
	Close();
}

bool cMain::MainLoop()
{
	txtTitle->Clear();
	txtDesc->Clear();
	txtDesc->SetDefaultStyle(wxTextAttr(wxTE_MULTILINE  |  wxTE_READONLY));
	
	while (GetGameRunning())
	{//  process the entire game loop from within here.  Return true if the game is completed
		if (bComplete || !bRefresh)
		{
			wxYield();
			if (!GetGameRunning())
			{//  should allow us to drop out of the main loop

				return true;
			}
		}
		else
		{
			CurrentMapNode = *(map->GetMapNodeByID(CurrentRoom));
			EnableSelectedNavButtons(CurrentMapNode.GetAllExits());
			txtTitle->SetValue(CurrentMapNode.GetTitle());
			txtDesc->SetValue(CurrentMapNode.GetDesc());
			bRefresh = false;
			wxYield();
			// give textual info about exits
			
		}
		
	}
	
	return false;
}

void cMain::DisableAllNavButtons()
{
	btnN->Enable(false);
	btnE->Enable(false);
	btnS->Enable(false);
	btnW->Enable(false);
	btnU->Enable(false);
	btnD->Enable(false);

}

void cMain::EnableSelectedNavButtons(uint16_t buttons)
{//  Enable only the buttons for which there is a legal exit
	DisableAllNavButtons();
	
	
	if (buttons & North)
		btnN->Enable(true);
	if (buttons & East)
		btnE->Enable(true);
	if (buttons & South)
		btnS->Enable(true);
	if (buttons & West)
		btnW->Enable(true);
	if (buttons & Up)
		btnU->Enable(true);
	if (buttons & Down)
		btnD->Enable(true);
	
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
	evt.Skip();
}

void cMain::OnWAVLoaded(wxMediaEvent& evt)
{
	Music->SetVolume(0.05);
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
		//ShowPrologue();
	}

	evt.Skip();
}

void cMain::OnGameLoop(wxTimerEvent& evt)
{
	if (!PrologueDone)
	{// stop the timer, show the prologue (which takes several seconds) and then restart the timer.
		loopTimer->Stop();
#ifndef NOPROLOGUE
		ShowPrologue();
#endif
		PrologueDone = true;
		loopTimer->Start(30);
		SetGameRunning(true);
		return;
	}
	// if we've got this far, we don't need the timer anymore.
	// We can kill it and start the 'real' game loop
	if (GetGameRunning())
	{
		loopTimer->Stop();
		MainLoop();
	}
}

void cMain::OnNorth(wxCommandEvent& evt)
{// set bRefresh
	bRefresh = true;
	CurrentRoom = CurrentMapNode.GetExit(0);
}
void cMain::OnEast(wxCommandEvent& evt)
{// set bRefresh
	bRefresh = true;
	CurrentRoom = CurrentMapNode.GetExit(1);
}
void cMain::OnSouth(wxCommandEvent& evt)
{// set bRefresh
	bRefresh = true;
	CurrentRoom = CurrentMapNode.GetExit(2);
}
void cMain::OnWest(wxCommandEvent& evt)
{// set bRefresh
	bRefresh = true;
	CurrentRoom = CurrentMapNode.GetExit(3);
}
void cMain::OnUp(wxCommandEvent& evt)
{// set bRefresh
	bRefresh = true;
	CurrentRoom = CurrentMapNode.GetExit(4);
}
void cMain::OnDown(wxCommandEvent& evt)
{// set bRefresh
	bRefresh = true;
	CurrentRoom = CurrentMapNode.GetExit(5);
}

void cMain::ShowPrologue()
{//  Display the prologue info
	txtTitle->Clear();
	txtTitle->SetValue(wxString("Prologue"));
	txtDesc->Clear();
	for (auto i = PrologueData.begin(); i != PrologueData.end(); i++)
	{//  need keypress detection, so that the prologue can be cancelled
		txtDesc->AppendText(*i);
		txtDesc->HideNativeCaret();
		wxYield();
		wxSleep(2);
	}
	wxSleep(3);
	txtDesc->Clear();
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

void cMain::ClearTitle()
{
	txtTitle->Clear();
}
void cMain::ClearDesc()
{
	txtDesc->Clear();
}

void cMain::SetTitle(std::string title)
{
	ClearTitle();
	this->txtTitle->SetValue(wxString(title));
}

void cMain::AddToDesc(std::string words)
{
	txtDesc->AppendText(wxString(words));
}

void cMain::SetGameRunning(bool isRunning)
{
	
	GameRunning = isRunning;
}
