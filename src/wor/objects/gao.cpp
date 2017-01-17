#include "./gao.h"
#include <stdlib.h>


int GaoObject::Draw ()
{
vec3 t;
vec2 t2;
t.x = PF.cord.x;
t.y = PF.cord.y;
t.z = 0;


if (InModel != NULL)
	InModel->Draw (t, PF.rotation, 0);
if (InParticle != NULL)
	{
	mat4 rot_mat;
	vec2 temp_vec;
	InParticle->nDirection.x = PF.direction.x;
	InParticle->nDirection.y = PF.direction.y;
	InParticle->nDirection.z = 0;
	InParticle->nDirection.normalize ();
	rot_mat.rotation_z(PF.rotation);
	temp_vec=rot_mat*ParticlePos2;
	InParticle->cor.x = InParticle->nDirection.x * ParticlePos.x+temp_vec.x;
	InParticle->cor.y = InParticle->nDirection.y * ParticlePos.y+temp_vec.y;
	InParticle->nSpeed = (PF.now_power * PF.now_power+fabs(PF.streif)*0.3) * 6;
	glPushMatrix ();
	glTranslatef (t.x, t.y, 0.2);
	InParticle->Draw ();
	glPopMatrix ();
	}
if (InSprite != NULL)
	InSprite->Draw (t, PF.rotation, 1);
glDisable (GL_LIGHTING);
glDisable (GL_COLOR_MATERIAL);
glColor3f(0,0,1.0);
/* glPushMatrix();
	if(GetDo ()==Do_MoveTo)
		{
		glBegin(GL_LINES);
		glVertex2f(GetCord().x,GetCord().y);
		glVertex2f(GetDoVar ()->avec[0].x,GetDoVar ()->avec[0].y);
		glEnd();
		}
	if(GetDo ()==Do_AttackObject)
		{
		glBegin(GL_LINES);
		glVertex2f(GetCord().x,GetCord().y);
		glVertex2f(O1->GetCord().x,O1->GetCord().y);
		glColor3f(1.0,0,0.0);
		glVertex2f(O1->GetCord().x,O1->GetCord().y);
		glVertex2f(GetDoVar ()->avec[1].x,GetDoVar ()->avec[1].y);
		glEnd();
		}
	glTranslatef(t.x,t.y,0);
	gluCylinder (DRadius, Radius, Radius, 0.01, 26, 1);
glPopMatrix();*/
return 0;
}

int GaoObject::Calc ()
{
/*if (GetDo()!=0)
cout<<GetName()<<"  GetDo:"<<GetDo()<<endl;*/
if(GetLastAttackReObject()!=NULL)
	if(GetLastAttackReObject()->GetStepKill())
		WriteLastAttackReObject(NULL);
if(GetLastAttackToObject()!=NULL)
	if(GetLastAttackToObject()->GetStepKill())
		WriteLastAttackToObject(NULL);

if(!GetStepKill())
	{
	if(GetParamsHS()->Health<=0)
		StepKill(true);
	IntStepKill=0;
	if(InParticle!=NULL)
		InParticle->Calc();
	switch (GetDo ())
		{
		case Do_MoveTo:
			if (Move ())
				RemoveDo ();
			break;
		case Do_RotTo:
			if (SRotTo ())
				RemoveDo ();
			break;
		case Do_AttackObject:
			if (SAttackObject ())
				RemoveDo ();
			break;
		case Do_FollowObject:
			if (MoveFollowObject ())
				RemoveDo ();
			break;
		}

	PF.Calc();

	ShootTimer+=(*PF.reltime);
	ShieldTimer+=(*PF.reltime);
	GunEnergyTimer+=(*PF.reltime);
	if(GunEnergyTimer>GetParamsHS()->SpeedRGunEnergy)
		{
		GunEnergyTimer=0;
		GetParamsHS()->GunEnergy+=1;
		if(GetParamsHS()->GunEnergy>GetParamsHS()->MaxGunEnergy)
			GetParamsHS()->GunEnergy=GetParamsHS()->MaxGunEnergy;
		}
	if(ShieldTimer>GetParamsHS()->SpeedRShield)
		{
		ShieldTimer=0;
		GetParamsHS()->Shield++;
		if(GetParamsHS()->Shield>GetParamsHS()->MaxShield)
			GetParamsHS()->Shield=GetParamsHS()->MaxShield;
		}
	int xs,ys;
	int s = GetSublimatObjects ()->GetSectorN (PF.cord,&xs,&ys);

//std::cout<<"AX:"<<xs<<" AY:"<<ys<<std::endl;

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
		BeginExplosion();
		if(GetLastAttackReObject()!=NULL)
			GetLastAttackReObject()->AddFrag();
		Kill();
		return 1;
		}
	}
return 0;
}

