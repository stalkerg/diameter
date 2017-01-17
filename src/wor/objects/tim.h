#ifndef OBJECT_AI_TIM
#define OBJECT_AI_TIM

#include "../AI.h"
#include "../fiz.h"
#include "../../gra/model.h"
#include "../../gra/sprite.h"
#include "../../gra/effect/particle.h"

class TimObject: public AI
{
Model *InModel;
Sprite *InSprite;
Particle *InParticle;
PlayFizState PF;
vec2 ParticlePos, ToCor;
float Life, Timer;
AI *ParentObject;
public:
~TimObject()
	{
	if(InParticle!=NULL)
		delete InParticle;
	}
TimObject (float time);
void WriteParent(AI *AIin){ParentObject=AIin;}
AI *GetParent(){return ParentObject;}
void WriteModel(Model *in)
	{
	InModel=in;
	}
void WriteSprite(Sprite *in){InSprite=in;}
void WriteParticlePos(vec2 in){ParticlePos=in;}
void WriteParticle(Particle *in){InParticle=in;}
//Virtual

virtual PlayFizState *GetPFS(){return &PF;}
virtual int Draw();
virtual vec2 GetCord();
virtual vec2 *GetUCord();
virtual int Calc();
};

#endif
