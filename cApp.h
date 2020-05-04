#pragma once
#include "wx/wx.h"
#include "cMain.h"
#define NOSPLASH
class cApp : public wxApp
{
public:
	cApp();
	~cApp();
	virtual bool OnInit();
private:
	cMain* m_frame1 = nullptr;
};

