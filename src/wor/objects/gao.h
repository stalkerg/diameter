#ifndef OBJECT_AI_GAO
#define OBJECT_AI_GAO

#ifdef _POSIX_C_SOURCE	// shut up pyconfig.h complaints
#undef _POSIX_C_SOURCE
#endif
#include <Python.h>

#include <GL/glu.h>
#include "./pul.h"
#include "./roc.h"
#include "./tim.h"

#include "../AI.h"
#include "../fiz.h"
#include "../../gra/model.h"
#include "../../gra/sprite.h"
#include "../../gra/effect/particle.h"
#include "../../gra/effect/explosion.h"
#include "../../snd/snd.h"

struct WeaponSM
{
WeaponSM()
	{
	PulsGun=NULL;
	Liser=NULL;
	Rocket1=NULL;
	gmlist=NULL;
	gslist=NULL;
	}
Sprite *PulsGun, *PulsGunEx;
Sprite *Liser, *LiserEx;
Model *Rocket1;
ModelList *gmlist;
SpriteList *gslist;
};

class GaoObject: public AI
{
Model *InModel;
Sprite *InSprite;
Particle *InParticle;
GLUquadric *DRadius;
PlayFizState PF;
vec2 ParticlePos,ParticlePos2;
WeaponSM GaoWeaponSM;
float Radius,ShootTimer,ShieldTimer,GunEnergyTimer;
int IntStepKill;
//reg
AI *O1,*O2,*O3;
//AI *LastAttackObject;
public:
~GaoObject()
	{
	if(InParticle!=NULL)
		delete InParticle;
	}
GaoObject();

Sprite *ExplosionSmall;
Sprite *ExplosionBig;

//void WriteLastAttackObject(AI *in){LastAttackObject=in;}
//AI * GetLastAttackObject(){return LastAttackObject;}
void BeginExplosion();
void WriteModel(Model *in);
void WriteSprite(Sprite *in){InSprite=in;}
void WriteParticlePos(vec2 in){ParticlePos=in;}
void WriteParticlePos2(vec2 in){ParticlePos2=in;}
void WriteParticle(Particle *in){InParticle=in;}
void WriteWeaponSM(WeaponSM in){GaoWeaponSM=in;}
//virtual
virtual void Dem(AI *in);
virtual float GetRadius(){return Radius;}
virtual PlayFizState *GetPFS(){return &PF;}
virtual int Draw();
virtual vec2 GetCord();
virtual vec2 *GetUCord();
virtual int Calc();
//Virtual AI
virtual bool RotTo(vec2 vin);
virtual bool SRotTo();
virtual bool Shoot();
virtual bool MoveTo(vec2 vin);
virtual bool MoveToAndStop(vec2 vin);
virtual bool FollowObject(AI *ain);
virtual bool AttackObject(AI *ain);
//virtual void KillDown(){if(InParticle!=NULL){delete InParticle;}cout<<"Helll"<<endl;}
//AI
bool MoveFollowObject();
bool Move();
bool SAttackObject();
};
//void AddShipToList(ShipObject * ship);
//ShipObject * GetShipByName(string ship_name);

namespace PyGaoObject
{
void InitGaoObject(SpriteList *gslist, ModelList *gmlist,
		   float *time_n, float *time_e, WeaponSM weapon, vec2 **CamCor_in);
}

#endif