void GaoObject::BeginExplosion()
{
vec2 TempVec1=(**GetCamCor());
TempVec1=TempVec1-PF.cord;
float TempFloat1=TempVec1.length();
int TempInt1=MIX_MAX_VOLUME;
TempInt1-=(int)TempFloat1*4;
if(TempInt1>0)
	{
	SoundVolumeExp(TempInt1);
	SoundExp();
	}

Explosion *ExplosionTemp;
ExplosionTemp = new Explosion(100);
ExplosionTemp->inSprite=ExplosionSmall;
ExplosionTemp->cor.x=0;
ExplosionTemp->cor.y=0;
ExplosionTemp->cor.z=-10;
ExplosionTemp->nColor[0]=1.0;
ExplosionTemp->nColor[1]=0.5;
ExplosionTemp->nColor[2]=0.5;
ExplosionTemp->nColor[3]=1;
ExplosionTemp->kColor[0]=1;
ExplosionTemp->kColor[1]=0;
ExplosionTemp->kColor[2]=0;
ExplosionTemp->kColor[3]=0;
ExplosionTemp->nSpeed=2;
ExplosionTemp->fSpeed_s=1;
ExplosionTemp->life=5;
ExplosionTemp->t=PF.reltime;
ExplosionTemp->tnow=PF.tnow;
ExplosionTemp->Init();
TimObject *TempTim=new TimObject(8);
TempTim->WriteName("TemporarilyObject");
TempTim->WriteType(O_Tim);
TempTim->WriteParent(this);
TempTim->GetPFS()->cord=PF.cord;
TempTim->GetPFS()->speed=PF.speed;
TempTim->GetPFS()->reltime=PF.reltime;
TempTim->GetPFS()->tnow=PF.tnow;
TempTim->WriteParticle(ExplosionTemp);
AddObjectToSO(TempTim);
if(InModel!=NULL&&(InModel->GetName()=="Ship4"||InModel->GetName()=="Ship3"))
	{
	ExplosionTemp = new Explosion(30);
	ExplosionTemp->inSprite=ExplosionBig;
	ExplosionTemp->cor.x=0;
	ExplosionTemp->cor.y=0;
	ExplosionTemp->cor.z=-10;
	ExplosionTemp->nColor[0]=0.0;
	ExplosionTemp->nColor[1]=0.0;
	ExplosionTemp->nColor[2]=1.0;
	ExplosionTemp->nColor[3]=1;
	ExplosionTemp->kColor[0]=0;
	ExplosionTemp->kColor[1]=0;
	ExplosionTemp->kColor[2]=1;
	ExplosionTemp->kColor[3]=0;
	ExplosionTemp->nSpeed=3;
	ExplosionTemp->fSpeed_s=0;
	ExplosionTemp->life=2;
	ExplosionTemp->t=PF.reltime;
	ExplosionTemp->tnow=PF.tnow;
	ExplosionTemp->Init();
	TempTim=new TimObject(5);
	TempTim->WriteName("TemporarilyObject");
	TempTim->WriteType(O_Tim);
	TempTim->WriteParent(this);
	TempTim->GetPFS()->cord=PF.cord;
	TempTim->GetPFS()->speed=PF.speed;
	TempTim->GetPFS()->reltime=PF.reltime;
	TempTim->GetPFS()->tnow=PF.tnow;
	TempTim->WriteParticle(ExplosionTemp);
	AddObjectToSO(TempTim);
	}
}

bool GaoObject::MoveFollowObject ()
{
if(O1->GetStepKill())
	return true;
vec2 v2, v1 = O1->GetCord();
float f1, f2=0;
v2.x = GetDoVar ()->avec[0].x - PF.cord.x;
v2.y = GetDoVar ()->avec[0].y - PF.cord.y;
f1 = v2.length ();
if (!RotTo (v1))
	{
	if (f1 > 20)
		PF.now_power = 0.5;
	else
		PF.now_power = 0.0;
	}
else
	{
	f2 = PF.speed.length ();
	if (f2 == 0)
		PF.now_power = 0.1;
	else
		{
		if (f1 < 5)
			PF.now_power = f1 / (f2 * (50 * (PF.mass / PF.max_power)));
		else
			if (f1 < 10)
				PF.now_power = f1 / (f2 * (35 * (PF.mass / PF.max_power)));
			else
				if (f1 < 15)
					PF.now_power = f1 / (f2 * (5 * (PF.mass / PF.max_power)));
				else
					PF.now_power = 1.0;
		}
	if (PF.now_power > 1)
		PF.now_power = 1.0;
	}
//cout<<"f:"<<f2<<endl;
if ( f1 < 4)
	{
	//if(b1==false)WriteDo(0);
	PF.now_power = 0;
	return false;
	}
return false;
}

