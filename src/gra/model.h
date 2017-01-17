#ifndef MOD_M
#define MOD_M

#include "../res/3ds.h"
#include "../res/texture.h"
#include "../res/xml/tinyxml.h"
#include "./mathlib.h"
#include "../uni.h"

#include <iostream>
#include <list>


struct SubModel
{
SubModel()
	{
	inmodel3ds=NULL;
	intexture=NULL;
	AmbientMaterial[0]=0;
	AmbientMaterial[1]=0;
	AmbientMaterial[2]=0;
	AmbientMaterial[3]=0;
	DiffuseMaterial[0]=0;
	DiffuseMaterial[1]=0;
	DiffuseMaterial[2]=0;
	DiffuseMaterial[3]=0;
	SpecularMaterial[0]=0;
	SpecularMaterial[1]=0;
	SpecularMaterial[2]=0;
	SpecularMaterial[3]=0;
	EmissionMaterial[0]=0;
	EmissionMaterial[1]=0;
	EmissionMaterial[2]=0;
	EmissionMaterial[3]=0;
	ShininessMaterial=0;
	ras=0;
	}
void Destruct()
	{
	if(inmodel3ds!=NULL)
		delete inmodel3ds;
	}
glm3ds *inmodel3ds;
Texture *intexture;

GLfloat AmbientMaterial[4];
GLfloat DiffuseMaterial[4];
GLfloat SpecularMaterial[4];
GLfloat EmissionMaterial[4];
GLint ShininessMaterial;

vec3 CD, RT, SA;
int ras;
};

typedef std::list <SubModel> SubModelList;

typedef std::list <SubModelList> LodModelList;

class Model
{
LodModelList slist;
string Name;
public:
Model()
	{
	lod=0;
	}
~Model()
	{
	LodModelList::iterator i1;
	SubModelList::iterator i2;
	for (i1=slist.begin(); i1!=slist.end(); ++i1)
		{
		//for (i2=i1->begin(); i2!=i1->end(); ++i2)
		//	i2->Destruct();
		i1->clear();
		}
	slist.clear();
	}
bool TimeTest(Options *in_option);
//void ClearTime();
void Unable();
string GetName(){return Name;}
void WriteName(string in){Name=in;}
void WriteName(char *in){Name=in;}
void WriteModelList(LodModelList in){slist=in;}
int lod;
float Radius;
void Draw(int inLod);
void Draw(vec3 in, float rot, int inLod)
	{
	CD=in;
	RT.z=rot;
	Draw(inLod);
	}
vec3 CD, RT, SA;
};

typedef std::list <Model> ModelList;
typedef std::list <Model*> UModelList;

struct DueMList
{
ModelList *Main;
UModelList *Slave;
Options *in_options;
};

Model *GetMFName(string name, ModelList *inlist);
int ManagerModel(void *unused);

#endif
