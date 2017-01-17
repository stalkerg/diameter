#ifndef EF_PARTICLE
#define EF_PARTICLE

#include "../sprite.h"
#include <stdlib.h>
#include <SDL.h>

#ifdef _POSIX_C_SOURCE	// shut up pyconfig.h complaints
#undef _POSIX_C_SOURCE
#endif
#include <Python.h>

struct Part
{
vec3 cor,nap;
vec4 color;
float t,speed;
bool life;
};

class Particle
{
protected:
Part *nPart;
int n;
void Initn(int in, bool lf);
public:
float nRas, nSpeed, nFade, life, *t, t2, *tnow;
int fSpeed_x, fSpeed_y, fSpeed_s;
bool up;
vec3 nDirection, cor;
color4 nColor, kColor, cFade;
Sprite *inSprite;
Particle(int in)
	{
	n=in;
	nPart=new Part[n];
	t2=0;
	up=false;
	tnow=NULL;
	};
virtual ~Particle(){delete nPart;}
//Part *GetPart(int i){return nPart[i];}
virtual void Init();
virtual void Calc();
void Draw();
};

namespace PyParticle
{
void InitPythonParticle(SpriteList *gslist, float *time_n, float *time_e);
}

#endif