bool GaoObject::Move ()
{
vec2 v2, v1 = GetDoVar ()->avec[0], v3;
float f1, f2, f3;
bool b2, b3, b4=false;
v2.x = GetDoVar ()->avec[0].x - PF.cord.x;
v2.y = GetDoVar ()->avec[0].y - PF.cord.y;
f1 = v2.length ();

ObjectList::iterator it1;
f3 = 40;
AI *TempAI = NULL, *TempAI2 = NULL;
b3 = false;
b2 = false;
if (PF.now_power != 0)
	{
	short Sub4Sector = GetSublimatObjects ()->Get4Sector (GetnSector (), PF.cord.x, PF.cord.y);
	ObjectList CalcList =
	GetViewObjectList (GetSublimatObjects ()->GetSeO (), GetnSector (),
			   Sub4Sector,
			   GetSublimatObjects ()->GetlenghS (),
			   GetSublimatObjects ()->GetnSectors ());
	for (it1 = CalcList.begin (); it1 != CalcList.end (); ++it1)
		{
		float fltemp;
		vec2 tv1;
		TempAI = (AI *) (it1->in);
		if (TempAI != this && it1->in->GetType()!=O_Pul)
			{
			v2.x = TempAI->GetCord ().x - PF.cord.x;
			v2.y = TempAI->GetCord ().y - PF.cord.y;
			if ((fltemp = v2.length ()) < 10 && fltemp < f3)
				{
				v2 = -PF.direction;
				v2 *= 30;
				v2.x += PF.cord.x;
				v2.y += PF.cord.y;
				v3 = v2;
				if (IntersectCircleLine(PF.cord, v2, TempAI->GetCord (),
				    TempAI->GetRadius () + GetRadius () + 0.5) == true)
					{
					f3 = fltemp;
					TempAI2 = TempAI;
					b3 = true;
					}
				if(GetDoVar()->abool[1])
					{
					if(IntersectCircleLine(PF.cord,GetDoVar()->avec[1],
					TempAI->GetCord(),TempAI->GetRadius()+GetRadius()+5.5)
					==false)
						b4=true;
					}
				}
			}
		}
	}
if(b4&&GetDoVar()->abool[1])
	return true;

if (b3 && TempAI2 != NULL)
	{
	v2.x = TempAI2->GetPFS()->cord.x - PF.cord.x;
	v2.y = TempAI2->GetPFS()->cord.y - PF.cord.y;
	v2.normalize ();

	if (fabs (TempAI2->GetPFS()->speed.x) < 0.1
	  && fabs (TempAI2->GetPFS()->speed.y) < 0.1)
		{
		srand ((int)TempAI2->GetPFS()->speed.x);
		if ((rand () % 10) < 5)
			v2=v2.perpend_left();
		else
			v2=v2.perpend_right();
		}
	else
		{
		vec2 v3=TempAI2->GetPFS()->speed;
		v3.normalize();
		v2.x=-v3.x;
		v2.y=-v3.y;
		}
	v2 *= (TempAI2->GetRadius () + GetRadius () + 4);
	v2.x += TempAI2->GetPFS()->cord.x;
	v2.y += TempAI2->GetPFS()->cord.y;

	DoCom *DCTemp=new DoCom (2, 0, 2);
	DoCom *DCTemp2=new DoCom(1, 0, 0);
	DCTemp->avec[0] = v2;
	DCTemp->abool[0] = false;
	if(GetDoVar()->abool[1])
		DCTemp->avec[1]=GetDoVar()->avec[1];
	else
		DCTemp->avec[1]=GetDoVar()->avec[0];
	DCTemp->abool[1]=true;
	DCTemp->Do = Do_MoveTo;
	UpWriteDo (DCTemp);

	DCTemp2->avec[0] = v2;
	DCTemp2->Do = Do_RotTo;
	UpWriteDo (DCTemp2);
	PF.now_power/= 4.0;
	return false;
	}

if (!RotTo (v1))
	{
	if (f1 > 20)
		PF.now_power = 0.5;
	else
		PF.now_power = 0.0;
	}
else
	{
	f2 = PF.speed.length ();
	if (f2 == 0)
		PF.now_power = 0.1;
	else
		{
		if (f1 < 5)
			PF.now_power = 0.05;
		else
			if (f1 < 10)
				PF.now_power = 0.2;
			else
				PF.now_power = 1.0;
		}
	if (PF.now_power > 1)
		PF.now_power = 1.0;
	}
f2 = PF.speed.length ();
if (GetDoVar ()->abool[0])
	{
	if (f2 < 0.2 && f1 < 2)
		{
		PF.now_power = 0;
		return true;
		}
	}
else
	{
	if (f1 < 2)
		{
		PF.now_power = 0;
		return true;
		}
	}
return false;
}


