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
//                                                                           //
//    You should have received a copy of the GNU General Public License      //
//    along with this program.If not, see < https://www.gnu.org/licenses/>.  //
//                                                                           //
//                     Tim Muston  tim@tmuston.co.uk                         //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
//                                                                           //                                                                           //
//                                                                           //
//    This file defines a wxFrame object, which controls the flow of the.    //
//    Application.  This is the equivalent of int main().                    //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
#include "wx/dir.h"
#include "wx/html/helpctrl.h"
#include "GameSetup.h"
#include "cMain.h"
#include "version.h"





#define id_panel 100
wxBEGIN_EVENT_TABLE(cMain, wxFrame)
EVT_MENU(wxID_EXIT, OnExit)  // file>exit
EVT_MENU(wxID_NEW, OnNew)  // file>exit
EVT_MENU(wxID_SAVE, OnSave)
EVT_MENU(wxID_OPEN, OnOpen)
EVT_MENU(wxID_HELP, OnHelpAbout)
EVT_MENU(tmID_SOUNDOPTIONS, OnSoundOptions)
EVT_MENU(tmID_SOUNDOFF, OnSoundOnOff)
EVT_MEDIA_LOADED(tmID_MUSICLOADED, OnWAVLoaded)
EVT_MEDIA_LOADED(tmID_SFXLOADED, OnSFXLoaded)
EVT_MEDIA_FINISHED(tmID_MUSICLOADED, OnWAVFinished)
EVT_IDLE(OnIdle)
EVT_TIMER(tmID_LOOPTIMER, OnGameLoop)
EVT_TIMER(tmID_HEALTHTIMER, OnHealthTimer)
// the nav buttons
EVT_BUTTON(tmID_NORTH, OnNorth)
EVT_BUTTON(tmID_EAST, OnEast)
EVT_BUTTON(tmID_SOUTH, OnSouth)
EVT_BUTTON(tmID_WEST, OnWest)
EVT_BUTTON(tmID_UP, OnUp)
EVT_BUTTON(tmID_DOWN, OnDown)
EVT_BUTTON(tmID_GOBUTTON, OnDoIt)
EVT_BUTTON(tmID_PLAYERBUTTON, OnPlayerButton)
EVT_KEY_DOWN(OnKeyDown)
EVT_LISTBOX_DCLICK(tmID_LISTBOX, OnDoIt)
EVT_LISTBOX_DCLICK(tmID_PLAYERLISTBOX, OnPlayerButton)

wxEND_EVENT_TABLE()

