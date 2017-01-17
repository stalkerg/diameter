#include "./snd.h"

Mix_Chunk *Shot, *Exp_0, *Exp_1;
bool Init=false;

void CloseSound(Mix_Music *music)
{
Mix_FreeMusic(music);
Mix_CloseAudio();
std::cout<<"Music Close."<<std::endl;
}

void InitSound(int buffer)
{
// start SDL with audio support
if (SDL_Init (SDL_INIT_AUDIO) == -1)
	{
	std::cout<<"SDL_Init: "<<SDL_GetError()<<std::endl;
	exit (1);
	}
// open 44.1KHz, signed 16bit, system byte order,
//      stereo audio, using 1024 byte chunks
if (Mix_OpenAudio (44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
	{
	std::cout<<"Mix_OpenAudio: "<<Mix_GetError()<<std::endl;
	exit (2);
	}
std::string temp_string = "music/sample/s1.wav";
temp_string = PKGDATADIR+temp_string;
Shot=Mix_LoadWAV (temp_string.c_str());

temp_string = "music/sample/explode_06.wav";
temp_string = PKGDATADIR+temp_string;
Exp_0=Mix_LoadWAV (temp_string.c_str());

temp_string = "music/sample/explode_07.wav";
temp_string = PKGDATADIR+temp_string;
Exp_1=Mix_LoadWAV (temp_string.c_str());
Init=true;
std::cout << "InitSound-OK" << std::endl;
}

void SoundExp()
{
if(Init)
	PlaySound ( Exp_1);
}

void SoundVolumeExp(int in)
{
if(Init)
	Mix_VolumeChunk(Exp_0, in);
}

void SoundShot()
{
if(Init)
	PlaySound ( Shot);
}

void SoundVolumeShot(int in)
{
if(Init)
	Mix_VolumeChunk(Shot, in);
}

void PlaySound( Mix_Chunk *sample)
{
if(Init)
	{
	if (!sample)
		{
		std::cout<<"Mix_LoadWAV: "<<Mix_GetError()<<std::endl;
		// handle error
		}

// play sample on first free unreserved channel
// play it exactly once through
	if (Mix_PlayChannel(-1, sample, 0) == 0)
		{
		std::cout<<"Mix_PlayChannel: "<<Mix_GetError()<<std::endl;
		// may be critical error, or maybe just no channels were free.
		// you could allocated another channel in that case...
		}
	}
}

void PlayMusic(char *file, int chanel)
{
if(Init)
	{
	// load the music file to play as music
	Mix_Music *music;
	music = Mix_LoadMUS (file);
	if (!music)
		{
		std::cout<<"Mix_LoadMUS(\"*.*\"): "<<Mix_GetError()<<std::endl;
		// this might be a critical error...
		}

	if (Mix_PlayMusic(music, chanel) == chanel)
		{
		std::cout<<"Mix_PlayMusic: "<<Mix_GetError()<<std::endl;
		// well, there's no music, but most games don't break without music...
		}
	}
	Mix_VolumeMusic(MIX_MAX_VOLUME-50);
}

void PlayMusic(Mix_Music *music, int loops)
{
if(Init)
	{
	// load the music file to play as music
	if (!music)
		{
		std::cout<<"Mix_LoadMUS(\"*.*\"): "<<Mix_GetError()<<std::endl;
		// this might be a critical error...
		}

	if (Mix_PlayMusic(music, loops) == loops)
		{
		std::cout<<"Mix_PlayMusic: "<<Mix_GetError()<<std::endl;
		// well, there's no music, but most games don't break without music...
		}
	}
}


