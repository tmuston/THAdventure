#ifndef CMAIN_H
#define CMAIN_H
///////////////////////////////////////////////////////////////////////////////
//								  cMain.h                                    //
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
//    This file declares a wxFrame object, which controls the flow of the.   //
//    Application.  This is the equivalent of int main().                    //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#include <tuple>
#include "wx/wx.h"
#include "wx/mediactrl.h"
#include "wx/sound.h"
#include "wx/config.h"
#include "wx/fileconf.h"
#include "wx/font.h"
#include "wx/arrstr.h"
#include "wx/timer.h"
#include "wx/listbox.h"
#include "wx/utils.h"


#include "Map.h"
#include "SoundOptions.h"
#include "GameSetup.h"
#include "BuildOptions.h"
#include "Player.h"
#include "StartDialog.h"
#include "GameState.h"



// definitions for the window events
enum
{
	tmID_SOUNDOPTIONS = 1,
	tmID_SOUNDOFF,
	tmID_MUSICLOADED,
	tmID_SFXLOADED,
	tmID_MUSICFINISHED,
	tmID_TITLE,
	tmID_DESCRIPTION,
	tmID_NORTH,
	tmID_EAST,
	tmID_SOUTH,
	tmID_WEST,
	tmID_UP,
	tmID_DOWN,
	tmID_LISTBOX,
	tmID_GOBUTTON,
	tmID_LOOPTIMER,
	tmID_PLAYERNAME,
	tmID_PLAYERHEALTH,
	tmID_PLAYERBUTTON,
	tmID_PLAYERLISTBOX,
	tmID_KEYPRESS
};

class cMain : public wxFrame
{
public:
	cMain();
	~cMain();

	// event functions
	void OnExit(wxCommandEvent& evt);
	void OnNew(wxCommandEvent& evt);
	void OnSave(wxCommandEvent& evt);

	void CreateMenu();
	void SetMusicVol(double dVal);
	void SetSfxVol(double dVal);
	void ClearTitle();
	void ClearDesc();
	void SetTitle( std::string title);
	void AddToDesc( std::string words);
	void SetGameRunning(bool isRunning); 
	inline bool GetGameRunning() { return m_bGameRunning; }
	bool MainLoop();
	void DisableAllNavButtons();
	void EnableSelectedNavButtons(uint16_t buttons);
	void WriteExitInfo(uint16_t info);
	bool WriteItemInfo();
	void ProcessItems();
	void NewOrOpen();
	inline void SetRefresh(bool refresh) { bRefresh = refresh; }
	inline Player* GetPlayer() { return player; }
	void FlashPanel();
	void FlashPanelBlack();
	void PlaySFX(std::string fName);
	void WaitForAnyKey();
	
private:
	void OnSoundOptions(wxCommandEvent& evt);
	void OnSoundOnOff(wxCommandEvent& evt);
	void OnWAVLoaded(wxMediaEvent& evt);
	void OnSFXLoaded(wxMediaEvent& evt);
	void OnWAVFinished(wxMediaEvent& evt);
	void OnIdle(wxIdleEvent& evt);
	void OnGameLoop(wxTimerEvent& evt);
	bool bRefresh = false;
	bool bPlayerRefresh = false;
	// Nav button event handles
	void OnNorth(wxCommandEvent& evt);
	void OnEast(wxCommandEvent& evt);
	void OnSouth(wxCommandEvent& evt);
	void OnWest(wxCommandEvent& evt);
	void OnUp(wxCommandEvent& evt);
	void OnDown(wxCommandEvent& evt);

	void OnDoIt(wxCommandEvent& evt);
	void OnPlayerButton(wxCommandEvent& evt);
	bool ProcessItemAction(uint16_t id, const std::string& action_string, uint16_t possible_actions);
	void ShowPrologue();
	void UpdatePlayerListBox();
	void OnKeyDown(wxKeyEvent& evt);
	bool m_bGameRunning;
	Map* map = nullptr;
	MapNode CurrentMapNode;

	std::string FileName = "";
	wxPanel* panel = nullptr;
	wxMenuBar* menuBar = nullptr;
	wxMenu* fileMenu = nullptr;
	wxMenu* soundMenu = nullptr;
	SoundOptions* soundWindow = nullptr;
	wxMediaCtrl* Music = nullptr;
	wxMediaCtrl* Sfx = nullptr;
	wxFileConfig* IniConfig = nullptr; // the Ini file
	wxTextCtrl* txtTitle = nullptr;
	wxTextCtrl* txtDesc = nullptr;
	wxFont* fntTitle = nullptr;
	wxFont* fntDesc = nullptr;
	wxButton* btnN = nullptr;
	wxButton* btnE = nullptr;
	wxButton* btnS = nullptr;
	wxButton* btnW = nullptr;
	wxButton* btnU = nullptr;
	wxButton* btnD = nullptr;
	wxListBox* lbItems = nullptr;
	wxButton* btnGo = nullptr;
	wxStaticBox* box = nullptr;
	wxStaticText* lblPlayerName = nullptr;
	wxStaticText* lblPlayerHealth = nullptr;
	wxListBox* lbPlayerItems = nullptr;
	wxButton* btnPlayer = nullptr;

	bool bComplete = false;
	bool PrologueDone = false;
	bool bGameSaved = false;
	Player* player = nullptr;
	wxTimer* loopTimer = nullptr;
	StartDialog* StartWindow = nullptr;
	GameState* game = nullptr;
	uint16_t CurrentRoom = 1;
	std::vector<std::tuple<uint16_t, uint16_t>> vItemInfo; //stores Item ID and Item Action, used by OnDoIt
	// data for the prologue and epilogue
	std::vector<std::string> PrologueData;
	std::vector<std::string> EpilogueData;
	wxDECLARE_EVENT_TABLE();
};
#endif // CMAIN_H
