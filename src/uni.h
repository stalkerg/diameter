#ifndef UNI
#define UNI
#include <iostream>

struct Options
	{
	unsigned int winH, winW, bit, snd_buffer,
	tm_live_texture, tm_loop_pause, tm_iteration_pause,
	mm_live_model, mm_loop_pause, mm_iteration_pause;
	bool fs, sound, input;
	std::string language, path_to_data, path_to_conffile;
	};


//#define DEBUG
//#define CVS


#ifdef __WORDSIZE
#else
#if (defined __LP64__)
#define __WORDSIZE 64
#else
#define __WORDSIZE 32
#endif
#endif

#endif
