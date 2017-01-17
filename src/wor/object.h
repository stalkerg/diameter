#ifndef OBJECT
#define OBJECT

#ifdef _POSIX_C_SOURCE	// shut up pyconfig.h complaints
#undef _POSIX_C_SOURCE
#endif
#include <Python.h>

#include <iostream>
#include <list>
#include <SDL.h>

#include "../uni.h"
#include "../gra/mathlib.h"
#include "./deftype.h"
#include "./decoration.h"

using namespace std;


string GetNameForType (int in);
int QuickPower (int Base, int Power);

struct IndObject
{
string Name;
int ID, Type;
};

/** Object is a base class for all object in the game world

    Базовый класс для всех обьектов в игровом мире
*/
class Object
{
float *t;
IndObject Ind;
public:
virtual ~Object()=0;
/** This function for draw object if child object not have
    function Draw return Error = (int)-1
*/
virtual int Draw (){return -1;}
/** Virtual Init function for Object. 
*/
virtual int Init (){return -1;}
virtual int SC (){ return -1;}
virtual int Calc (){return -1;}

//----
void InitT (float *in){t = in;}
void WriteName (string in){Ind.Name = in;}
void WriteType (int in){Ind.Type = in;}
void WriteID (int in){Ind.ID = in;}
string GetName (){return Ind.Name;}
int GetId (){return Ind.ID;}
int GetType (){return Ind.Type;}
};

struct UObject
{
Object *in;
void Free (){delete in;}
};

typedef list < UObject > ObjectList;

#define SizeSector 30


class SublimatObjects
{
ObjectList SubObjects, *SectorObjects;
DecorationObjectList DecorationList;
int SizeSublimat, nSectors, lenghS, sSub;
unsigned int py_next_time;
float *reltime, *tnow;
vec2 nXYSector;
std::string py_filename;
FILE *py_file;
public:
~SublimatObjects ();	
SublimatObjects ();	
SublimatObjects (int sSub);
void Init ();
void Init (int sSubi);
void WritesSub (int in);	
vec2 GetXYSectorN(vec2 in);
int GetSectorN (vec2 in);	
int GetSectorN (vec2 in, int *outx, int *outy);	
int GetSectorN (float x, float y);
int GetSectorN (float x, float y, int *outx, int *outy);
int Get4Sector (int n, float x, float y);
int GetnSectors ();
int GetlenghS ();
int GetSizeS ();
ObjectList *GetSO ();
ObjectList *GetSeO ();
Object *GetShipByName (string ship_name);
DecorationObjectList *GetDecorationList();
void SetTime(float *rt, float *tn);

unsigned GetPyNextTime();
void SetPyNextTime(int pause);
void SetPyFile(std::string name);
void RunPython();
void RunPythonOnce(std::string name);
};

ObjectList GetViewObjectList (ObjectList * inlist, int sector, int sectro4,
			      int lenS, int nsectors);

class WorldObjects
{
SublimatObjects *WorldSubOb;
int nWorld;
public:
SublimatObjects * GetSub (int in)
	{
	if(in<nWorld)
		return &WorldSubOb[in];
	return NULL;
	}
WorldObjects (int n)
	{
	nWorld = n;
	WorldSubOb = new SublimatObjects[n];
	}
int GetnWorld ()
	{
	return nWorld;
	}
void DeleteWorld()
	{
	delete[] WorldSubOb;
	}
};

#endif
