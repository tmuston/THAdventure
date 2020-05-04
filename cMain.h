#pragma once
#include "wx/wx.h"
#include "Map.h"

// definitions for the window events

#define tmID_CONTINUE 200



class cMain : public wxFrame
{
public:
	cMain();
	~cMain();

	// event functions
	void OnContinue(wxCommandEvent& evt);
private:
	Map* map = nullptr;
	MapNode* CurrentMapNode = nullptr;
	wxButton* btnContinue = nullptr;
	std::string FileName = "";
	wxPanel* panel = nullptr;
	wxMenuBar* menuBar = nullptr;
	wxMenu* fileMenu = nullptr;
	void CreateMenu();
	
	wxDECLARE_EVENT_TABLE();

};