bool GaoObject::SAttackObject ()
{
if(O1->GetStepKill())
	return true;
vec2 v2, v1, v3;
float f1, f2, f3;
bool b2, b3, b4=false;
if(GetDoVar()->abool[1])
	v1=GetDoVar()->avec[0];
else
	v1 = O1->GetCord();
v2.x = v1.x - PF.cord.x;
v2.y = v1.y - PF.cord.y;
f1 = v2.length ();

ObjectList::iterator it1;
f3 = 40;
AI *TempAI = NULL, *TempAI2 = NULL;
b3 = false;
b2 = false;
if (PF.now_power != 0)
	{
	short Sub4Sector =
	GetSublimatObjects ()->Get4Sector (GetnSector (), PF.cord.x,
					   PF.cord.y);
	ObjectList CalcList =
	GetViewObjectList (GetSublimatObjects ()->GetSeO (), GetnSector (),
			   Sub4Sector,
			   GetSublimatObjects ()->GetlenghS (),
			   GetSublimatObjects ()->GetnSectors ());
	for (it1 = CalcList.begin (); it1 != CalcList.end (); ++it1)
		{
		float fltemp;
		vec2 tv1;
		TempAI = (AI *) (it1->in);
		if (TempAI && TempAI != this && !TempAI->GetStepKill() && it1->in->GetType()!=O_Pul && it1->in->GetType()!=O_Roc && it1->in->GetType()!=O_Tim)
			{
			v2.x = TempAI->GetCord ().x - PF.cord.x;
			v2.y = TempAI->GetCord ().y - PF.cord.y;

			if ((fltemp = v2.length ()) < 10 && fltemp < f3)
				{
				v2 = -PF.direction;
				
				v2 *= 30;
				v2.x += PF.cord.x;
				v2.y += PF.cord.y;
				v3 = v2;
				if (IntersectCircleLine
				   (PF.cord, v2, TempAI->GetCord (),
				   TempAI->GetRadius () + GetRadius () + 0.5) == true)
					{
					f3 = fltemp;
					TempAI2 = TempAI;
					if(TempAI2!=O1)
						b3 = true;
					}
				if(GetDoVar()->abool[1])
					{
					if(IntersectCircleLine(PF.cord,O1->GetCord(),
					   TempAI->GetCord(),TempAI->GetRadius()+GetRadius()+5.5)
					   ==false)
						{
						b4=true;
						}
					}
				}
			}
		}
	}

if(b4&&GetDoVar()->abool[1])
	return true;
if (b3 && TempAI2 != NULL)
	{
	if(TempAI2==O1)
		Shoot();
	v2.x = TempAI2->GetPFS()->cord.x - PF.cord.x;
	v2.y = TempAI2->GetPFS()->cord.y - PF.cord.y;
	v2.normalize ();

	double ftemp;
	if (fabs (TempAI2->GetPFS()->speed.x) < 0.1
	  && fabs (TempAI2->GetPFS()->speed.y) < 0.1)
		{
		srand ((int)TempAI2->GetPFS()->speed.x);
		ftemp = rand () % 10;
		if (ftemp < 5)
			{
			ftemp = v2.x;
			v2.x = -v2.y;
			v2.y = ftemp;
			}
		else
			{
			ftemp = v2.y;
			v2.y = -v2.x;
			v2.x = ftemp;
			}
		}
	else
		{
		vec2 v3=TempAI2->GetPFS()->speed;
		v3.normalize();
		v2.x=-v3.x;
		v2.y=-v3.y;
		}
	v2 *= (TempAI2->GetRadius () + GetRadius () + 4);
	v2.x += TempAI2->GetPFS()->cord.x;
	v2.y += TempAI2->GetPFS()->cord.y;	

	DoCom *DCTemp=new DoCom (2, 0, 2);
	DCTemp->avec[0] = v2;
	DCTemp->avec[1].x = 0;
	DCTemp->avec[1].y = 0;
	DCTemp->abool[0] = false;
	DCTemp->abool[1]=true;
	DCTemp->Do = Do_AttackObject;
	UpWriteDo (DCTemp);
	//DCTemp2.avec[0] = v2;
	//DCTemp2.Do = Do_RotTo;
	//UpWriteDo (DCTemp2);
	PF.now_power/= 14.0;
	return false;
	}
if(!GetDoVar()->abool[1])
	v1=v1+O1->GetPFS()->speed+O1->GetPFS()->a;
//GetDoVar()->avec[1]=v1;
if (!RotTo (v1))
	{
	if (f1 > 20)
		PF.now_power = 0.5;
	else
		PF.now_power = 0.0;
	}
else
	{
	f2 = PF.speed.length ();
	if (f2 == 0)
		PF.now_power = 0.1;
	else
		{
		if(GetDoVar ()->abool[1])
			{
			if (f1 < 5)
				PF.now_power = 0.05;
			else
				if (f1 < 10)
					PF.now_power = 0.2;
				else
					PF.now_power = 1.0;
        		}
		else
			{
			if(f1<13)
				Shoot();
			if (f1 < 10)
				PF.now_power = 0.0;
			else
				if (f1 < 15)
					PF.now_power = 0.2;
				else
					PF.now_power = 1.0;
			}
		}
	if (PF.now_power > 1)
		PF.now_power = 1.0;
	}
f2 = PF.speed.length ();
if (GetDoVar ()->abool[0])
	{
	if (f2 < 0.2 && f1 < 2)
		{
		  PF.now_power = 0;
		  return true;
		}
	}
else
	{
	if (f1 < 2)
		{
		PF.now_power = 0;
		return true;
		}
	}
return false;
}


bool GaoObject::SRotTo ()
{
//cout<<"s:"<<GetSizeSteck()<<"  do:"<<GetDo()<<"  x:"<<GetDoVar()->avec[0].x<<"  y:"<<GetDoVar()->avec[0].y<<"  RT:"<<RotTo(GetDoVar()->avec[0])<<endl;
return RotTo (GetDoVar ()->avec[0]);
}

