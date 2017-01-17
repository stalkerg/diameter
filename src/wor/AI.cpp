#include "./AI.h"


void AI::WriteSublimatObjects(SublimatObjects *in)
{
SO=in;
}

SublimatObjects *AI::GetSublimatObjects()
{
return SO;
}

void AI::AddObjectToSO(AI *InObject)
{
int s;
UObject TempUObject;

s=SO->GetSectorN(InObject->GetCord());

InObject->WriteSublimatObjects(SO);
InObject->WritenSector(s);

TempUObject.in=InObject;
SO->GetSO()->push_front(TempUObject);
SO->GetSeO()[s].push_front(TempUObject);
}

void AI::Kill()
{
ObjectList::iterator it1;
for (it1 = SO->GetSeO ()[nSector]. begin ();it1 != SO->GetSeO ()[nSector].end ();it1++)
	{
	if (it1->in == this)
		{
		SO->GetSeO ()[nSector].erase (it1);
		break;
		}
	}
for (it1 = SO->GetSO ()->begin (); it1 != SO->GetSO ()->end (); it1++)
	{
	if (it1->in == this)
		{
		SO->GetSO ()->erase (it1);
		break;
		}
	}
delete this;
}

void WorldInit(WorldObjects *WIN)
{
int i,s;
ObjectList::iterator it1;
for(i=0;i<WIN->GetnWorld();i++)
	{
	for(it1=WIN->GetSub(i)->GetSO()->begin(); it1!=WIN->GetSub(i)->GetSO()->end(); it1++)
		{
		AI *AItemp=(AI*)it1->in;
		WIN->GetSub(i)->GetSeO()[(s=WIN->GetSub(i)->GetSectorN(AItemp->GetCord()))].push_front(*it1);
		AItemp->WriteSublimatObjects(WIN->GetSub(i));
		AItemp->WritenSector(s);
		cout<<"Sector n:"<<s<<endl;
		}
	}
cout<<"World Init - OK"<<endl;
}



bool AI::RotTo(vec2 vin)
{
cout<<"Error: this object("<<GetName()<<") type("<<GetNameForType(GetType())<<") don`t RotTo."<<endl;
return true;
}

bool AI::FollowObject(AI *ain)
{
cout<<"Error: this object("<<GetName()<<") type("<<GetNameForType(GetType())<<") don`t FollowObject."<<endl;
return true;
}

bool AI::AttackObject(AI *ain)
{
cout<<"Error: this object("<<GetName()<<") type("<<GetNameForType(GetType())<<") don`t AttackObject."<<endl;
return true;
}

bool AI::MoveTo(vec2 vin)
{
cout<<"Error: this object("<<GetName()<<") type("<<GetNameForType(GetType())<<") don`t MoveTo."<<endl;
return true;
}

bool AI::Shoot()
{
cout<<"Error: this object("<<GetName()<<") type("<<GetNameForType(GetType())<<") don`t Shoot."<<endl;
return true;
}

bool AI::MoveToAndStop(vec2 vin)
{
cout<<"Error: this object("<<GetName()<<") type("<<GetNameForType(GetType())<<") don`t MoveToAndStop."<<endl;
return true;
}

vec2 AI::GetCord()
{
cout<<"Error: this object("<<GetName()<<") type("<<GetNameForType(GetType())<<") don`t get cord."<<endl;
vec2 null;
null[0]=0;
null[1]=0;
return null;
}

vec2 *AI::GetUCord()
{
cout<<"Error: this object("<<GetName()<<") type("<<GetNameForType(GetType())<<") don`t get Ucord."<<endl;
return NULL;
}

/*void AI::WriteUFS(fizstate *in)
{
cout<<"Error: this object("<<GetName()<<") type("<<GetNameForType(GetType())<<") don`t WriteUFS."<<endl;
}

fizstate *AI::GetUFS()
{
cout<<"Error: this object("<<GetName()<<") type("<<GetNameForType(GetType())<<") don`t GetUFS."<<endl;
return NULL;
}*/

PlayFizState *AI::GetPFS()
{
cout<<"Error: this object("<<GetName()<<") type("<<GetNameForType(GetType())<<") don`t GetPFS."<<endl;
return NULL;
}

float AI::GetRadius()
{
cout<<"Error: this object("<<GetName()<<") type("<<GetNameForType(GetType())<<") don`t GetRadius."<<endl;
return 0;
}

void AI::Dem(AI *in)
{
cout<<"Error: this object("<<GetName()<<") type("<<GetNameForType(GetType())<<") don`t Dem."<<endl;
}

