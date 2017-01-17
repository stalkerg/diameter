#include "simple2d.h"


void DrawRadar(WorldObjects *in_World,Object *PlayerObject,int nWorld)
{
ObjectList::iterator it1;
glEnable( GL_BLEND );
glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
glDisable(GL_TEXTURE_2D);

glPushMatrix();
	glTranslatef(10, -8, -3);
	glColor4f(0.5, 0.5, 1, 0.5);
	glBegin(GL_QUADS);
		glVertex2f(-2, -2);
		glVertex2f(2, -2);
		glVertex2f(2, 2);
		glVertex2f(-2, 2);
	glEnd();
	glTranslatef(0, 0, 1);
	glPointSize(3);
	glBegin(GL_POINTS);
	vec2 PCord,TCord;
	if(PlayerObject!=NULL)
		for(it1=in_World->GetSub(nWorld)->GetSO()->begin(); it1!=in_World->GetSub(nWorld)->GetSO()->end(); ++it1)
			{
			if(it1->in->GetType()!=O_Tim&&it1->in->GetType()!=O_Nul)
				{
				PCord=((AI*)it1->in)->GetCord()*0.01;
				TCord=((AI*)PlayerObject)->GetCord()*0.01;
				PCord-=TCord;
				if(PCord.x<2&&PCord.y<2&&PCord.x>-2&&PCord.y>-2)
					{
					if(it1->in==PlayerObject)
						glColor4f(0, 0, 1, 1);
					else
						if(it1->in->GetType()==O_Pul
						 ||it1->in->GetType()==O_Roc)
							glColor4f(0, 1, 0, 1);
						else
							glColor4f(1, 0, 0, 1);
						glVertex2f(PCord.x, PCord.y);
					}
				}
			}
	glEnd();
glPopMatrix();
glEnable(GL_TEXTURE_2D);
glDisable( GL_BLEND );
}



