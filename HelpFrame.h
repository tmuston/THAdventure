#ifndef HELPFRAME_H
#define HELPFRAME_H
#include "wx/wx.h"
#include "wx/window.h"
#include "wx/richtext/richtextctrl.h"

#define tmHELPOK 203


class HelpFrame : public wxFrame
{
public:
	HelpFrame();
	~HelpFrame();

	void OnHelpOk(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();
};
#endif // HELPFRAME_H

