#ifndef MAIN_H
#define MAIN_H

#include "wx/wx.h"
#include "Map.h"
#include "SoundOptions.h"
#include "wx/mediactrl.h"
#include "wx/sound.h"
#include "wx/config.h"
#include "wx/fileconf.h"


// definitions for the window events
enum
{
	tmID_CONTINUE = 1,
	tmID_SOUNDOPTIONS,
	tmID_SOUNDOFF,
	tmID_MUSICLOADED,
	tmID_MUSICFINISHED

};


class cMain : public wxFrame
{
public:
	cMain();
	~cMain();

	// event functions
	void OnContinue(wxCommandEvent& evt);
	void OnExit(wxCommandEvent& evt);
	void OnSoundOptions(wxCommandEvent& evt);
	void OnSoundOnOff(wxCommandEvent& evt);
	void OnWAVLoaded(wxMediaEvent& evt);
	void OnWAVFinished(wxMediaEvent& evt);
	void OnIdle(wxIdleEvent& evt);
	void CreateMenu();
	void SetMusicVol(double dVal);
private:
	Map* map = nullptr;
	MapNode* CurrentMapNode = nullptr;
	wxButton* btnContinue = nullptr;
	std::string FileName = "";
	wxPanel* panel = nullptr;
	wxMenuBar* menuBar = nullptr;
	wxMenu* fileMenu = nullptr;
	wxMenu* soundMenu = nullptr;
	SoundOptions* soundWindow = nullptr;
	wxMediaCtrl* Music = nullptr;
	wxFileConfig* IniConfig = nullptr;
	bool GameLoop();
	bool bComplete = false;
	wxDECLARE_EVENT_TABLE();

};
#endif // MAIN_H