bool GaoObject::Shoot()
{
float TimeTSH=0;
switch(GetTypeGun())
	{
	case 1:TimeTSH=0.4;break;
	case 2:TimeTSH=0.2;break;
	case 3:TimeTSH=1.0;break;
	}

if(ShootTimer>TimeTSH&&GetParamsHS()->GunEnergy>0)
	{
	vec2 TempVec1=(**GetCamCor());
	TempVec1=TempVec1-PF.cord;
	float TempFloat1=TempVec1.length();
	int TempInt1=MIX_MAX_VOLUME;
	TempInt1-=(int)TempFloat1*4;
	if(TempInt1>0)
		{
		SoundVolumeShot(TempInt1);
		SoundShot();
		}
	ShootTimer=0;
	if(GetTypeGun()==1)
		{
		PulObject *TempPul;
		TempPul=new PulObject(PF.speed-PF.direction*15,PF.rotation,GetTypeGun());
		TempPul->WriteName("Pulya");
		TempPul->WriteType(O_Pul);
		TempPul->WriteSprite(GaoWeaponSM.PulsGun);
		GetParamsHS()->GunEnergy-=5;
		TempPul->SetADem(10);
		if(GetParamsHS()->GunEnergy<0)
			GetParamsHS()->GunEnergy=0;
		TempPul->WriteParent(this);
		TempPul->GetPFS()->reltime=PF.reltime;
		TempPul->GetPFS()->tnow=PF.tnow;
		TempPul->GetPFS()->mass=0.01;
		TempPul->GetPFS()->cord=PF.cord-PF.direction*2.5;
		TempPul->ExplosionSprite=GaoWeaponSM.PulsGunEx;
		AddObjectToSO(TempPul);
		}
	if(GetTypeGun()==2)
		{
		PulObject *TempPul;
		TempPul=new PulObject(PF.speed-PF.direction*25,PF.rotation,GetTypeGun());
		TempPul->WriteName("Liser");
		TempPul->WriteType(O_Pul);
		TempPul->WriteSprite(GaoWeaponSM.Liser);
		GetParamsHS()->GunEnergy-=3;
		TempPul->SetADem(4);
		if(GetParamsHS()->GunEnergy<0)
			GetParamsHS()->GunEnergy=0;
		TempPul->WriteParent(this);
		TempPul->GetPFS()->reltime=PF.reltime;
		TempPul->GetPFS()->tnow=PF.tnow;
		TempPul->GetPFS()->mass=0.00001;
		TempPul->GetPFS()->cord=PF.cord-PF.direction*2.5;
		TempPul->ExplosionSprite=GaoWeaponSM.LiserEx;
		AddObjectToSO(TempPul);
		}
	if(GetTypeGun()==3)
		{
		Particle *ParticleTemp;
		ParticleTemp = new Particle(30);
		ParticleTemp->inSprite=GetSFName("sp011",GaoWeaponSM.gslist);
		ParticleTemp->nDirection.x=1;
		ParticleTemp->nDirection.y=1;
		ParticleTemp->nDirection.z=0;
		ParticleTemp->cor.x=0;
		ParticleTemp->cor.y=0;
		ParticleTemp->cor.z=-10;
		ParticleTemp->nColor[0]=0.7;
		ParticleTemp->nColor[1]=0.7;
		ParticleTemp->nColor[2]=1;
		ParticleTemp->nColor[3]=1;
		ParticleTemp->kColor[0]=1;
		ParticleTemp->kColor[1]=0;
		ParticleTemp->kColor[2]=0;
		ParticleTemp->kColor[3]=0;
		ParticleTemp->nSpeed=2;
		ParticleTemp->fSpeed_x=400;
		ParticleTemp->fSpeed_y=400;
		ParticleTemp->life=0.6;
		ParticleTemp->t=PF.reltime;
		ParticleTemp->tnow=PF.tnow;
		ParticleTemp->Init();
		RocObject *TempRoc;
		vec2 TempVec=PF.speed,TempVec2;
		TempVec.normalize();
		if (PF.player)
			{
			TempVec2.x = cosf ((PF.to_rotation - 180) * (PI / 180));
			if (PF.to_rotation == 0 || PF.to_rotation == 360)
				TempVec2.y = 0;
			else
				TempVec2.y = sinf ((PF.to_rotation - 180) * (PI / 180));
			TempVec2*=(PF.now_power*8);
			TempVec2+=PF.cord;
			}
		TempRoc=new RocObject(TempVec-PF.direction*5,PF.rotation,TempVec2);
		TempRoc->WriteName("Rocket");
		TempRoc->WriteType(O_Roc);
		TempRoc->WriteModel(GaoWeaponSM.Rocket1);
		TempRoc->SetADem(15);
		TempRoc->WriteParent(this);
		TempRoc->GetPFS()->reltime=PF.reltime;
		TempRoc->GetPFS()->max_power=4;
		TempRoc->GetPFS()->speed_rotation=190;
		TempRoc->GetPFS()->mass=0.2;
		TempRoc->GetPFS()->cord=PF.direction.perpend_left();
		TempRoc->GetPFS()->cord*=2.5;
		TempRoc->GetPFS()->cord=PF.cord-TempRoc->GetPFS()->cord;
		TempRoc->WriteParticle(ParticleTemp);
		TempRoc->GetPFS()->now_power=0;
		vec2 tempvec2;
		tempvec2.x=1.8;
		tempvec2.y=1.8;
		TempRoc->WriteParticlePos(tempvec2);
		AddObjectToSO(TempRoc);
		}
	}
return false;
}

