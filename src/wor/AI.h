#ifndef OBJECT_AI
#define OBJECT_AI

#include "./object.h"
#include "./fiz.h"
#include "../gra/model.h"

#define Do_MoveTo 1
#define Do_FollowObject 2
#define Do_RotTo 3
#define Do_AttackObject 4

struct DoCom
{
int Do,size_avec,size_afloat,size_abool;
DoCom *MasterDo;
void Init(int nvec,int nfloat,int nbool,DoCom *Min)
	{
	MasterDo=Min;
	if(nvec!=0)
		avec=new vec2[nvec];
	else
		avec=NULL;
	size_avec=nvec;
	if(nfloat!=0)
		afloat=new float[nfloat];
	else
		afloat=NULL;
	size_afloat=nfloat;
	if(nbool!=0)
		abool=new bool[nbool];
	else
		abool=NULL;
	size_abool=nbool;
	}
DoCom(int nvec,int nfloat,int nbool)
	{
	Init(nvec,nfloat,nbool,NULL);
	}
DoCom(int nvec,int nfloat,int nbool,DoCom *Min)
	{
	Init(nvec,nfloat,nbool,Min);
	}
DoCom()
	{
	avec=NULL;
	afloat=NULL;
	abool=NULL;
	}
void RemoveCom()
	{
	if(avec!=NULL)
		delete avec;
	if(afloat!=NULL)
		delete afloat;
	if(abool!=NULL)
		delete abool;
	}
~DoCom()
	{
	RemoveCom();
	}
vec2 *avec;
float *afloat;
bool *abool;
};


typedef list<DoCom*> DoList;

struct ParamsHS
{
float Health,MaxHealth,Shield,MaxShield,SpeedRShield,
      GunEnergy,MaxGunEnergy,SpeedRGunEnergy;
};

class AI: public Object
{
SublimatObjects *SO;
int nSector, Do, Frag, TypeGun;
float ADem;
DoCom *UDoVarStack;
vec2 **CamCor;
DoList DoSteck;
ParamsHS HalthSheld;
bool BStepKill;
AI *LastAttackToObject, *LastAttackReObject;
public:
AI()
	{
	BStepKill=false;
	ADem=0;
	Frag=0;
	TypeGun=0;
	LastAttackToObject=NULL;
	LastAttackReObject=NULL;
	}
~AI()
	{
	ClearStack();
	DoSteck.clear();
	}
void ClearStack()
	{
	DoList::iterator it1;
	for(it1=DoSteck.begin(); it1!=DoSteck.end(); it1++)
		delete *it1;
	}
int GetSizeSteck(){return DoSteck.size();}
ParamsHS *GetParamsHS(){return &HalthSheld;}
void UpWriteDo(DoCom *in)
	{
	if(DoSteck.size()<256)
		DoSteck.push_front(in);
	else
		{
		ClearStack();
		DoSteck.clear();
		}
	}
void WriteDo(DoCom *in)
	{
	if(DoSteck.size()<256)
		DoSteck.push_back(in);
	else
		{
		ClearStack();
		DoSteck.clear();
		}
	}
DoCom *GetDoVar(){return UDoVarStack;}
int GetDo()
	{	
	if(DoSteck.size()==0)
		return 0;
	else
		{
		UDoVarStack=DoSteck.front();
		Do=DoSteck.front()->Do;
		}
	return Do;
	}
void RemoveDo()
	{
	if(DoSteck.size()!=0)
		{
		delete DoSteck.front();
		DoSteck.pop_front();
		}
	}
float GetADem(){return ADem;}
void SetADem(float in){ADem=in;}
void AddFrag(){Frag++;}
int GetFrag(){return Frag;}
void WriteTypeGun(int in){TypeGun=in;}
int GetTypeGun(){return TypeGun;}
void RemoveAllDo(){DoSteck.clear();}
void WriteSublimatObjects(SublimatObjects *in);
void WriteCamCor(vec2 **in){CamCor=in;};
vec2 **GetCamCor(){return CamCor;}
SublimatObjects *GetSublimatObjects();
void WritenSector(int in){nSector=in;}
int GetnSector(){return nSector;}
void AddObjectToSO(AI *InObject);
void Kill();
void StepKill(bool in){BStepKill=in;}
bool GetStepKill(){return BStepKill;}
void WriteLastAttackToObject(AI *in){LastAttackToObject=in;}
void WriteLastAttackReObject(AI *in){LastAttackReObject=in;}
AI *GetLastAttackToObject(){return LastAttackToObject;}
AI *GetLastAttackReObject(){return LastAttackReObject;}
//AI

//Virtual AI
virtual bool RotTo(vec2 vin);
virtual bool MoveTo(vec2 vin);
virtual bool Shoot();
virtual bool MoveToAndStop(vec2 vin);
virtual bool FollowObject(AI *ain);
virtual bool AttackObject(AI *ain);
//Virtual:
virtual vec2 GetCord();
virtual vec2 *GetUCord();
virtual PlayFizState *GetPFS();
virtual float GetRadius();
virtual void Dem(AI *in);
};

void WorldInit(WorldObjects *WIN);


#endif

