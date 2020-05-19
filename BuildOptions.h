#ifndef BUILDOPTS_H
#define BUILDOPTS_H

//#define TIM_TESTING  //  Comment this line out for production
#ifdef TIM_TESTING
	#define NOSPLASH
	#define NOPROLOGUE
	#define NOEPILOGUE
#endif
#endif