bool GaoObject::RotTo (vec2 vin)
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
	{
	GetPFS ()->to_rotation = rot;
	}
return false;
}

bool GaoObject::FollowObject (AI * ain)
{
DoCom *DCTemp=new DoCom (2, 0, 2);
DCTemp->Do = Do_FollowObject;
DCTemp->abool[0] = true;
WriteDo(DCTemp);
O1=ain;
return false;
}

bool GaoObject::AttackObject (AI * ain)
{
DoCom *DCTemp=new DoCom (2, 0, 2);
DCTemp->Do = Do_AttackObject;
DCTemp->abool[0] = false;
DCTemp->abool[1] = false;
WriteDo(DCTemp);
O1=ain;
return false;
}

bool GaoObject::MoveTo (vec2 vin)
{
if (PF.cord != vin)
	{
	DoCom *DCTemp=new DoCom (1, 0, 2);
	DCTemp->avec[0] = vin;
	DCTemp->abool[0] = false;
	DCTemp->abool[1] = false;
	//cout<<"HEL"<<endl;
	DCTemp->Do = Do_MoveTo;
	WriteDo (DCTemp);
	return false;
	}
return true;
}

bool GaoObject::MoveToAndStop (vec2 vin)
{
  if (PF.cord != vin)
    {
      DoCom *DCTemp=new DoCom (1, 0, 2);
      DCTemp->avec[0] = vin;
      DCTemp->abool[0] = true;
      DCTemp->abool[1] = false;
      DCTemp->Do = Do_MoveTo;
      WriteDo (DCTemp);
      return false;
    }
  return true;
}

vec2 GaoObject::GetCord ()
{
return PF.cord;
}

vec2 *GaoObject::GetUCord ()
{
return &PF.cord;
}

void GaoObject::Dem(AI *in)
{
GetParamsHS()->Shield-=in->GetADem();
if(GetParamsHS()->Shield<0) 
	{
	GetParamsHS()->Health+=GetParamsHS()->Shield;
	GetParamsHS()->Shield=0;
	}
}

void GaoObject::WriteModel(Model *in)
{
InModel=in;
Radius=InModel->Radius;
vec2 nullvec;
ColOSphere *TempSP1 = new ColOSphere(GetRadius(),nullvec);
PF.Colision->AddObject(TempSP1);
}

GaoObject::GaoObject ()
{
InModel = NULL;
InSprite = NULL;
InParticle = NULL;
ShootTimer=0;
ShieldTimer=0;
GunEnergyTimer=0;
StepKill(false);
IntStepKill=0;
DRadius = gluNewQuadric ();
gluQuadricDrawStyle (DRadius, GLU_LINE);
//WriteDo(0);
/*b1=false;
b2=false;
b3=false;*/
//AddShipToList(this);
}

