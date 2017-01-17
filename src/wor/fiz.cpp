#include "fiz.h"
#include "./objects/gao.h"
#include "./objects/pul.h"
#include <iostream>

using namespace std;

void PlayFizState::SetToRot(float inx, float iny, Options oin)
{
float temp_d;
to_direction.x = (2.0 * inx) / oin.winW - 1;
to_direction.y = (2.0 * iny) / oin.winH - 1;
temp_d = to_direction.length();
if (temp_d != 0)
	{
	to_rotation = acosf (to_direction.x / temp_d) * 180 / PI;
	if (to_direction.y > 0)
		to_rotation *= -1;
	to_rotation += 180;
	if (temp_d > 1)
		{
		temp_d = 1;
		to_direction.normalize();
		}
	}
if(send_only_cord)
	now_power=0;
else
	now_power=temp_d;
}

void PlayFizState::CalcRotation()
{
if (rotation > 180 && to_rotation < 90 && rotation - to_rotation > 180)
	rotation += (*reltime) * speed_rotation;
else
	if (rotation > 180 && to_rotation < 90 && rotation - to_rotation < 180)
		rotation -= (*reltime) * speed_rotation;
	else 
		if (rotation < 360 && to_rotation < 90 && (to_rotation + rotation) > 360)
			rotation += (*reltime) * speed_rotation;
		else 
			if (fabs (to_rotation - rotation) <= 180)
				{
				if (to_rotation > rotation)
					rotation += (*reltime) * speed_rotation;
				if (to_rotation < rotation)
					rotation -= (*reltime) * speed_rotation;
				}
			else
				{
				if (to_rotation < rotation)
					rotation += (*reltime) * speed_rotation;
				if (to_rotation > rotation)
					rotation -= (*reltime) * speed_rotation;
				}

if (rotation > 360)
	rotation = 0;
if (rotation < 0)
	rotation = 360;
direction.x = cosf ((rotation - 180) * (PI / 180));
if (rotation == 0 || rotation == 360)
	direction.y = 0;
else
	direction.y = sinf ((rotation - 180) * (PI / 180));
direction.y *= -1;
direction.x *= -1;
}

void PlayFizState::RotLeft()
{
to_rotation += (*reltime) * speed_rotation;
if (to_rotation > 360)
	to_rotation = 0;
if (to_rotation < 0)
	to_rotation = 360;
}

void PlayFizState::RotRight()
{
to_rotation -= (*reltime) * speed_rotation;
if (to_rotation > 360)
	to_rotation = 0;
if (to_rotation < 0)
	to_rotation = 360;
}

void PlayFizState::Calc()
{
if(calc_rot_left)
	RotLeft();
if(calc_rot_right)
	RotRight();
CalcRotation();

if(send_only_cord)
	now_power=0;
if(next_speed_b)
	{
	speed=next_speed;
	next_speed_b=false;
	}
/*if (player == false)
	{
	//SGall ();
	}*/
vec2 StreifA;
float F_Temp;
if(streif>=0)
	{
	StreifA.x=direction.y;
	StreifA.y=-direction.x;
	F_Temp=streif;
	}
else
	{
	StreifA.y=-direction.x;
	StreifA.x=direction.y;
	F_Temp=-streif;
	}

StreifA=((StreifA*streif)/mass)*(max_power/2);
a = ((direction * now_power) / mass) * max_power;
speed -= (a+StreifA) * (*reltime);
speed -= (speed / (2 / mass)) * (*reltime);
pre_cord = cord;
cord += speed * (*reltime);
}

/*void PlayFizstate::Work3_n ()
{
if (player == false)
	{
	SGall ();
	}
cord += speed * (*reltime);
}

void PlayFizstate::Work3_n2 ()
{
Work2();
if (player == false)
	SGall ();
cord += speed * (*reltime);
}*/

double OprSystem(vec2 in1, vec2 in2)
{
return in1.y*in2.x-in1.x*in2.y;
}

double D2(double a11, double a12, double a21, double a22)
{
return a11 * a22 - a12 * a21;
}

