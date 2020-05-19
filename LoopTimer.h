#ifndef LOOPTIMER_H
#define LOOPTIMER_H

#include "wx/timer.h"
class LoopTimer : public wxTimer
{
public:
	void Notify();
	void start();
};

#endif  //  LOOPTIMER_H

