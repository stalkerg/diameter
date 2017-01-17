#include "./sta.h"
#include <stdlib.h>



int StaObject::Draw ()
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
	InParticle->nSpeed = 4;	
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
	glColor4f(1.0,1.0,1.0,1.0);
	InSprite->Draw (t, PF.rotation, 1);
	glDisable(GL_COLOR_MATERIAL);
	glDisable (GL_BLEND);
	glDepthMask (GL_TRUE);
	}
return 0;
}

int StaObject::Calc ()
{
if(InParticle!=NULL) 
	InParticle->Calc();
return 0;
}



vec2 StaObject::GetCord ()
{
return PF.cord;
}

vec2 *StaObject::GetUCord ()
{
return &PF.cord;
}

StaObject::StaObject ()
{
InModel = NULL;
InSprite = NULL;
InParticle = NULL;
}
