#include "./object.h"
#include "./fiz.h"
#include "./objects/nul.h"

Object::~Object()
{
}

string GetNameForType (int in)
{
switch (in)
	{
	case O_Static:
		return "Static";
	case O_ShipTrade:
		return "ShipTrade";
	case O_Pul:
		return "Pul";
	case O_Roc:
		return "Roc";
	case O_Tim:
		return "Tim";
	case O_Nul:
		return "Nul";
	}
return "Unknow type";
}

Object *SublimatObjects::GetShipByName (string ship_name)
{
ObjectList::iterator it1;
for (it1 = SubObjects.begin (); it1 != SubObjects.end (); it1++)
	{
	if (it1->in->GetName () == ship_name)
		return it1->in;
	}
return NULL;
}

int SublimatObjects::Get4Sector (int n, float x, float y)
{
float sx, sy;
sy = (int) (n / lenghS);
sx = n - sy * lenghS;
sx *= SizeSector;
sy *= SizeSector;
sy -= (lenghS * SizeSector) / 2;
sx -= (lenghS * SizeSector) / 2;
sx += SizeSector / 2;
sy += SizeSector / 2;
sx -= x;
sy -= y;
if (sy > 0 && sx > 0)
	return 3;
if (sy < 0 && sx > 0)
	return 1;
if (sy < 0 && sx < 0)
	return 2;
if (sy > 0 && sx < 0)
	return 4;
return -1;
}

SublimatObjects::~SublimatObjects ()
{
ObjectList::iterator object_iterator_1;
for (object_iterator_1=SubObjects.begin();
	     object_iterator_1!=SubObjects.end();
	     ++object_iterator_1)
		{
		object_iterator_1->Free();
		}
delete[] SectorObjects;
}

SublimatObjects::SublimatObjects ()
{}

SublimatObjects::SublimatObjects (int sSub)
{
Init (sSub);
}

void SublimatObjects::Init ()
{
Init (sSub);
}

void SublimatObjects::Init (int sSubi)
{
py_file = NULL;
sSub = sSubi;
SizeSublimat = sSub;
py_next_time = 0;
nSectors = SizeSublimat / (SizeSector*SizeSector);
lenghS = (int) sqrt ((double) nSectors);
SectorObjects = new ObjectList[nSectors];

NulObject *nul = new NulObject;
vec2 start_vec, end_vec;
start_vec.x = 10-(lenghS/2)*SizeSector;
start_vec.y = 10-(lenghS/2)*SizeSector;
end_vec.x = 10-(lenghS/2)*SizeSector;
end_vec.y = (lenghS/2)*SizeSector-10;
ColOLine *TempSP1 = new ColOLine(start_vec, end_vec);
nul->GetPFS()->Colision->AddObject(TempSP1);
start_vec.x = (lenghS/2)*SizeSector+10;
start_vec.y = 10-(lenghS/2)*SizeSector;
end_vec.x = (lenghS/2)*SizeSector+10;
end_vec.y = (lenghS/2)*SizeSector-10;
TempSP1 = new ColOLine(start_vec, end_vec);
nul->GetPFS()->Colision->AddObject(TempSP1);
start_vec.x = 10-(lenghS/2)*SizeSector;
start_vec.y = 10-(lenghS/2)*SizeSector;
end_vec.x = (lenghS/2)*SizeSector+10;
end_vec.y = 10-(lenghS/2)*SizeSector;
TempSP1 = new ColOLine(start_vec, end_vec);
nul->GetPFS()->Colision->AddObject(TempSP1);
start_vec.x = 10-(lenghS/2)*SizeSector;
start_vec.y = (lenghS/2)*SizeSector+10;
end_vec.x = (lenghS/2)*SizeSector+10;
end_vec.y = (lenghS/2)*SizeSector+10;
TempSP1 = new ColOLine(start_vec, end_vec);
nul->GetPFS()->Colision->AddObject(TempSP1);

UObject tob;
tob.in = nul;
SubObjects.push_front(tob);
std::cout<<"x:"<<start_vec.x<<" y:"<<start_vec.y<<std::endl;
std::cout<<"x:"<<end_vec.x<<" y:"<<end_vec.y<<std::endl;

cout << "nSectors:" << nSectors << endl;
cout << "lenghS:" << lenghS << endl;
}

void SublimatObjects::SetTime(float *rt, float *tn)
{
reltime = rt;
tnow = tn;
}

void SublimatObjects::WritesSub (int in)
{
sSub = in;
}

vec2 SublimatObjects::GetXYSectorN(vec2 in)
{
vec2 out;
out.x=((lenghS * SizeSector) / 2 + (int) in.x) / SizeSector;
out.y=(((lenghS * SizeSector) / 2 + (int) in.y) / SizeSector) * lenghS;
return out;
}

int SublimatObjects::GetSectorN (vec2 in)
{
return GetSectorN (in.x, in.y);
}

int SublimatObjects::GetSectorN (vec2 in, int *outx, int *outy)
{
return GetSectorN (in.x, in.y, outx, outy);
}

