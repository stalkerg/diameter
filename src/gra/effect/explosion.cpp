#include "./explosion.h"

void Explosion::Init()
{
int i;
for (i=0; i<n; i++)
	{
	nPart[i].color=nColor;
	nPart[i].cor.z=-i/100.0+0.01;
	float Rot = rand()%360;
	nPart[i].nap.x=k_deflection * cosf (Rot) + k_deflection * (-sinf (Rot));
	nPart[i].nap.y=k_deflection * sinf (Rot) + k_deflection * cosf (Rot);
	nPart[i].nap+=main_dir;
	nPart[i].speed=nSpeed;
	nPart[i].speed+=(100-rand()%200)*0.01*fSpeed_s;
	nPart[i].t=(int)(*tnow);
	nPart[i].life=true;
	}

cFade[0]=(kColor[0]-nColor[0])/life;
cFade[1]=(kColor[1]-nColor[1])/life;
cFade[2]=(kColor[2]-nColor[2])/life;
cFade[3]=(kColor[3]-nColor[3])/life;
}

void Explosion::Calc()
{
int i,temp=(int)(*tnow);

for(i=0; i<n; i++)
	{
	if(nPart[i].life)
		{
		if(temp-nPart[i].t>life*1000)
			{
			nPart[i].life=false;
			}
		else
			{
			nPart[i].cor.x+=(((*t)*nPart[i].speed)*nPart[i].nap.x);
			nPart[i].cor.y+=(((*t)*nPart[i].speed)*nPart[i].nap.y);
			nPart[i].cor.z+=(((*t)*nPart[i].speed)*nPart[i].nap.z);
			nPart[i].color[0]+=cFade[0]*(*t);
			nPart[i].color[1]+=cFade[1]*(*t);
			nPart[i].color[2]+=cFade[2]*(*t);
			nPart[i].color[3]+=cFade[3]*(*t);
			}
		}
	}
}

