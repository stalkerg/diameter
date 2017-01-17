#ifndef SPRITE
#define SPRITE

#include "../res/texture.h"
#include "./mathlib.h"
#include "../res/texture.h"
#include "../uni.h"
#include "../res/xml/tinyxml.h"
#include <iostream>
#include <list>

class Sprite
{
string name;
public:
Texture *intexture;
float insca,sx1,sx2,sy1,sy2;
Sprite()
	{
	insca=1;
	sx1=0;
	sx2=0;
	sy2=0;
	sy1=0;
	}
string GetName(){return name;}
void WriteName(string in) {name=in;}
void Draw(vec3 in, float rot);
void Draw(vec3 in){Draw(in,0);}
void Draw(vec2 in)
	{
	vec3 in2;
	in2.x=in.x;
	in2.y=in.y;
	Draw(in2, 0);
	}
void Draw(vec2 in, float rot)
	{
	vec3 in2;
	in2.x=in.x;
	in2.y=in.y;
	Draw(in2, rot);
	}
void Draw(vec3 in, float rot, float sca);
void Draw(float rot, float sca)
	{
	vec3 temp;
	temp.x=0;
	temp.y=0;
	temp.z=0;
	Draw(temp, rot, sca);
	}
void Draw()
	{
	vec3 temp;
	temp.x=0;temp.y=0;temp.z=0;
	Draw(temp,0,1);
	}
};

typedef list <Sprite> SpriteList;

void SpriteInit(string file,SpriteList *inlist,TextureList *inlist2);


Sprite *GetSFName(string name,SpriteList *inlist);


#endif