bool ColSystem::CompareColObject(ColObject *in_CO1, ColObject *in_CO2)
{
if(in_CO1->GetType()==Col_Sphere&&in_CO2->GetType()==Col_Sphere)
	{
	if((((ColOSphere *)in_CO1)->GetCord()-((ColOSphere *)in_CO2)->GetCord()).length ()<
	((ColOSphere *)in_CO1)->GetRadius()+((ColOSphere *)in_CO2)->GetRadius())
		return true;
	else
		return false;
	}
if((in_CO1->GetType()==Col_Line&&in_CO2->GetType()==Col_Sphere)||
	(in_CO1->GetType()==Col_Sphere&&in_CO2->GetType()==Col_Line))
	{
	if(in_CO1->GetType()==Col_Sphere)
		{
		ColObject *tmp_CO=in_CO2;
		in_CO2=in_CO1;
		in_CO1=tmp_CO;
		}
	return IntersectCircleLine(((ColOLine *)in_CO1)->GetStart(),
		((ColOLine *)in_CO1)->GetEnd(),
		((ColOSphere *)in_CO2)->GetCord(),
		((ColOSphere *)in_CO2)->GetRadius());
	}
if(in_CO1->GetType()==Col_Line&&in_CO2->GetType()==Col_Line)
	{
	double t1=0,t2=0;
	double D =(((ColOLine *)in_CO1)->GetEnd().y-((ColOLine *)in_CO1)->GetStart().y)*(((ColOLine *)in_CO2)->GetStart().x-((ColOLine *)in_CO2)->GetEnd().x)-(((ColOLine *)in_CO2)->GetStart().y-((ColOLine *)in_CO2)->GetEnd().y)*(((ColOLine *)in_CO1)->GetEnd().x-((ColOLine *)in_CO1)->GetStart().x);
	double D1=(((ColOLine *)in_CO1)->GetEnd().y-((ColOLine *)in_CO1)->GetStart().y)*(((ColOLine *)in_CO2)->GetStart().x-((ColOLine *)in_CO1)->GetStart().x)-(((ColOLine *)in_CO2)->GetStart().y-((ColOLine *)in_CO1)->GetStart().y)*(((ColOLine *)in_CO1)->GetEnd().x-((ColOLine *)in_CO1)->GetStart().x);
	double D2=(((ColOLine *)in_CO2)->GetStart().y-((ColOLine *)in_CO1)->GetStart().y)*(((ColOLine *)in_CO2)->GetStart().x-((ColOLine *)in_CO2)->GetEnd().x)-(((ColOLine *)in_CO2)->GetStart().y-((ColOLine *)in_CO2)->GetEnd().y)*(((ColOLine *)in_CO2)->GetStart().x-((ColOLine *)in_CO1)->GetStart().x);

	if(D!=0)
		{
		t1=D1/D;
		t2=D2/D;
		if( (t1<=1)&&(t1>=0) && (t2>=0)&&(t2<=1) )
			return true;
		else
			return false;
		}
	}
return false;
}

void ColSystem::AddObject(ColObject *in_CO)
{
in_CO->WriteCord(cord);
ListObject.push_front(in_CO);
}

bool ColSystem::CompareColSystem(ColList *in_ListObject)
{
ColList::iterator i1,i2;
for(i1=ListObject.begin();i1!=ListObject.end();i1++)
	for(i2=in_ListObject->begin();i2!=in_ListObject->end();i2++)
		{
		if(CompareColObject((*i1),(*i2)))
			return true;
		}
return false;
}

bool ColSystem::CompareColSystem(ColSystem *in_ColSystem)
{
ColList *in_ListObject=in_ColSystem->GetUListColObject();
ColList::iterator i1,i2;
for(i1=ListObject.begin();i1!=ListObject.end();i1++)
	for(i2=in_ListObject->begin();i2!=in_ListObject->end();i2++)
		{
		if(CompareColObject((*i1),(*i2)))
			return true;
		}
return false;
}

bool ColCompareType(int type1, int type2)
{
if(type1 != O_Pul || type2 != O_Pul)
	return true;
return false;
}



