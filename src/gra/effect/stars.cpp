#include "./stars.h"

Stars::Stars()
{
color = new GLfloat[100*4];
cord = new GLfloat[100*3];
int i;
for (i=0; i<100; i++)
	{
	color[i*4]=1;
	color[i*4+1]=1;
	color[i*4+2]=1;
	color[i*4+3]=1.0-(rand()%100)*0.01;//1.0-(8*(rand()%100/100.0))/10;
	cord[i*3]=(rand()%2000)*0.01-10;
	cord[i*3+1]=(rand()%2000)*0.01-10;
	cord[i*3+2]=-(rand()%300)*0.1;
	}
}

void Stars::Draw()
{
glPointSize (3);
glDisable(GL_TEXTURE_2D);
glEnableClientState(GL_VERTEX_ARRAY);
glEnableClientState(GL_COLOR_ARRAY);
glColorPointer(4,GL_FLOAT,0,color);
glVertexPointer(3,GL_FLOAT,0,cord);
glPointSize(0.5);
glDrawArrays(GL_POINTS,0,25);
glPointSize(1.5);
glDrawArrays(GL_POINTS,25,25);
glPointSize(2.5);
glDrawArrays(GL_POINTS,50,25);
glPointSize(3.5);
glDrawArrays(GL_POINTS,75,25);
glColor3f(1.0, 1.0, 1.0);
glEnable(GL_TEXTURE_2D);
}
	
StarSystem::StarSystem()
{
int i;
for (i=0; i<9; i++) 
	BoolQuant[i]=false;
tcx=0;
tcy=0;
tcb=false;
}

void StarSystem::Draw()
{
if(playercord==NULL)
	playercord=&default_playercord;
	int cx=0, cy=0;
	if(playercord->x>=0) 
		cx=(int)((playercord->x+10)/20);
	if(playercord->x<0) 
		cx=(int)((playercord->x-10)/20);
	
	if(playercord->y>=0) 
		cy=(int)((playercord->y+10)/20);
	if(playercord->y<0) 
		cy=(int)((playercord->y-10)/20);
	
	if(tcb==true)
		{
		if (tcx<cx) 
			{
			tStarQuant[0]=StarQuant[0];
			tStarQuant[1]=StarQuant[1];
			tStarQuant[2]=StarQuant[2];
		
			StarQuant[0]=StarQuant[3];
			StarQuant[1]=StarQuant[4];
			StarQuant[2]=StarQuant[5];
		
			StarQuant[3]=StarQuant[6];
			StarQuant[4]=StarQuant[7];
			StarQuant[5]=StarQuant[8];
		
			StarQuant[6]=tStarQuant[0];
			StarQuant[7]=tStarQuant[1];
			StarQuant[8]=tStarQuant[2];
			//cout<<"CordSector  x:"<<cx<<"  y:"<<cy<<endl;
			}
		if(tcx>cx)
			{
			tStarQuant[0]=StarQuant[6];
			tStarQuant[1]=StarQuant[7];
			tStarQuant[2]=StarQuant[8];
		
			StarQuant[6]=StarQuant[3];
			StarQuant[7]=StarQuant[4];
			StarQuant[8]=StarQuant[5];
		
			StarQuant[3]=StarQuant[0];
			StarQuant[4]=StarQuant[1];
			StarQuant[5]=StarQuant[2];
		
			StarQuant[0]=tStarQuant[0];
			StarQuant[1]=tStarQuant[1];
			StarQuant[2]=tStarQuant[2];
			//cout<<"CordSector  x:"<<cx<<"  y:"<<cy<<endl;
			}
		if(tcy>cy)
			{
			tStarQuant[0]=StarQuant[2];
			tStarQuant[1]=StarQuant[5];
			tStarQuant[2]=StarQuant[8];
		
			StarQuant[2]=StarQuant[1];
			StarQuant[5]=StarQuant[4];
			StarQuant[8]=StarQuant[7];
		
			StarQuant[1]=StarQuant[0];
			StarQuant[4]=StarQuant[3];
			StarQuant[7]=StarQuant[6];
		
			StarQuant[0]=tStarQuant[0];
			StarQuant[3]=tStarQuant[1];
			StarQuant[6]=tStarQuant[2];
			//cout<<"CordSector  x:"<<cx<<"  y:"<<cy<<endl;
			}
		if(tcy<cy)
			{
			tStarQuant[0]=StarQuant[0];
			tStarQuant[1]=StarQuant[3];
			tStarQuant[2]=StarQuant[6];
		
			StarQuant[0]=StarQuant[1];
			StarQuant[3]=StarQuant[4];
			StarQuant[6]=StarQuant[7];
		
			StarQuant[1]=StarQuant[2];
			StarQuant[4]=StarQuant[5];
			StarQuant[7]=StarQuant[8];
		
			StarQuant[2]=tStarQuant[0];
			StarQuant[5]=tStarQuant[1];
			StarQuant[8]=tStarQuant[2];
			//cout<<"CordSector  x:"<<cx<<"  y:"<<cy<<endl;
			}
		}
	else 
		tcb=true;
	
	tcx=cx;
	tcy=cy;
	int i=0;
	int dx, dy;
	for(dx=-1; dx<2; dx++)
	{
		for(dy=-1; dy<2; dy++)
			{
				glPushMatrix();
					glTranslatef((cx+dx)*20, (cy+dy)*20+10, 0);
					StarQuant[i].Draw();
				glPopMatrix();	
			i++;
			}
	}
}