double gdMusicVolume;
double gdSfxVolume;
bool gSoundOptions;
cMain::cMain() : wxFrame(nullptr, wxID_ANY, "EGM Game Engine", wxDefaultPosition, wxSize(800, 600), wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER & ~wxMAXIMIZE_BOX)
{
	player = new Player("");
	map = new Map();
	gSoundOptions = false;
	SetGameRunning(false);
	double dReadVal = -1.0;
	double dSfxVal = -1.0;
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
	
	
	dSfxVal = IniConfig->ReadDouble(wxT("SfxVol"), dReadVal);
	if (dSfxVal < 0.0)  //not changed.  write the default value
	{
		IniConfig->Write(wxT("SfxVol"), 0.5);
		gdSfxVolume = 0.5;

	}
	else
		gdSfxVolume = dSfxVal;


	panel = new wxPanel(this, id_panel, wxPoint(0, 0), wxSize(800, 600));
	panel->SetBackgroundColour(wxColour(120, 120, 160));
	
	Music = new wxMediaCtrl(this, tmID_MUSICLOADED, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, MEDIA_BACKEND);
	
	Sfx = new wxMediaCtrl(this, tmID_SFXLOADED, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, MEDIA_BACKEND);
	Music->SetVolume(0.0);
	Music->Load(gSetup->GetMusicFile());
	EndChimeFilename = gSetup->GetEndChimeFile();
	GameLostMusic = gSetup->GetGameLostFile();
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

	txtTitle = new wxTextCtrl(panel, tmID_TITLE, "", wxPoint(150, 10), wxSize(500, 50), wxTE_CENTRE | wxTE_READONLY);
	txtDesc = new wxTextCtrl(panel, tmID_DESCRIPTION, "", wxPoint(50, 70), wxSize(700, 260), wxTE_MULTILINE | wxTE_READONLY);

	fntTitle = new wxFont(26, wxFONTFAMILY_DECORATIVE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Arial");
	fntTitle->AddPrivateFont(gSetup->GetTitleFont());
	fntTitle->SetFaceName(gSetup->GetTitleFaceName());
	txtTitle->SetFont(*fntTitle);
	txtTitle->SetToolTip(wxT("This is the name of the current location"));
	
	fntDesc = new wxFont(14, wxFONTFAMILY_DECORATIVE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Arial");
	fntPlayerInfo = new wxFont(10, wxFONTFAMILY_DECORATIVE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "Arial");
	txtDesc->SetFont(*fntDesc);
	txtDesc->SetToolTip(wxT("This window describes the action of the game"));
	// player stuff

	box = new wxStaticBox(panel, wxID_ANY, "Player information", wxPoint(50, 340), wxSize(700, 80));
	lblPlayerName = new wxStaticText(panel, tmID_PLAYERNAME, wxT("Player Name:"), wxPoint(70, 360), wxSize(100, 20));
	lblPlayerHealth = new wxStaticText(panel, tmID_PLAYERHEALTH, wxT("Player Health:"), wxPoint(70, 380), wxSize(100, 20));
	lblPlayerName->SetFont(*fntPlayerInfo);
	lblPlayerHealth->SetFont(*fntPlayerInfo);
	btnPlayer = new wxButton(panel, tmID_PLAYERBUTTON, wxT("Do it!"), wxPoint(630, 360), wxSize(100, 40));
	lbPlayerItems = new wxListBox(panel, tmID_PLAYERLISTBOX, wxPoint(250,360), wxSize(370,50));
	lbPlayerItems->SetToolTip(wxT("Select an option from the list, and press the button to the right"));
	btnN = new wxButton(panel, tmID_NORTH, wxT("N"), wxPoint(628, 435), wxSize(25, 25));
	btnE = new wxButton(panel, tmID_EAST, wxT("E"), wxPoint(678, 460), wxSize(25, 25));
	btnS = new wxButton(panel, tmID_SOUTH, wxT("S"), wxPoint(628, 485), wxSize(25, 25));
	btnW = new wxButton(panel, tmID_WEST, wxT("W"), wxPoint(578, 460), wxSize(25, 25));
	btnU = new wxButton(panel, tmID_UP, wxT("U"), wxPoint(725, 435), wxSize(25, 32));
	btnD = new wxButton(panel, tmID_DOWN, wxT("D"), wxPoint(725, 480), wxSize(25, 32));
	btnN->SetToolTip(wxT("Go North"));
	btnE->SetToolTip(wxT("Go East"));
	btnS->SetToolTip(wxT("Go South"));
	btnW->SetToolTip(wxT("Go West"));
	btnU->SetToolTip(wxT("Go Up"));
	btnD->SetToolTip(wxT("Go Down"));
	lbItems = new wxListBox(panel, tmID_LISTBOX, wxPoint(100, 430), wxSize(450, 50));
	lbItems->SetFont(*fntDesc);
	lbItems->SetToolTip(wxT("Select an option from the list, and press the button below"));
	lbPlayerItems->SetFont(*fntDesc);
	lbItems->Show(false);
	
	btnGo = new wxButton(panel, tmID_GOBUTTON, wxT("Do it!"), wxPoint(100, 490), wxSize(450, 40));
	btnGo->Enable(false);
	//Do all the map stuff
	 
	map->LoadMap(gSetup->GetMapName());
	
	gSetup->InitFirstRun(*map, *player);
	player->SetMap(map);
	gSetup->SetMap(map);
	NewOrOpen();
	wxString NameText = "Player Name: " + player->GetName();
	wxString HealthText = "Player Health: " + wxString::Format(wxT("%u"), player->GetHealth());
	bPlayerRefresh = true;
	wxTopLevelWindow::SetTitle(gSetup->GetGameTitle());
	UpdatePlayerListBox();
	
	lblPlayerName->SetLabelText(NameText);
	lblPlayerName->SetToolTip(wxT("The player's name"));
	lblPlayerHealth->SetLabelText(HealthText);
	lblPlayerHealth->SetToolTip(wxT("The player's level of health.  If this reaches zero, it's goodnight Vienna"));
	PrologueData = gSetup->Prologue();
	EpilogueData = gSetup->Epilogue();
	GameOverData = gSetup->GameOver();

	SetGameRunning(true);
	bRefresh = true;
	loopTimer = new wxTimer(this, tmID_LOOPTIMER);
	loopTimer->Start(30);
	healthTimer = new wxTimer(this, tmID_HEALTHTIMER);
	//  for testing healthTimer->Start(100);
	healthTimer->Start(30000);

	
	
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
	if (fntPlayerInfo != nullptr)
	{
		delete fntPlayerInfo;
		fntPlayerInfo = nullptr;
	}
	if (loopTimer != nullptr)
	{
		delete loopTimer;
		loopTimer = nullptr;
	}
	if (healthTimer != nullptr)
	{
		delete healthTimer;
		healthTimer = nullptr;
	}
	if (player != nullptr)
	{
		delete player;
		player = nullptr;
	}
	if (game != nullptr)
	{
		delete game;
		game = nullptr;
	}

	if (IniConfig != nullptr)
	{
		delete IniConfig;
		IniConfig = nullptr;
	}
}

void cMain::OnExit(wxCommandEvent& evt)
{
	
	bComplete = true;  // exit the game loop
	PrologueDone = true;
	SetGameRunning(false);
	
	Close();
}

void cMain::OnNew(wxCommandEvent& evt)
{// bring up the new dialog
	StartWindow = new StartDialog(this, wxID_ANY, "Welcome", wxDefaultPosition, wxSize(400, 300));
	StartWindow->ShowModal();
	std::string PlayerName = StartWindow->GetText().ToStdString();
	StartWindow->Destroy();
	delete player;
	player = new Player(PlayerName);
	// Lots of stuff needs to happen if we're here
	delete map;
	map = new Map();
	std::unique_ptr<GameSetup> gSetup(new GameSetup);
	map->LoadMap(gSetup->GetMapName());
	vItemInfo.clear();
	ZeroItemID();
	gSetup->InitFirstRun(*map, *player);
	player->SetMap(map);
	gSetup->SetMap(map);
	wxString NameText = "Player Name: " + player->GetName();
	wxString HealthText = "Player Health: " + wxString::Format(wxT("%u"), player->GetHealth());
	lblPlayerName->SetLabelText(NameText);
	lblPlayerHealth->SetLabelText(HealthText);
	CurrentRoom = 1;
	
	bRefresh = true;
	bPlayerRefresh = true;
	evt.Skip();
}

void cMain::OnOpen(wxCommandEvent& evt)
{//  open an existing game
	wxDir d(wxStandardPaths::Get().GetUserLocalDataDir());
	wxString fName;
	bool bSaveExists = d.GetFirst(&fName, wxT("*.sav"));
	if (bSaveExists)
	{
		wxFileDialog OpenDialog(
			this, _("Choose a saved game file to open"), d.GetName(), wxEmptyString,
			_("Save files (*.sav)|*.sav"),
			wxFD_OPEN, wxDefaultPosition);

		if (OpenDialog.ShowModal() == wxID_OK) // if the user clicks "Open" instead of "Cancel"
		{
			wxString wxFile = OpenDialog.GetPath(); // Set the Title to reflect the file open
			game = new GameState(*player, *map);
			uint16_t tmpNodeID;
			game->LoadFromFile(wxFile.ToStdString(), &tmpNodeID);
			bGameSaved = true;
			CurrentRoom = tmpNodeID;
			delete game;
			game = nullptr;
			PrologueDone = true;  // don't run the prologue
			bRefresh = true;
			//evt.Skip();
			return;
		}// if the dialog was cancelled, carry on
	}
	else
		wxMessageBox("There are no saved games to open", "Ooops");
	evt.Skip();
}

void cMain::OnSave(wxCommandEvent& evt)
{//save the game state 
	uint16_t nodeID = CurrentMapNode.GetID();
	
	game = new GameState(*player, *map);

	game->SaveToFile(nodeID);
	bGameSaved = true;
	delete game;
	game = nullptr;
	evt.Skip();
}

void cMain::OnHelpAbout(wxCommandEvent& evt)
{
	std::string Message = "EGM Game engine version "+ (std::string)VERSION_MAJOR + VERSION_MINOR;
	wxMessageBox(Message, "About ...");
	evt.Skip();
}

bool cMain::MainLoop()
{ /////////////////////////////////////////////
 // This function is the 'guts' of the game  /
/////////////////////////////////////////////
	txtTitle->Clear();
	txtDesc->Clear();
	txtDesc->SetDefaultStyle(wxTextAttr(wxTE_MULTILINE  |  wxTE_READONLY));
	
	while ( GetGameRunning() == true)
	{//  process the entire game loop from within here.  Return true if the game is completed
		uint16_t PlayerHealth = player->GetHealth();
		wxString HealthText = "Player Health: " + wxString::Format(wxT("%u"), PlayerHealth);
		
		
		if (PlayerHealth < 25)  //  give a warning if health is getting low
		{
			wxColour colour;
			colour.Set(180, 0, 0);  // the standard wxRED was too vivid
			lblPlayerHealth->SetForegroundColour(colour);
		}
		else
			lblPlayerHealth->SetForegroundColour(*wxBLACK);

		lblPlayerHealth->SetLabelText(HealthText);
		if(PlayerHealth < 1)  // the player died
		{
			bRefresh = false;
			ShowGameOver();
			return true;
		}
		if (bRefresh == true)
		{
			if (bGameSaved == true)
				bGameSaved = false;
			uint16_t exits;
			CurrentMapNode = *(map->GetMapNodeByID(CurrentRoom));
			exits = CurrentMapNode.GetAllExits();
			EnableSelectedNavButtons(exits);
			txtTitle->SetValue(CurrentMapNode.GetTitle());
			txtDesc->SetValue(CurrentMapNode.GetDesc());
			UpdatePlayerListBox();
			bPlayerRefresh = false;
			bRefresh = false;
			wxYield();
			
			// give textual info about Items
			if (WriteItemInfo())  // there are items
				ProcessItems();
			else
			{
				lbItems->Clear();
				lbItems->Show(false);  //  we don't want no steenkin listbox
			}
			if (exits > 0)
				WriteExitInfo(exits);
		}
		else  // no need to update yet
			wxYield();
		
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

void cMain::WriteExitInfo(uint16_t info)
{// write the info on the availablr exits to txtDesc
	// sanity check
	if (0 == info)
		return;
	txtDesc->AppendText(wxT("\n\n\tAvailable exits:\n\n"));

	if (info & North)
		txtDesc->AppendText(wxT("\tNorth"));
	if (info & South)
		txtDesc->AppendText(wxT("\tSouth"));
	if (info & East)
		txtDesc->AppendText(wxT("\tEast"));
	if (info & West)
		txtDesc->AppendText(wxT("\tWest"));
	if (info & Up)
		txtDesc->AppendText(wxT("\tUp"));
	if (info & Down)
		txtDesc->AppendText(wxT("\tDown"));

}

bool cMain::WriteItemInfo()
{// write all the Items in the node to txtDesc - assuming any exist
	std::vector<Item> things;
	bool bAnyItems = CurrentMapNode.GetItems(things);
	lbItems->Clear();
	lbItems->Show(false);
	if (!bAnyItems)// nothing to see here
	{
		
		btnGo->Enable(false);
		return false;
	}
	txtDesc->AppendText(wxT("\nThis place contains :\n"));
	for (std::vector<Item>::iterator it = things.begin(); it != things.end(); ++it)
	{
		std::string s = it->GetDescription();
		txtDesc->AppendText(s);
		txtDesc->AppendText(wxT("\n"));
	}
	btnGo->Enable(true);
	return true;
}

void cMain::ProcessItems()
{
	std::vector<Item> lItems;
	CurrentMapNode.GetItems(lItems);
	uint16_t uId = 0;
	uint16_t uAction = 0;
	std::string sItemName = "";
	std::string sAction = "";
	// clear out the vItemInfo vector
	vItemInfo.clear();
	
	std::vector<Item>::iterator it;
	for (it = lItems.begin(); it != lItems.end(); ++it)
	{ // get all of the item IDs
		uId = it->GetID();
		uAction = it->GetProperties();
		auto tup = std::make_tuple(uId, uAction);
		vItemInfo.push_back(tup);
		sItemName = it->GetName(); 
			
		
		if (uAction & Eatable)
		{
			sAction = "Eat " + sItemName;
			lbItems->AppendString(sAction);
		}
		if (uAction & Drinkable)
		{
			sAction = "Drink " + sItemName;
			lbItems->AppendString(sAction);
		}
		if (uAction & Takeable)
		{
			sAction = "Take " + sItemName;
			lbItems->AppendString(sAction);
		}
		
		if (uAction & Usable)
		{
			sAction = "Use " + sItemName;
			lbItems->AppendString(sAction);
		}
		if (uAction & Talkable)
		{
			sAction = "Question " + sItemName;
			lbItems->AppendString(sAction);
		}
		if (uAction & Killable)
		{
			sAction = "Kill " + sItemName;
			lbItems->AppendString(sAction);
		}
		

	}
	lbItems->Show(true);
	
}

void cMain::NewOrOpen()
{// If no saved games exist, ask for a player name
 // otherwise ask which saved game to load
 	wxDir d(wxStandardPaths::Get().GetUserLocalDataDir());
	
	wxString fName;
	bool bSaveExists = d.GetFirst(&fName, wxT("*.sav"));
	if(bSaveExists)
	{
		wxFileDialog OpenDialog(
			this, _("Choose a saved game file to open"), d.GetName(), wxEmptyString,
			_("Save files (*.sav)|*.sav"),
			wxFD_OPEN, wxDefaultPosition);

		if (OpenDialog.ShowModal() == wxID_OK) // if the user clicks "Open" instead of "Cancel"
		{
			wxString wxFile = OpenDialog.GetPath(); // Set the Title to reflect the file open
			game = new GameState(*player, *map);
			uint16_t tmpNodeID;
			game->LoadFromFile(wxFile.ToStdString(), &tmpNodeID);
			bGameSaved = true;
			CurrentRoom = tmpNodeID;
			delete game;
			game = nullptr;
			PrologueDone = true;  // don't run the prologue
			bRefresh = true;
			return;
		}
	}
	else // Offer the option to start a new game
	{
		StartWindow = new StartDialog(this, wxID_ANY, "Welcome - first run of the game", wxDefaultPosition, wxSize(400, 200));
		StartWindow->ShowModal();
		
		player->SetName(StartWindow->GetText().ToStdString());
		StartWindow->Destroy();
		
	}
	
}

void cMain::FlashPanel()
{//  flash the panel to indicate something has happened
	for (uint16_t i = 0; i < 255; i+=16)
	{
		panel->SetBackgroundColour(wxColour(i, 127, i));
		panel->Refresh();
		::wxYield();
	}
	panel->SetBackgroundColour(wxColour(120, 120, 160));
	panel->Refresh();
	::wxYield();
}

void cMain::FlashPanelBlack()
{
	for (uint16_t i = 0; i < 5; i++)
	{
		panel->SetBackgroundColour(wxColour(0, 0, 0));
		panel->Refresh();
		wxMilliSleep(60);
		::wxYield();
		panel->SetBackgroundColour(wxColour(255, 255, 255));
		panel->Refresh();
		wxMilliSleep(60);
		::wxYield();

	}
	panel->SetBackgroundColour(wxColour(120, 120, 160));
	panel->Refresh();
}

void cMain::PlaySFX(std::string fName)
{
	Sfx->Load(fName);
}

void cMain::WaitForAnyKey()
{
	bRefresh = false;
	
	EnableCloseButton(false);
	fileMenu->Enable(wxID_EXIT, false);
	soundMenu->Enable(tmID_SOUNDOPTIONS, false);
	helpMenu->Enable(wxID_HELP, false);

	AddToDesc("\n\n\t\t Press any key to continue ...");

	while (!bRefresh)
	{
		this->SetFocus();
		wxYield();
		
		wxMilliSleep(10);

	}
	//txtDesc->SetForegroundColour(*wxBLACK);
	
	EnableCloseButton(true);
	fileMenu->Enable(wxID_EXIT, true);
	soundMenu->Enable(tmID_SOUNDOPTIONS, true);
	helpMenu->Enable(wxID_HELP, true);
}

void cMain::StartNewGame()
{
	RestartWindow = new RestartDialog(this, wxID_ANY, "Choose a new player name, or press Exit to leave", wxDefaultPosition, wxSize(400, 200));
	//if (RestartWindow->ShowModal() == wxID_CANCEL)
	int retval = RestartWindow->ShowModal();
	if (wxID_CANCEL == retval)
	{
		RestartWindow->Destroy();
		FadeMusic();
		wxMessageBox("Byee!", "Thank you for playing");
		Close();
	}
	
	player->SetName(RestartWindow->GetText().ToStdString());
	RestartWindow->Destroy();
}

void cMain::EnableCurrentMapNodeExit(uint16_t num, uint16_t room)
{// change the room that a MamNode's Exits point towards, or alternatively disable that exit
	CurrentMapNode.SetExit(num-1, room);
	map->Replace(CurrentMapNode);
}

bool cMain::ReduceEnemyHealth(uint16_t h)
{
	uint16_t health = GetEnemyHealth();
	if (health  < 1)
	
		return false;
	EnemyHealth -= h;
	return true;

	
}


void cMain::OnSoundOptions(wxCommandEvent& evt)
{//  Create a new SoundOptions wxFrame
	soundWindow = new SoundOptions();
	//bSoundOptionsActive = true;
	soundWindow->Show();
	//bSoundOptionsActive = false;

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
	Music->SetVolume(0.0);
	Music->Play();
	SetMusicVol(gdMusicVolume);

	evt.Skip();
}

void cMain::OnSFXLoaded(wxMediaEvent& evt)
{
	Sfx->SetVolume(gdSfxVolume);
	Sfx->Play();
	

	evt.Skip();
}

void cMain::OnWAVFinished(wxMediaEvent& evt)
{
	Music->Play();
	evt.Skip();
}

void cMain::OnIdle(wxIdleEvent& evt)
{	// music volume
	if (Music != nullptr)  // stop the application from crashing if the media control hasn't yet been created
	{
		double ldMusicVolume = Music->GetVolume();
		if (fabs(ldMusicVolume - gdMusicVolume) > 0.05)
		{
			Music->SetVolume(gdMusicVolume);
			// save the value to the ini file
			IniConfig->Write(wxT("MusicVol"), gdMusicVolume);
			
		}

		double ldSfxVolume = Sfx->GetVolume();
		if (fabs(ldSfxVolume - gdSfxVolume) > 0.05)
		{
			Sfx->SetVolume(gdSfxVolume);
			// save the value to the ini file
			IniConfig->Write(wxT("SfxVol"), gdSfxVolume);
			if(gSoundOptions)
				PlaySFX("ting.wav");

		}
	
	}
	evt.Skip();
}

void cMain::OnGameLoop(wxTimerEvent& evt)
{
	//evt.Skip();
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

void cMain::OnHealthTimer(wxTimerEvent& evt)
{
	if (player != nullptr)
		player->RemoveHealth(1);
	evt.Skip();
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

void cMain::OnDoIt(wxCommandEvent& evt)
{// Do something when the 'do it' button is pressed.
	wxString ListItem = lbItems->GetStringSelection();
	if (ListItem == wxT(""))
	{ // this code should never fire
		wxMessageBox(wxT("You need to select an action from the list"), wxT("Ooops!"));
		return;
	}
	//  now comes the fun part.  Figure out which action of which item to perform, and
	// adjust Item, player and MapNode accordingly
	uint16_t uId =0, uActions =0;

	// get the ItemID from the listbox selection by nefarious means
	uint16_t uListBoxID = CurrentMapNode.GetItemIdFromName(std::string((lbItems->GetStringSelection())));
	for (size_t i = 0; i < vItemInfo.size(); ++i)
	{
		uId = std::get<0>(vItemInfo[i]);
		if (uId == uListBoxID)
		{
			uActions = std::get<1>(vItemInfo[i]);  // available actions
			break;
		}
	}
		
	std::string ActionString = ListItem.ToStdString();
	size_t len = ActionString.std::string::find_first_of(" ");
	ActionString = ActionString.substr(0, len);
	ProcessItemAction(uId, ActionString, uActions);

	evt.Skip();
}

void cMain::OnPlayerButton(wxCommandEvent& evt)
{
	wxString ListItem = lbPlayerItems->GetStringSelection();
	if (ListItem == wxT(""))
	{ // this code should never fire
		wxMessageBox(wxT("You need to select an action from the list"), wxT("Ooops!"));
		return;
	}
	//  now comes the fun part.  Figure out which action of which item to perform, and
	// adjust Item, player and MapNode accordingly
	uint16_t uActions = 0;

	// get the ItemID from the listbox selection by nefarious means
	uint16_t uListBoxID = player->GetItemIdFromName(std::string((lbPlayerItems->GetStringSelection())));
	uActions = player->pNode.GetActions(uListBoxID);

	std::string ActionString = ListItem.ToStdString();
	size_t len = ActionString.std::string::find_first_of(" ");
	ActionString = ActionString.substr(0, len);

	// special case for drop
	if (ActionString == "Drop")  // add the item to the current loacation
	{
		uint16_t id = 0;
		for (auto index : player->pNode.ItemsInNode)
		{
			if (index.GetID() == uListBoxID)
			{
				index.SetLocation(CurrentMapNode.GetID());
				map->PlaceItemInNode( index, CurrentMapNode.GetID());
								
			}
		}
		
	}
	player->ProcessItemAction(this, uListBoxID, ActionString, uActions);
	bRefresh = true;
	bPlayerRefresh = true;
	evt.Skip();
}

bool cMain::ProcessItemAction(uint16_t id, const std::string& action_string, uint16_t possible_actions)
{  // process the item given by ID with the action mentioned in action_string 
   // if that action is allowed for that item
	
	uint16_t tmpAction = 0;
	if (action_string == "Eat")
		tmpAction = Eatable; //1
	else
	if(action_string == "Drink")
		tmpAction = Drinkable;  //2
	else
	if (action_string == "Take")
		tmpAction = Takeable; //4
	else
	if (action_string == "Drop")
		tmpAction = Droppable;  //8
	else
	if (action_string == "Use")
		tmpAction = Usable;  //16
	else
	if (action_string == "Question")
		tmpAction = Talkable; //32
	else
	if (action_string == "Kill")
		tmpAction = Killable;  //64

	uint16_t theItemID = 0;
	// find the item that has the correct ID
	std::vector<Item>::iterator it;
	uint16_t found = 0;
	for (it = CurrentMapNode.ItemsInNode.begin(); it != CurrentMapNode.ItemsInNode.end(); ++it)
	{
		uint16_t x = CurrentMapNode.ItemsInNode[found].GetID();
		if (x == id)
		{
			break;
		}
		found++;
	}
	void(*function)(void* mainwin);//  this function pointer sends a pointer to cMain back to GameSetup.
	if (tmpAction & possible_actions)
	{//  Now we have the Item ID and the action.  
				
		std::string conv;
		uint16_t weight = 0;
		switch (tmpAction)
		{
		case Eatable:// remove from MapNode and increment health
			function = CurrentMapNode.ItemsInNode[found].f;

			if (function)
				function(this);
			CurrentMapNode.DropItem(CurrentMapNode.ItemsInNode[found]);
			
			map->Replace(CurrentMapNode);
			player->AddHealth(10);
			// need to set health
			break;
		
		case Drinkable:
			function = CurrentMapNode.ItemsInNode[found].f;

			if (function)
				function(this);
			CurrentMapNode.DropItem(CurrentMapNode.ItemsInNode[found]);
			
			map->Replace(CurrentMapNode);
			player->AddHealth(20);
			
			break;

			
		case Takeable:
			// firstly need to check that the item isn't too heavy
			weight = player->pNode.GetCombinedItemWeight();
			weight += CurrentMapNode.ItemsInNode[found].GetWeight();
			if (weight > MAXWEIGHT)  // can't take - too heavy
			{
				wxMessageBox(wxT("You can't pick this up at the moment.  Try leaving something else behind"), wxT("Items too heavy"));
			}
			else
			{
				player->AddItemID(id);
				
				CurrentMapNode.DropItem(CurrentMapNode.ItemsInNode[found]);

				map->Replace(CurrentMapNode);
				bPlayerRefresh = true;
			}
			
			break;
		
		case Usable:
			function = CurrentMapNode.ItemsInNode[found].f;
				
			if (function)
				function(this);
			if (CurrentMapNode.ItemsInNode[found].GetKeep() == false)
			{
				CurrentMapNode.DropItem(CurrentMapNode.ItemsInNode[found]);
				map->Replace(CurrentMapNode);
			}
			
			break;
		case Talkable:
			
			conv = CurrentMapNode.ItemsInNode[found].GetConversation();
			function = CurrentMapNode.ItemsInNode[found].f;
			txtDesc->AppendText(conv);
			bRefresh = false;
			
			WaitForAnyKey();
			
			if (function)
			{
				
				function(this);
				
			}
			
			break;
		case Killable:
			
						
			EnableCloseButton(false);
			fileMenu->Enable(wxID_EXIT, false);
			// while neither player is dead, continue fighting
			while (ReduceEnemyHealth(20)) 
			{
				player->RemoveHealth(10);
				txtDesc->AppendText("\nOuch!");
				wxYield();
				wxMilliSleep(500);
				
			}
			bBossKilled = true;
			txtDesc->AppendText("\n\n\tYou fight valiantly, and eventually you defeat the enemy\n\n");
			bRefresh = false;
			
			WaitForAnyKey();
			function = CurrentMapNode.ItemsInNode[found].f;
			if (function)
			{

				function(this);

			}
			EnableCloseButton(true);
			fileMenu->Enable(wxID_EXIT, true);
			break;
		default: //should never happen
			wxMessageBox("Invalid Item option", "This is embarrassing");
			break;
		}
		
	}
	else 
		return false;
	// update the grid
	bRefresh = true;
	return true;
}

void cMain::ShowPrologue()
{//  Display the prologue info
	txtTitle->Clear();
	txtTitle->SetValue(wxString("Prologue"));
	txtDesc->Clear();
	fileMenu->Enable(wxID_EXIT, false);
	EnableCloseButton(false);
	
	DisableAllNavButtons();
	for (auto i = PrologueData.begin(); i != PrologueData.end(); i++)
	{//  need keypress detection, so that the prologue can be cancelled
		txtDesc->AppendText(*i);
		txtDesc->HideNativeCaret();
		for (int j = 0; j < 10; j++)
		{// to make the menus a bit more responsive during the prologue
			wxYield();
							
			::wxMilliSleep(200);
		}
	}
	
	for (int j = 0; j < 150; j++)
	{// to make the menus a bit more responsive during the prologue
		wxYield();
		
		::wxMilliSleep(20);
	}
	bRefresh = true;
	txtDesc->Clear();
	fileMenu->Enable(wxID_EXIT, true);
	EnableCloseButton(true);
	
}

void cMain::ShowEpilogue()
{
	txtTitle->Clear();
	txtTitle->SetValue(wxString("You won!"));
	txtDesc->Clear();
	fileMenu->Enable(wxID_EXIT, false);
	EnableCloseButton(false);

	// fade out the music
	FadeMusic();
	Music->Stop();
	
	Sfx->Load(EndChimeFilename);
	

	DisableAllNavButtons();
	for (auto i = EpilogueData.begin(); i != EpilogueData.end(); i++)
	{//  need keypress detection, so that the epilogue can be cancelled
		txtDesc->AppendText(*i);
		txtDesc->HideNativeCaret();
		for (int j = 0; j < 10; j++)
		{// to make the menus a bit more responsive during the epilogue
			wxYield();
			

			::wxMilliSleep(200);
		}
	}

	for (int j = 0; j < 150; j++)
	{// to make the menus a bit more responsive during the epilogue
		wxYield();
		if (bRefresh)
		
		::wxMilliSleep(20);
	}
	txtDesc->Clear();
	fileMenu->Enable(wxID_EXIT, true);
	EnableCloseButton(true);
	SetGameRunning(false);
}

void cMain::FadeMusic()
{// fade the music out to zero
	double vol = Music->GetVolume() / 10;
	for (uint8_t i = 0; i < 10; i++)
	{
		Music->SetVolume(Music->GetVolume() - vol);
		wxMilliSleep(250);
	}
}

void cMain::ShowGameOver()
{
	SetGameRunning(false);
	btnPlayer->Enable(false);
	btnGo->Enable(false);
	lbItems->Show(false);
	lbPlayerItems->Show(false);
	txtTitle->Clear();
	txtTitle->SetValue(wxString("The End"));
	txtDesc->Clear();
	fileMenu->Enable(wxID_SAVE, false);
	DisableAllNavButtons();
	

	for (auto i = GameOverData.begin(); i != GameOverData.end(); i++)
	{
		txtDesc->AppendText(*i);
		txtDesc->HideNativeCaret();
		
	}
	
	FadeMusic();
	Music->Stop();

	Sfx->Load(GameLostMusic);
	
}

void cMain::UpdatePlayerListBox()
{// update the player listbox's contents, obviously
	if (bPlayerRefresh == false)
		return;
	if (player->pNode.GetNumItems() == 0)
	{
		lbPlayerItems->Show(false);
		btnPlayer->Enable(false);
		return;
	}
	else
	{
		
		btnPlayer->Enable(true);
		bPlayerRefresh = false;
	}
	lbPlayerItems->Clear();

	uint16_t uID, uAction = 0;
	std::vector<Item>::iterator it;
	std::string sItemName = "";
	std::string sAction = "";
	for (it = player->pNode.ItemsInNode.begin(); it != player->pNode.ItemsInNode.end(); ++it)
	{
		uID = it->GetID();
		uAction = it->GetProperties();
		auto tup = std::make_tuple(uID, uAction);
		player->vPlayerItemInfo.push_back(tup);
		sItemName = it->GetName();
		if (uAction & Eatable)
		{
			sAction = "Eat " + sItemName;
			lbPlayerItems->AppendString(sAction);
		}
		if (uAction & Drinkable)
		{
			sAction = "Drink " + sItemName;
			lbPlayerItems->AppendString(sAction);
		}
		
		if (uAction & Droppable)
		{
			sAction = "Drop " + sItemName;
			lbPlayerItems->AppendString(sAction);
		}
		if (uAction & Usable)
		{
			sAction = "Use " + sItemName;
			lbPlayerItems->AppendString(sAction);
		}
		
		if (uAction & Killable)
		{
			sAction = "Kill " + sItemName;
			lbPlayerItems->AppendString(sAction);
		}
		
	}
	lbPlayerItems->Show(true);
}

void cMain::OnKeyDown(wxKeyEvent& evt)
{

	bRefresh = true;
	evt.Skip();
}

void cMain::CreateMenu()
{
	menuBar = new wxMenuBar();

	fileMenu = new wxMenu();
	// add items in the file menu
	fileMenu->Append(wxID_NEW, _T("New game"));
	fileMenu->Append(wxID_OPEN, _T("Open"));
	fileMenu->AppendSeparator();
	fileMenu->Append(wxID_SAVE, _T("Save"));
	
	fileMenu->AppendSeparator();

	fileMenu->Append(wxID_EXIT, _T("Exit"));

	menuBar->Append(fileMenu, _T("File"));
	
	soundMenu = new wxMenu();
	soundMenu->Append(tmID_SOUNDOPTIONS, _T("Sound Options"));
	soundMenu->AppendSeparator();
	soundMenu->AppendCheckItem(tmID_SOUNDOFF, _T("Silent Mode"));
	menuBar->Append(soundMenu, _T("Sounds"));
	
	helpMenu = new wxMenu();
	helpMenu->Append(wxID_HELP, _T("About ..."));
	menuBar->Append(helpMenu, _T("Help"));
	SetMenuBar(menuBar);
}

void cMain::SetMusicVol(double dVal)
{
	Music->SetVolume(dVal);
}

void cMain::SetSfxVol(double dVal)
{
	Sfx->SetVolume(dVal);
	if(gSoundOptions)
		PlaySFX("ting.wav");
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
	
	m_bGameRunning = isRunning;
}
