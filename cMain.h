#ifndef MAIN_H
#define MAIN_H
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

#include "wx/wx.h"
#include "Map.h"
#include "SoundOptions.h"
#include "wx/mediactrl.h"
#include "wx/sound.h"
#include "wx/config.h"
#include "wx/fileconf.h"
#include "wx/font.h"


// definitions for the window events
enum
{
	tmID_SOUNDOPTIONS = 1,
	tmID_SOUNDOFF,
	tmID_MUSICLOADED,
	tmID_MUSICFINISHED,
	tmID_TITLE,
	tmID_DESCRIPTION
};

class cMain : public wxFrame
{
public:
	cMain();
	~cMain();

	// event functions
	void OnExit(wxCommandEvent& evt);

	void CreateMenu();
	void SetMusicVol(double dVal);
private:
	void OnSoundOptions(wxCommandEvent& evt);
	void OnSoundOnOff(wxCommandEvent& evt);
	void OnWAVLoaded(wxMediaEvent& evt);
	void OnWAVFinished(wxMediaEvent& evt);
	void OnIdle(wxIdleEvent& evt);
	Map* map = nullptr;
	MapNode* CurrentMapNode = nullptr;

	std::string FileName = "";
	wxPanel* panel = nullptr;
	wxMenuBar* menuBar = nullptr;
	wxMenu* fileMenu = nullptr;
	wxMenu* soundMenu = nullptr;
	SoundOptions* soundWindow = nullptr;
	wxMediaCtrl* Music = nullptr;
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

	bool GameLoop();
	bool bComplete = false;
	wxDECLARE_EVENT_TABLE();
};
#endif // MAIN_H