void Colizion(SublimatObjects * SubWorld, ObjectList ColPhysList)
{
ObjectList::iterator it1, it2;
vec2 TSec1, TSec2, TSec3,X_Axis,U1x,U1y,U2x,U2y,V1x,V1y,V2x,V2y;
AI *AI_1,*AI_2;
float a,b,m1,m2;
while (ColPhysList.size())
	{
	TSec1 = ((AI *) ColPhysList.begin()->in)->GetCord();
	//SubWorld->GetXYSectorN (((AI *) ColPhysList.begin ()->in)->
	//			GetCord ());
	if(ColPhysList.size()>1)
	for ((it1 = ColPhysList.begin())++;
	      it1 != ColPhysList.end();
	      ++it1)
		{
		if (ColCompareType(it1->in->GetType(), ColPhysList.begin()->in->GetType())
		    &&(!(((AI *) ColPhysList.begin ()->in)->GetStepKill()
		    ||((AI *) it1->in)->GetStepKill())))
			{
			TSec2 = ((AI *) it1->in)->GetCord ();
			//SubWorld->GetXYSectorN (((AI *) it1->in)->GetCord ());
			TSec2-=TSec1;
			if (it1->in->GetType()==O_Nul || ColPhysList.begin()->in->GetType()==O_Nul)
				{
				TSec2.x=0;
				TSec2.y=0;
				}
			if (TSec2.length () < 10 &&
			   ((AI *) ColPhysList.begin ()->in)->GetPFS()->Colision->
			   CompareColSystem(((AI *) it1->in)->GetPFS()->Colision))
				{
				/*if (it1->in->GetType()==O_Nul || ColPhysList.begin()->in->GetType()==O_Nul)
					{
					if(it1->in->GetType()!=ColPhysList.begin()->in->GetType())
						{
						if(it1->in->GetType()==O_Nul)
							{
							AI_1=(AI*)it1->in;
							AI_2=(AI*)ColPhysList.begin()->in;
							}
						else
							{
							AI_2=(AI*)it1->in;
							AI_1=(AI*)ColPhysList.begin()->in;
							}
						X_Axis = AI_2->GetPFS()->speed;
						X_Axis.normalize();
						X_Axis *= AI_2->GetRadius();
						X_Axis = X_Axis+AI_2->GetPFS()->cord;

						}
					}
				else*/
					{
					AI_1=(AI*)it1->in;
					AI_2=(AI*)ColPhysList.begin()->in;
					m1=AI_1->GetPFS()->mass;
					m2=AI_2->GetPFS()->mass;
					X_Axis = AI_2->GetCord()-AI_1->GetCord();
					X_Axis.normalize();
					a=X_Axis.dot(AI_1->GetPFS()->speed);
					U1x=X_Axis*a;
					U1y=AI_1->GetPFS()->speed-U1x;
					X_Axis = AI_1->GetCord()-AI_2->GetCord();
					X_Axis.normalize();
					b=X_Axis.dot(AI_2->GetPFS()->speed);
					U2x=X_Axis*b; 
					U2y=AI_2->GetPFS()->speed-U2x;
					V1x=(U1x*m1+U2x*m2-(U1x-U2x)*m2)/(m1+m2);
					V2x=(U1x*m1+U2x*m2-(U2x-U1x)*m1)/(m2+m1);
					V1y=U1y;
					V2y=U2y;
					AI_1->GetPFS()->speed=V1x+V1y;
					AI_2->GetPFS()->speed=V2x+V2y;
					AI_1->GetPFS()->cord=AI_1->GetPFS()->pre_cord;
					AI_2->GetPFS()->cord=AI_2->GetPFS()->pre_cord;
					}
				if (it1->in->GetType () == O_Pul)
					{
					((AI*)ColPhysList.begin ()->in)->Dem((AI*)it1->in);
					((AI*)it1->in)->Dem((AI*)ColPhysList.begin ()->in);
					if(((PulObject*)it1->in)->GetParent()!=NULL)
						{
						((AI*)ColPhysList.begin ()->in)->WriteLastAttackReObject(((PulObject*)it1->in)->GetParent());
						((PulObject*)it1->in)->GetParent()->WriteLastAttackToObject((AI*)ColPhysList.begin()->in);
						}
					//((AI*)it1->in)->Kill();
					((AI*)it1->in)->StepKill(true);
					ColPhysList.erase (it1);
					}
				if (ColPhysList.begin ()->in->GetType () == O_Pul)
					{
					((AI*)it1->in)->Dem((AI*)ColPhysList.begin ()->in);
					((AI*)ColPhysList.begin ()->in)->Dem((AI*)it1->in);
					if(((PulObject*)ColPhysList.begin ()->in)->GetParent()!=NULL)
						{
						((AI*)it1->in)->WriteLastAttackReObject(((PulObject*)ColPhysList.begin ()->in)->GetParent());
						((PulObject*)ColPhysList.begin ()->in)->GetParent()->WriteLastAttackToObject((AI*)it1->in);
						}
					//((AI*)ColPhysList.begin ()->in)->Kill();
					((AI*)ColPhysList.begin ()->in)->StepKill(true);
					ColPhysList.pop_front ();
					}
				//Rocket
				if (it1->in->GetType () == O_Roc)
					{
					((AI*)ColPhysList.begin ()->in)->Dem((AI*)it1->in);
					((AI*)ColPhysList.begin ()->in)->WriteLastAttackReObject(((RocObject*)it1->in)->GetParent());
					((RocObject*)it1->in)->GetParent()->WriteLastAttackToObject((AI*)ColPhysList.begin()->in);
					((AI*)it1->in)->Kill();
					ColPhysList.erase (it1);
					}
				if (ColPhysList.begin ()->in->GetType () == O_Roc)
					{
					((AI*)it1->in)->Dem((AI*)ColPhysList.begin ()->in);
					((AI*)it1->in)->WriteLastAttackReObject(((RocObject*)ColPhysList.begin ()->in)->GetParent());
					((RocObject*)ColPhysList.begin ()->in)->GetParent()->WriteLastAttackToObject((AI*)it1->in);
					((AI*)ColPhysList.begin ()->in)->Kill();
					ColPhysList.pop_front ();
					}
				}
			}
		}
	ColPhysList.pop_front ();
	}
}
