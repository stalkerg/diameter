#ifndef FIZ
#define FIZ

#include "./object.h"
#include "../gra/mathlib.h"

#include "../uni.h"

#include <iostream>

using namespace std;

#define Col_Sphere 1
#define Col_Line 2

class ColObject
{
short Type;
vec2 col;
public:
short GetType(){return Type;}
void WriteType(short in){Type=in;}
void WriteCol(vec2 in_col){col=in_col;}
vec2 GetCol(){return col;}
void WriteCord(vec2 *in_cord){cord=in_cord;}
protected:
vec2 *cord;
};

class ColOSphere: public ColObject
{
double r;
vec2 cor;
public:
ColOSphere(double in_R,vec2 in_cor)
	{
	r=in_R;
	cor=in_cor;	
	WriteType(Col_Sphere);
	}
double GetRadius(){return r;}
vec2 GetCord(){return cor+(*cord);}
};

class ColOLine: public ColObject
{
vec2 start,end;
public:
ColOLine(vec2 in_start, vec2 in_end)
	{
	start=in_start;
	end=in_end;
	WriteType(Col_Line);
	}
vec2 GetStart(){return start+(*cord);}
vec2 GetEnd(){return end+(*cord);}
};

typedef list<ColObject*> ColList;

class ColSystem
{
ColList ListObject;
vec2 *cord;
public:
ColSystem(vec2 *in_cord)
	{
	cord=in_cord;
	}
ColList *GetUListColObject(){return &ListObject;}
void AddObject(ColObject *in_CO);
bool CompareColObject(ColObject *in_CO1, ColObject *in_CO2);
bool CompareColSystem(ColList *in_ListObject);
bool CompareColSystem(ColSystem *in_ColSystem);
};


struct PlayFizState
{
PlayFizState()
	{
	Colision = new ColSystem(&cord);
	rotation=0;
	to_rotation=0;
	streif=0;
	player=false;
	now_power=0;
	max_power=0;
	mass=EPSILON;
	send_only_cord=false;
	next_speed_b=false;
	calc_rot_left=false;
	calc_rot_right=false;
	}
float speed_rotation, rotation, to_rotation, *reltime, *tnow, mass, max_power, now_power, streif;
vec2 speed, next_speed, cord, pre_cord, a, direction, to_direction;
ColSystem *Colision;
bool player, send_only_cord, next_speed_b, calc_rot_left, calc_rot_right;
void SetToRot(float inx, float iny, Options oin);
void CalcRotation();
void Calc();
void AddSpeed(vec2 in)
	{
	next_speed = in;
	next_speed_b=true;
	}
void RotRight();
void RotLeft();
};

void Colizion(SublimatObjects *SubWorld, ObjectList ColPhysList);

#endif
