#ifndef OBJECT_AI_PUL
#define OBJECT_AI_PUL

#include "../AI.h"
#include "./tim.h"

#include "../fiz.h"
#include "../../gra/model.h"
#include "../../gra/sprite.h"
#include "../../gra/effect/particle.h"
#include "../../gra/effect/explosion.h"

class PulObject: public AI
{
Model *InModel;
Sprite *InSprite;
Particle *InParticle;
PlayFizState PF;
vec2 ParticlePos, dir_splash, speed_object;
float Radius;
float Life;
int TypePul, IntStepKill;
AI *ParentObject;
public:
~PulObject()
	{
	if(InParticle!=NULL)
		delete InParticle;
	}
PulObject (vec2 in,float rot,int TypeGun);

Sprite *ExplosionSprite;

void WriteParent(AI *AIin){ParentObject=AIin;}
AI *GetParent(){return ParentObject;}
void WriteModel(Model *in){InModel=in;Radius=InModel->Radius;}
void WriteSprite(Sprite *in){InSprite=in;}
void WriteParticlePos(vec2 in){ParticlePos=in;}
void WriteParticle(Particle *in){InParticle=in;}
int GetTypePul(){return TypePul;}
void BeginExplosion();
//virtual
virtual float GetRadius()
	{
	if(InModel==NULL)
		return 0.3;
	else
		return Radius;
	}
//virtual float GetRadius(){return Radius;}
virtual void Dem(AI *in);
virtual PlayFizState *GetPFS(){return &PF;}
virtual int Draw();
virtual vec2 GetCord();
virtual vec2 *GetUCord();
virtual int Calc();
//Virtual AI

//AI

};

#endif


