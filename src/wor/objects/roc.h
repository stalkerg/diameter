#ifndef OBJECT_AI_ROC
#define OBJECT_AI_ROC

#include "../AI.h"
#include "../fiz.h"
#include "../../gra/model.h"
#include "../../gra/sprite.h"
#include "../../gra/effect/particle.h"

class RocObject: public AI
{
Model *InModel;
Sprite *InSprite;
Particle *InParticle;
PlayFizState PF;
vec2 ParticlePos, ToCor;
float Radius, Life, Timer;
bool Start;
AI *ParentObject;
public:
~RocObject()
	{
	if(InParticle!=NULL)
		delete InParticle;
	}
RocObject (vec2 in, float rot, vec2 To);
void WriteParent(AI *AIin){ParentObject=AIin;}
AI *GetParent(){return ParentObject;}
void WriteModel(Model *in)
	{
	InModel=in;
	Radius=InModel->Radius;
	}
void WriteSprite(Sprite *in){InSprite=in;}
void WriteParticlePos(vec2 in){ParticlePos=in;}
void WriteParticle(Particle *in){InParticle=in;}
//virtual
virtual void Dem(AI *in);
virtual float GetRadius()
	{
	if(InModel==NULL)
		return 0.3;
	else
		return Radius;
	}
//virtual float GetRadius(){return Radius;}
virtual PlayFizState *GetPFS(){return &PF;}
virtual int Draw();
virtual vec2 GetCord();
virtual vec2 *GetUCord();
virtual bool RotTo(vec2 vin);
virtual int Calc();
//Virtual AI

//AI

};

#endif


