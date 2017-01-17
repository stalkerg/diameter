#include "mathlib.h"

bool IntersectCircleLine(vec2 p1,vec2 p2,vec2 center,float radius)
{
float x01=p1.x-center.x;
float y01=p1.y-center.y;
float x02=p2.x-center.x;
float y02=p2.y-center.y;

float dx=x02-x01;
float dy=y02-y01;

float a=dx*dx+dy*dy;
float b=2.0f*(x01*dx+y01*dy);
float c=x01*x01+y01*y01-radius*radius;

if(-b<0)return (c<0);
if(-b<(2.0f*a))return (4.0f*a*c-b*b<0);
return (a+b+c<0);
}

