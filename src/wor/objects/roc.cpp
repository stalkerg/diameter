#include "./roc.h"
#include <stdlib.h>



int RocObject::Draw()
{
vec3 t;
vec2 t2;
t.x = PF.cord.x;
t.y = PF.cord.y;
t.z = 0;
if (InParticle != NULL)
	{
	InParticle->nDirection.x = PF.direction.x;
	InParticle->nDirection.y = PF.direction.y;
	InParticle->nDirection.z = 0;
	InParticle->nDirection.normalize ();
	InParticle->cor.x = InParticle->nDirection.x * ParticlePos.x;
	InParticle->cor.y = InParticle->nDirection.y * ParticlePos.y;
	InParticle->nSpeed = PF.now_power*4;	
	glPushMatrix ();
	glTranslatef (t.x, t.y, 0);
	InParticle->Draw ();
	glPopMatrix ();
	}
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
return 0;
}

int RocObject::Calc()
{
Life+=(*PF.reltime);	
if(Life>5)
	{
	Kill();
	return 1;
	}

PF.Calc();
Timer+=(*PF.reltime);
if(Timer>0.5&&Start)
	{
	RotTo(ToCor);
	PF.now_power=1.0;
	//Start=false;
	}

if(InParticle!=NULL) 
	InParticle->Calc();
int xs,ys; 
int s = GetSublimatObjects ()->GetSectorN (PF.cord,&xs,&ys);

//cout<<"xs:"<<xs<<"  xy:"<<ys<<endl;
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
return 0;
}

bool RocObject::RotTo(vec2 vin)
{
float rot;
vin.x = vin.x - PF.cord.x;
vin.y = vin.y - PF.cord.y;
vin.y *= -1;
vin.normalize ();
rot = acos (vin.x) * 180 / PI;
if (vin.y > 0)
	rot *= -1;
rot += 180;
if (fabs (PF.rotation - rot) < 1)
	return true;
if (PF.to_rotation == rot)
	return false;
else
	GetPFS()->to_rotation = rot;
return false;
}

vec2 RocObject::GetCord()
{
return PF.cord;
}

vec2 *RocObject::GetUCord()
{
return &PF.cord;
}

void RocObject::Dem(AI *in)
{
GetParamsHS()->Shield-=in->GetADem();
if(GetParamsHS()->Shield<0) 
	{
	GetParamsHS()->Health+=GetParamsHS()->Shield;
	GetParamsHS()->Shield=0;
	}
}

RocObject::RocObject (vec2 in, float rot, vec2 To)
{
InModel = NULL;
InSprite = NULL;
InParticle = NULL;
Timer=0;
Start=true;
ToCor=To;
PF.speed=in.perpend_left();
Life=0;
PF.rotation=rot;
PF.to_rotation=rot;
vec2 start,end;
start[0]=(-GetRadius());
end[0]=GetRadius();
ColOLine *TempSP1 = new ColOLine(start,end);
PF.Colision->AddObject(TempSP1);
}


