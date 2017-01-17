/*Texture meneger.
by stalkerg[PLG Team]
stalkerg@newmail.ru 
http://plg.lrn.ru
*/


#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include <list>
#include <string.h>
#include <SDL.h>
#include <SDL_image.h>
#include "./xml/tinyxml.h"
#include "../uni.h"
#include "texture.h"
#include "tga.h"

using namespace std;

Texture *GetTFName(string name, TextureList *inlist)
{
TextureList::iterator i;
for(i=inlist->begin(); i!=inlist->end(); ++i)
	if (name==i->name) 
		return &(*i);
return NULL;
}

/*Get Matrix view texture.*/
Texture **GetHesh(TextureList *inlist, int *outsize)
{
Texture **temp;
int i2=0;
*outsize=inlist->size();
temp=(Texture**)calloc(inlist->size(), sizeof(Texture*));
//temp= new (Texture*)[inlist->size()];
TextureList::iterator i;
for (i=inlist->begin(); i!=inlist->end(); ++i)
	{
	temp[i2]= &(*i);
	i2++;
	}
return temp;
}

/*Without size out.*/
Texture **GetHesh(TextureList *inlist)
{
int nulll;
return GetHesh(inlist, &nulll);
}

void DeleteTFName(string name, TextureList *inlist)
{
TextureList::iterator i;
for(i=inlist->begin(); i!=inlist->end(); ++i)
	{
	if (name==i->name)
		{
		inlist->erase(i);
		return;
		}
	}
}

void addTexture(TextureList *TL, char *FileName, char *Name, int Param, float *ticknow)
{
string temp=Name;
TextureList::iterator i;
for(i=TL->begin(); i!=TL->end(); ++i)
	{
	if (i->name==temp)
		{
		cout<<"Error add texture(Dublicated name "<<Name<<")"<<endl;
		return;
		}
	}

Texture Temp;
Temp.ticknow=ticknow;
Temp.SetTexture(FileName, Name);	
TL->push_front(Temp);
GetTFName(Name,TL)->LoadTexture(Param);
}

void addTexture(TextureList *TL, const char *FileName, const char *Name, int Param, float *ticknow)
{
string temp=Name;
TextureList::iterator i;
for(i=TL->begin(); i!=TL->end(); ++i)
	{
	if (i->name==temp) 
		{
		cout<<"Error add texture(Dublicated name "<<Name<<")"<<endl;
		return;
		}
	}

Texture Temp;
Temp.ticknow=ticknow;
Temp.name=Name;
Temp.file=FileName;
TL->push_front(Temp);
GetTFName(Name,TL)->LoadTexture(Param);
}

void Texture::LoadTexture(const char *FileName, int Param)
{
string t1;
SDL_Surface *texture=NULL;
SDL_RWops *rw=NULL;
file=FileName;
t1=strrchr(FileName,'.');
struct DTA temp;
int swi=0;
FILE *prov=fopen(FileName,"r");
if (prov==NULL) 
	{
	cout<<"Error load texture:"<<FileName<<endl;
	exit(1);
	}
fclose(prov);

if (t1==".jpg")  {texture = IMG_LoadJPG_RW (rw=SDL_RWFromFile (FileName, "rb"));swi=1;goto End;}
if (t1==".JPG")  {texture = IMG_LoadJPG_RW (rw=SDL_RWFromFile (FileName, "rb"));swi=1;goto End;}
if (t1==".bmp")  {texture = IMG_LoadBMP_RW (rw=SDL_RWFromFile (FileName, "rb"));swi=1;goto End;}
if (t1==".BMP")  {texture = IMG_LoadBMP_RW (rw=SDL_RWFromFile (FileName, "rb"));swi=1;goto End;}
if (t1==".tga")  {temp= LDTA(FileName);swi=1;goto End;}
if (t1==".png")  {texture = IMG_LoadPNG_RW (rw=SDL_RWFromFile (FileName, "rb"));swi=1;}
End:
if (texture==NULL||swi==0) 
	{
	cout<<"Error load texture:"<<FileName<<endl;
	exit(1);
	}

glGenTextures(1,&id); 
glBindTexture (GL_TEXTURE_2D, id);
//glPixelStorei (GL_UNPACK_ALIGNMENT, 1);
//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAX_ANISOTROPY_EXT,3);
glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

switch(Param)
	{
	case 0:
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		break;
	case 1:
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		break;
	case 2:
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		break;
	case 3:
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		break;
	case 4:
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		break;
	case 5:
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		break;
	case 6:
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		break;
	}

glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
if (t1==".tga") 
	{
	gluBuild2DMipmaps (GL_TEXTURE_2D, 3, temp.ww, temp.wh, 
			   temp.texFormat, GL_UNSIGNED_BYTE, temp.imageData);
	free(temp.imageData);
	}
if(t1==".jpg"||t1==".JPG"||t1==".bmp"||t1==".BMP")
	{
	gluBuild2DMipmaps (GL_TEXTURE_2D, 3, texture->w, texture->h,
			   GL_RGB, GL_UNSIGNED_BYTE, texture->pixels);
	}
if (t1==".png") 
	{
	gluBuild2DMipmaps (GL_TEXTURE_2D, 4, texture->w, texture->h,
			   GL_RGBA, GL_UNSIGNED_BYTE, texture->pixels);
	}

SDL_FreeSurface(texture);
SDL_FreeRW(rw);
enable=true;
timenow=SDL_GetTicks();
};

void LoadTextureList(string file,TextureList *inlist, float *ticknow)
{
string temp;
TiXmlDocument doc;
if(doc.LoadFile(file.c_str()) == false)
	{
	cout<<file<<":"<< doc.ErrorDesc()<<endl;
	exit(0);
	}
TiXmlElement *element=doc.FirstChildElement();
element=element->FirstChildElement();
while (element)
	{
	while (true)
		{
		if((temp=element->Value())=="texture") 
			{
			#ifdef DEBUG
			cout<<element->Value()<<"\t"<<element->Attribute("name")<<endl;
			#endif
			string N,P;
			N=element->Attribute("name");
			P=element->Attribute("path");
			P=PKGDATADIR+P;
			addTexture(inlist, P.c_str(), N.c_str(), 6, ticknow);
			}
		if (element->NextSiblingElement())
			element=element->NextSiblingElement();
		else 
			break;
		}
	element=element->FirstChildElement();
	}
}

int ManagerTexture(void *unused)
{
while(true)
	{
	TextureList::iterator i;
	for(i=((DueTList*)unused)->Main->begin(); i!=((DueTList*)unused)->Main->end(); ++i)
		{
		if(i->enable&&SDL_GetTicks()-i->timenow>
		((DueTList*)unused)->in_options->tm_live_texture)
			((DueTList*)unused)->Slave->push_front(&(*i));
		SDL_Delay(((DueTList*)unused)->in_options->tm_iteration_pause);
		}
	SDL_Delay(((DueTList*)unused)->in_options->tm_loop_pause);
	}
return 0;
}

