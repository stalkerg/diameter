#ifndef SND
#define SND
#include <SDL/SDL.h>
#include <SDL/SDL_audio.h>
#include <SDL/SDL_mixer.h>
#include <iostream>
#include <string>


void InitSound (int buffer);

void CloseSound(Mix_Music *music);

void SoundShot();

void SoundVolumeShot(int in);

void SoundExp();

void SoundVolumeExp(int in);

void PlaySound ( Mix_Chunk *sample);


void PlayMusic (char *file, int chanel);

void PlayMusic (Mix_Music *music, int loops);


#endif

