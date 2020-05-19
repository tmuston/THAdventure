#include "LoopTimer.h"

void LoopTimer::Notify()
{// do some witchcraft
}

void LoopTimer::start()
{//Start the timer
	wxTimer::Start(30);  // 30 milliseconds
}
