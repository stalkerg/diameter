#include "./cloud.h"
#include <stdlib.h>

void Ef_Clouds::Init()
{
Ef_Cl temp;
int it;
for (it=0; it<n; it++)
	{
	temp.cor.x=(rand()%(int)(splo.x*10))/10.0-splo.x/2.0;
	temp.cor.y=(rand()%(int)(splo.y*10))/10.0-splo.y/2.0;
	temp.cor.z=(rand()%(int)(splo.z*10))/10.0-splo.z/2.0;

	temp.popr.x=(rand()%(int)(spopr.x*100))/100.0-spopr.x/2.0;
	temp.popr.y=(rand()%(int)(spopr.y*100))/100.0-spopr.y/2.0;

	temp.ro=rand()%1000;
	temp.r=(rand()%(int)(splo.x*100))/100.0-splo.x/2.0;
	temp.z=rand()%2;
	CL.push_front(temp);
	}
}

ClList::iterator i;

void Ef_Clouds::Draw()
{
glEnable (GL_BLEND);
glBlendFunc (GL_SRC_ALPHA, GL_ONE);
glHint (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
glHint (GL_POINT_SMOOTH_HINT, GL_NICEST);
glDepthMask (GL_FALSE);
glPushMatrix();
glTranslatef(cor.x, cor.y, cor.z);


for(i=CL.begin(); i!=CL.end(); i++)
	{
	glPushMatrix();
	glRotatef(i->ro, 0, 0, 1);
	glTranslatef(i->r, i->r, i->cor.z);
		glPushMatrix();
		if (i->z) 
			glRotatef(rot, 0, 0, 1); 
		else 
			glRotatef(-rot, 0, 0, 1);
		glTranslatef(i->popr.x, i->popr.y, 0);
		inSprite->Draw();
		glPopMatrix();
	glPopMatrix();
	}
glPopMatrix();
glDepthMask (GL_TRUE);
glDisable (GL_BLEND);
rot=rot+(*t)*speed;
}


