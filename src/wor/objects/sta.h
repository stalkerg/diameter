#ifndef OBJECT_AI_STA
#define OBJECT_AI_STA

#include "../AI.h"
#include "../fiz.h"
#include "../../gra/model.h"
#include "../../gra/sprite.h"
#include "../../gra/effect/particle.h"

class StaObject: public AI
{
Model *InModel;
Sprite *InSprite;
Particle *InParticle;
PlayFizState PF;
vec2 ParticlePos, ToCor;
AI *ParentObject;
public:
~StaObject()
	{
	if(InParticle!=NULL)
		delete InParticle;
	}
StaObject ();
bool blend, lighting, depthmsk;

void WriteParent(AI *AIin){ParentObject=AIin;}
AI *GetParent(){return ParentObject;}
void WriteModel(Model *in)
	{
	InModel=in;
	}
void WriteSprite(Sprite *in){InSprite=in;}
void WriteParticlePos(vec2 in){ParticlePos=in;}
void WriteParticle(Particle *in){InParticle=in;}

virtual PlayFizState *GetPFS(){return &PF;}
virtual int Draw();
virtual vec2 GetCord();
virtual vec2 *GetUCord();
virtual int Calc();
};

#endif
