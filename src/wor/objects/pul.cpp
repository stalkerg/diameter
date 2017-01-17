#include "./pul.h"
#include <stdlib.h>



int PulObject::Draw()
{
vec3 t;
vec2 t2;
t.x = PF.cord.x;
t.y = PF.cord.y;
t.z = 0;
if (InModel != NULL)
	InModel->Draw (t, PF.rotation, 0);
if (InSprite != NULL)
	{
	/* Enable Blending */
	glEnable (GL_BLEND);
	/* Type Of Blending To Perform */
	glBlendFunc (GL_SRC_ALPHA, GL_ONE);
	/* Really Nice Perspective Calculations */
	glHint (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	/* Really Nice Point Smoothing */
	glHint (GL_POINT_SMOOTH_HINT, GL_NICEST);
	glDepthMask (GL_FALSE);
	glEnable(GL_COLOR_MATERIAL);
	glColor4f(1.0,1.0,1.0,1.0-Life/3.0);
	InSprite->Draw (t, PF.rotation, 1);
	glDisable(GL_COLOR_MATERIAL);
	glDisable (GL_BLEND);
	glDepthMask (GL_TRUE);
	}
if (InParticle != NULL)
	{
	InParticle->nDirection.x = PF.direction.x;
	InParticle->nDirection.y = PF.direction.y;
	InParticle->nDirection.z = 0;
	InParticle->nDirection.normalize ();
	InParticle->cor.x = InParticle->nDirection.x * ParticlePos.x;
	InParticle->cor.y = InParticle->nDirection.y * ParticlePos.y;
	InParticle->nSpeed = PF.now_power * PF.now_power * 6;
	glPushMatrix ();
	glTranslatef (t.x, t.y, 0);
	InParticle->Draw ();
	glPopMatrix ();
	}
return 0;
}

int PulObject::Calc()
{
Life+=(*PF.reltime);
if(GetStepKill()==false)
	{
	if(ParentObject!=NULL&&ParentObject->GetStepKill())
		ParentObject=NULL;
	if(Life>3)
		StepKill(true);
	PF.Calc();
	int xs,ys;
	int s = GetSublimatObjects ()->GetSectorN (PF.cord,&xs,&ys);

	if (s != GetnSector ())
		{
		ObjectList::iterator it1;
		for (it1 = GetSublimatObjects ()->GetSeO ()[GetnSector ()].begin ();
		     it1 != GetSublimatObjects ()->GetSeO ()[GetnSector ()].end ();
		     ++it1)
			{
			if (it1->in == this)
				{
				GetSublimatObjects ()->GetSeO ()[s].push_front (*it1);
				GetSublimatObjects ()->GetSeO ()[GetnSector ()].erase (it1);
				WritenSector (s);
				return 0;
				}
			}
		}
	}
else
	{
	IntStepKill++;
	if(IntStepKill>=2)
		{
		if(Life<3)
			BeginExplosion();
		Kill();
		return 1;
		}
	}
return 0;
}

void PulObject::BeginExplosion()
{
Explosion *ExplosionTemp;
switch(TypePul)
	{
	case 1:ExplosionTemp = new Explosion(5);break;
	case 2:ExplosionTemp = new Explosion(15);break;
	default: return;
	}

ExplosionTemp->inSprite=ExplosionSprite;
ExplosionTemp->cor.x=0;
ExplosionTemp->cor.y=0;
ExplosionTemp->cor.z=-10;
if(TypePul==1)
	{
	ExplosionTemp->nColor[0]=1.0;
	ExplosionTemp->nColor[1]=0.8;
	ExplosionTemp->nColor[2]=0.3;
	ExplosionTemp->nColor[3]=1;
	ExplosionTemp->kColor[0]=1;
	ExplosionTemp->kColor[1]=0.5;
	ExplosionTemp->kColor[2]=1;
	ExplosionTemp->kColor[3]=0;
	}
if(TypePul==2)
	{
	ExplosionTemp->nColor[0]=1.0;
	ExplosionTemp->nColor[1]=0.5;
	ExplosionTemp->nColor[2]=1.0;
	ExplosionTemp->nColor[3]=1;
	ExplosionTemp->kColor[0]=1;
	ExplosionTemp->kColor[1]=0.5;
	ExplosionTemp->kColor[2]=1;
	ExplosionTemp->kColor[3]=0;
	}
ExplosionTemp->nSpeed=2;
ExplosionTemp->fSpeed_s=1;
ExplosionTemp->main_dir.x=dir_splash.x;
ExplosionTemp->main_dir.y=dir_splash.y;
ExplosionTemp->k_deflection=0.5;
ExplosionTemp->life=1;
ExplosionTemp->t=PF.reltime;
ExplosionTemp->tnow=PF.tnow;
ExplosionTemp->Init();
TimObject *TempTim=new TimObject(1);
TempTim->WriteName("TemporarilyObject");
TempTim->WriteType(O_Tim);
TempTim->WriteParent(this);
TempTim->GetPFS()->cord=PF.cord;
TempTim->GetPFS()->speed=speed_object;
TempTim->GetPFS()->reltime=PF.reltime;
TempTim->WriteParticle(ExplosionTemp);
AddObjectToSO(TempTim);
}

void PulObject::Dem(AI *in)
{
dir_splash=GetCord()-in->GetCord();
speed_object=in->GetPFS()->speed;
dir_splash.normalize();
StepKill(true);
}

vec2 PulObject::GetCord()
{
return PF.cord;
}

vec2 *PulObject::GetUCord()
{
return &PF.cord;
}

PulObject::PulObject(vec2 in, float rot, int TypeGun)
{
InModel = NULL;
InSprite = NULL;
InParticle = NULL;
PF.speed=in;
Life=0;
IntStepKill=0;
StepKill(false);
PF.rotation=rot;
PF.to_rotation=rot;
if(TypeGun==1)
	{
	vec2 nullvec;
	ColOSphere *TempSP1 = new ColOSphere(GetRadius(),nullvec);
	PF.Colision->AddObject(TempSP1);
	TypePul=TypeGun;
	}
if(TypeGun==2)
	{
	vec2 start,end;
	start[0]=(-GetRadius());
	end[0]=GetRadius();
	ColOLine *TempSP1 = new ColOLine(start,end);
	PF.Colision->AddObject(TempSP1);
	TypePul=TypeGun;
	}
}