int SublimatObjects::GetSectorN (float x, float y)
{
int Sec=(((lenghS * SizeSector) / 2 + (int) y) / SizeSector) * lenghS +
((lenghS * SizeSector) / 2 + (int) x) / SizeSector;
return Sec;
}

int SublimatObjects::GetSectorN (float x, float y, int *outx, int *outy)
{	
(*outy)=((lenghS * SizeSector) / 2 + (int) y) / SizeSector;
(*outx)=((lenghS * SizeSector) / 2 + (int) x) / SizeSector;
return (*outy)* lenghS+(*outx);
}

int SublimatObjects::GetnSectors ()
{
return nSectors;
}

int SublimatObjects::GetlenghS ()
{
return lenghS;
}

int SublimatObjects::GetSizeS ()
{
return SizeSector;
}

ObjectList *SublimatObjects::GetSO ()
{
return &SubObjects;
}

ObjectList *SublimatObjects::GetSeO ()
{
return SectorObjects;
}

DecorationObjectList *SublimatObjects::GetDecorationList()
{
return &DecorationList;
}

unsigned SublimatObjects::GetPyNextTime()
{
return py_next_time;
}

void SublimatObjects::SetPyNextTime(int pause)
{
py_next_time = pause + SDL_GetTicks();
}

void SublimatObjects::SetPyFile(std::string name)
{
py_filename = name;
if (py_filename.size()==0)
	{
	std::cout<<"Error: py_filename is null"<<std::endl;
	exit(0);
	}
if (py_file!=NULL)
	fclose(py_file);
py_file = fopen(py_filename.c_str(), "r");
if (py_file==NULL)
	{
	std::cout<<"Error: py_file is null"<<std::endl;
	std::cout<<"py_filename:"<<py_filename<<std::endl;
	exit(0);
	}
}

void SublimatObjects::RunPython()
{
rewind(py_file);
PyRun_AnyFile(py_file, py_filename.c_str());
}

void SublimatObjects::RunPythonOnce(std::string name)
{
FILE *file;
if (name.size()==0)
	{
	std::cout<<"Error: name is null"<<std::endl;
	exit(0);
	}
file = fopen(name.c_str(), "r");
if (file==NULL)
	{
	std::cout<<"Error: file is null"<<std::endl;
	std::cout<<"name:"<<name<<std::endl;
	exit(0);
	}
PyRun_AnyFile(file, name.c_str());
if (file!=NULL)
	fclose(file);
}


ObjectList GetViewObjectList (ObjectList * inlist, int sector, int sectro4, int lenS,
			      int nsectors)
{
/*
   1 2 3
   4 5 6
   7 8 9
 */
ObjectList outlist, tmpl;
tmpl = inlist[sector];
//5
outlist.splice (outlist.begin (), tmpl);
if (sectro4 == 1)
	{
	//4
	if (sector - 1 >= 0)
		{
		tmpl=inlist[sector-1];
		outlist.splice (outlist.begin (), tmpl);
		}
	//2
	if (sector + lenS < nsectors)
		{
		tmpl=inlist[sector + lenS];
		outlist.splice (outlist.begin (), tmpl);
		}
	//1
	if (sector + lenS - 1 < nsectors)
		{
		tmpl=inlist[sector + lenS - 1];
		outlist.splice (outlist.begin (), tmpl);
		}
	}

if (sectro4 == 2)
	{
	//6
	if (sector + 1 < nsectors)
		{
		tmpl=inlist[sector + 1];
		outlist.splice (outlist.end (), tmpl);
		}
	//2
	if (sector + lenS < nsectors)
		{
		tmpl=inlist[sector + lenS];
		outlist.splice (outlist.begin (), tmpl);
		}
	//3
	if (sector + lenS + 1 < nsectors)
		{
		tmpl=inlist[sector + lenS + 1];
		outlist.splice (outlist.end (), tmpl);
		}
	}

if (sectro4 == 3)
	{
	//8
	if (sector - lenS >= 0)
		{
		tmpl=inlist[sector - lenS];
		outlist.splice (outlist.end (), tmpl);
		}
	//7
	if (sector - lenS - 1 >= 0)
		{
		tmpl=inlist[sector - lenS - 1];
		outlist.splice (outlist.end (), tmpl);
		}
	//4
	if (sector - 1 >= 0)
		{
		tmpl=inlist[sector-1];
		outlist.splice (outlist.begin (), tmpl);
		}
	}

if (sectro4 == 4)
	{
	//9
	if (sector - lenS + 1 >= 0)
		{
		tmpl=inlist[sector - lenS + 1];
		outlist.splice (outlist.end (), tmpl);
		}
	//8
	if (sector - lenS >= 0)
		{
		tmpl=inlist[sector - lenS];
		outlist.splice (outlist.end (), tmpl);
		}
	//6
	if (sector + 1 < nsectors)
		{
		tmpl=inlist[sector + 1];
		outlist.splice (outlist.end (), tmpl);
		}
	}
return outlist;
}