namespace PyGaoObject
{
SpriteList *slist;
ModelList *mlist;
float *n_time, *e_time;
WeaponSM weapon_sw;
vec2 **PyCamCor;

PyObject *PyNewGaoObject(PyObject *self, PyObject *args)
	{
	GaoObject *PyGao;
	PyGao = new GaoObject;
	PyGao->WriteWeaponSM(weapon_sw);
	PyGao->WriteCamCor(PyCamCor);
	PyGao->GetPFS()->reltime=e_time;
	PyGao->GetPFS()->tnow=n_time;
	#if __WORDSIZE == 64
	return Py_BuildValue("l", (long int)PyGao);
	#else
	return Py_BuildValue("i", (int)PyGao);
	#endif
	}

PyObject *PySetName(PyObject *self, PyObject *args)
	{
	char *name = NULL;
	#if __WORDSIZE == 64
	long int addr;
	if (!PyArg_ParseTuple (args, "ls", &addr,&name))
	#else
	int addr;
	if (!PyArg_ParseTuple (args, "is", &addr,&name))
	#endif
	{
		PyErr_Print ();
		PyErr_Clear ();
		return Py_None;
	}
	if (name)
		((GaoObject*)addr)->WriteName(name);
	
	return Py_None;
	}

PyObject *PySetShipType(PyObject *self, PyObject *args)
	{
	int type;
	#if __WORDSIZE == 64
	long int addr;
	if (!PyArg_ParseTuple (args, "li", &addr,&type))
	#else
	int addr;
	if (!PyArg_ParseTuple (args, "ii", &addr,&type))
	#endif
	{
		PyErr_Print ();
		PyErr_Clear ();
		return Py_None;
	}

	if (type)
		((GaoObject*)addr)->WriteType(type);
	
	return Py_None;
	}

PyObject *PySetModel(PyObject *self, PyObject *args)
	{
	char *name = NULL;
	#if __WORDSIZE == 64
	long int addr;
	if (!PyArg_ParseTuple (args, "ls", &addr,&name))
	#else
	int addr;
	if (!PyArg_ParseTuple (args, "is", &addr,&name))
	#endif
	{
		PyErr_Print ();
		PyErr_Clear ();
		return Py_None;
	}
	if (name)
		((GaoObject*)addr)->WriteModel(GetMFName(name, mlist));
	
	return Py_None;
	}



PyObject *PySetParamsHS(PyObject *self, PyObject *args)
	{
	float Shield, MaxShield, SpeedRShield, Health, MaxHealth,
	      GunEnergy, MaxGunEnergy, SpeedRGunEnergy;
	#if __WORDSIZE == 64
	long int addr;
	if (!PyArg_ParseTuple (args, "lffffffff", &addr, &Shield, &MaxShield, 
		&SpeedRShield, &Health, &MaxHealth, &GunEnergy, 
		&MaxGunEnergy, &SpeedRGunEnergy))
	#else
	int addr;
	if (!PyArg_ParseTuple (args, "iffffffff", &addr, &Shield, &MaxShield, 
		&SpeedRShield, &Health, &MaxHealth, &GunEnergy, 
		&MaxGunEnergy, &SpeedRGunEnergy))
	#endif
	{
		PyErr_Print ();
		PyErr_Clear ();
		return Py_None;
	}

	if (addr)
		{
		((GaoObject*)addr)->GetParamsHS()->Shield=Shield;
		((GaoObject*)addr)->GetParamsHS()->MaxShield=MaxShield;
		((GaoObject*)addr)->GetParamsHS()->SpeedRShield=SpeedRShield;
		((GaoObject*)addr)->GetParamsHS()->Health=Health;
		((GaoObject*)addr)->GetParamsHS()->MaxHealth=MaxHealth;
		((GaoObject*)addr)->GetParamsHS()->GunEnergy=GunEnergy;
		((GaoObject*)addr)->GetParamsHS()->MaxGunEnergy=MaxGunEnergy;
		((GaoObject*)addr)->GetParamsHS()->SpeedRGunEnergy=SpeedRGunEnergy;
		}
	return Py_None;
	}

PyObject *PySetParticlePos(PyObject *self, PyObject *args)
	{
	float x1, y1, x2, y2;
	#if __WORDSIZE == 64
	long int addr;
	if (!PyArg_ParseTuple (args, "lffff", &addr, &x1, &y1, &x2, &y2))
	#else
	int addr;
	if (!PyArg_ParseTuple (args, "iffff", &addr, &x1, &y1, &x2, &y2))
	#endif
	{
		PyErr_Print ();
		PyErr_Clear ();
		return Py_None;
	}
	if (addr)
		{
		vec2 tempvec;
		tempvec.x = x1;
		tempvec.y = y1;
		((GaoObject*)addr)->WriteParticlePos(tempvec);
		tempvec.x = x2;
		tempvec.y = y2;
		((GaoObject*)addr)->WriteParticlePos2(tempvec);
		}
	return Py_None;
	}

PyObject *PySetPFS(PyObject *self, PyObject *args)
	{
	float max_power, mass, speed_rotation;
	#if __WORDSIZE == 64
	long int addr;
	if (!PyArg_ParseTuple (args, "lfff", &addr,&max_power, &mass, &speed_rotation))
	#else
	int addr;
	if (!PyArg_ParseTuple (args, "ifff", &addr,&max_power, &mass, &speed_rotation))
	#endif
	{
		PyErr_Print ();
		PyErr_Clear ();
		return Py_None;
	}

	if (addr)
		{
		((GaoObject*)addr)->GetPFS()->max_power=max_power;
		((GaoObject*)addr)->GetPFS()->mass=mass;
		((GaoObject*)addr)->GetPFS()->speed_rotation=speed_rotation;
		}
	return Py_None;
	}

PyObject *PySetExplosion(PyObject *self, PyObject *args)
	{
	char *name_small = NULL, *name_big = NULL;
	#if __WORDSIZE == 64
	long int addr;
	if (!PyArg_ParseTuple (args, "lss", &addr, &name_small, &name_big))
	#else
	int addr;
	if (!PyArg_ParseTuple (args, "iss", &addr, &name_small, &name_big))
	#endif
	{
		PyErr_Print ();
		PyErr_Clear ();
		return Py_None;
	}
	
	if (addr)
		{
		((GaoObject*)addr)->ExplosionSmall=GetSFName(name_small, slist);
		((GaoObject*)addr)->ExplosionBig=GetSFName(name_big, slist);
		}
	return Py_None;
	}

PyObject *PyWriteParticle(PyObject *self, PyObject *args)
	{
	#if __WORDSIZE == 64
	long int addr, addr_p;
	if (!PyArg_ParseTuple (args, "ll", &addr, &addr_p))
	#else
	int addr, addr_p;
	if (!PyArg_ParseTuple (args, "ii", &addr, &addr_p))
	#endif
	{
		PyErr_Print ();
		PyErr_Clear ();
		return Py_None;
	}
	if (addr&&addr_p)
		((GaoObject*)addr)->WriteParticle((Particle *)addr_p);
	return Py_None;
	}

PyObject *PySetCord(PyObject *self, PyObject *args)
	{
	float x, y;
	#if __WORDSIZE == 64
	long int addr;
	if (!PyArg_ParseTuple (args, "lff", &addr, &x, &y))
	#else
	int addr;
	if (!PyArg_ParseTuple (args, "iff", &addr, &x, &y))
	#endif
	{
		PyErr_Print ();
		PyErr_Clear ();
		return Py_None;
	}

	if (addr)
		{
		((GaoObject*)addr)->GetPFS()->cord.x=x;
		((GaoObject*)addr)->GetPFS()->cord.y=y;
		}
	
	return Py_None;
	}

PyObject *PyGetCord(PyObject *self, PyObject *args)
	{
	#if __WORDSIZE == 64
	long int addr;
	if (!PyArg_ParseTuple (args, "l", &addr))
	#else
	int addr;
	if (!PyArg_ParseTuple (args, "i", &addr))
	#endif
	{
		PyErr_Print ();
		PyErr_Clear ();
		return Py_None;
	}

	if (addr)
		return Py_BuildValue("ff", ((GaoObject*)addr)->GetPFS()->cord.x, ((GaoObject*)addr)->GetPFS()->cord.y);

	return Py_None;
	}

PyObject *PyAttackObject(PyObject *self, PyObject *args)
	{
	#if __WORDSIZE == 64
	long int addr, addr_p;
	if (!PyArg_ParseTuple (args, "ll", &addr, &addr_p))
	#else
	int addr, addr_p;
	if (!PyArg_ParseTuple (args, "ii", &addr, &addr_p))
	#endif
	{
		PyErr_Print ();
		PyErr_Clear ();
		return Py_None;
	}

	if (addr&&addr_p)
		((GaoObject*)addr)->AttackObject((AI*)addr_p);
	
	return Py_None;
	}

PyObject *PyFollowObject(PyObject *self, PyObject *args)
	{
	#if __WORDSIZE == 64
	long int addr, addr_p;
	if (!PyArg_ParseTuple (args, "ll", &addr, &addr_p))
	#else
	int addr, addr_p;
	if (!PyArg_ParseTuple (args, "ii", &addr, &addr_p))
	#endif
	{
		PyErr_Print ();
		PyErr_Clear ();
		return Py_None;
	}

	if (addr&&addr_p)
		((GaoObject*)addr)->FollowObject((AI*)addr_p);
	
	return Py_None;
	}

PyObject *PySetTypeGun(PyObject *self, PyObject *args)
	{
	int temp;
	#if __WORDSIZE == 64
	long int addr = 0;
	if (!PyArg_ParseTuple (args, "li", &addr, &temp))
	#else
	int addr = 0;
	if (!PyArg_ParseTuple (args, "ii", &addr, &temp))
	#endif
	{
		PyErr_Print ();
		PyErr_Clear ();
		return Py_None;
	}
	if (addr)
		((GaoObject*)addr)->WriteTypeGun(temp);

	return Py_None;
	}

void InitGaoObject(SpriteList *gslist, ModelList *gmlist,
		   float *time_n, float *time_e, WeaponSM weapon, vec2 **CamCor_in)
	{
	n_time = time_n;
	e_time = time_e;
	slist = gslist;
	mlist = gmlist;
	weapon_sw = weapon;
	PyCamCor = CamCor_in;
	static PyMethodDef GaoObjectFunctionsList[] = {
			{ "NewGaoObject", PyNewGaoObject, METH_NOARGS },
			{ "SetName", PySetName, METH_VARARGS },
			{ "SetShipType", PySetShipType, METH_VARARGS },
			{ "SetModel", PySetModel, METH_VARARGS },
			{ "SetParamsHS", PySetParamsHS, METH_VARARGS },
			{ "SetPFS", PySetPFS, METH_VARARGS },
			{ "SetParticlePos", PySetParticlePos, METH_VARARGS },
			{ "SetExplosion", PySetExplosion, METH_VARARGS },
			{ "SetCord", PySetCord, METH_VARARGS },
			{ "GetCord", PyGetCord, METH_VARARGS },
			{ "WriteParticle", PyWriteParticle, METH_VARARGS },
			{ "AttackObject", PyAttackObject, METH_VARARGS },
			{ "FollowObject", PyFollowObject, METH_VARARGS },
			{ "SetTypeGun", PySetTypeGun, METH_VARARGS },
			{ NULL, NULL, 0 }
			};
	Py_InitModule ("GaoObject", GaoObjectFunctionsList);
	}
}
