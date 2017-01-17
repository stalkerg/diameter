/*
Texture maneger.
by stalkerg[PLG Team]
stalkerg@newmail.ru 
http://plg.lrn.ru
*/

#ifndef TEX_M
#define TEX_M

#include <GL/gl.h>
#include <iostream>
#include <list>
#include "../uni.h"

using namespace std;


class Texture
{
GLuint id;
public:
bool enable;
string name, file;
int pr, timenow;
float *ticknow;
Texture()
	{
	pr=6;
	}
void Bind()
	{
	if(!enable)
		{
		cout<<"ReLoad texture: "<<name<<endl;
		LoadTexture();
		}
	timenow=(int)(*ticknow);
	glBindTexture(GL_TEXTURE_2D, id);
	}
~Texture()
	{
	GLuint in[1];
	in[0]=id;
	#ifdef DEBUG
		cout<<"Delete Texture "<<name<<"  id:"<<id<<endl;
	#endif
	glDeleteTextures(1,in);
	}
void Unable()
	{
	cout<<"Unable texture: "<<name<<endl;
	GLuint in[1];
	in[0]=id;
	glDeleteTextures(1,in);
	enable=false;
	}
void Writeid(int ind) {id=ind;}
int Getid(){return id;}
void LoadTexture(const char *FileName, int Param);
void LoadTexture(int Param) {LoadTexture(file.c_str(), Param);}
void LoadTexture() {LoadTexture(file.c_str(), pr);}
void SetTexture(const char *FileName, char *Name, int Param) 
	{
	file=FileName;
	name=Name;
	pr=Param;
	}
void SetTexture(const char *FileName, char *Name) 
	{
	file=FileName;
	name=Name;
	}
};

typedef list <Texture> TextureList;
typedef list <Texture*> UTextureList;

struct DueTList
{
TextureList *Main;
UTextureList *Slave;
Options *in_options;
};

Texture *GetTFName(string name, TextureList *inlist);
void DeleteTFName(string name, TextureList *inlist);
void addTexture(TextureList *TL, char *FileName, char *Name, int Param, float *ticknow);
void addTexture(TextureList *TL, const char *FileName, const char *Name, int Param, float *ticknow);
/*Test mode!!!*/
Texture **GetHesh(TextureList *inlist, int *outsize);
Texture **GetHesh(TextureList *inlist);

void LoadTextureList(string file, TextureList *inlist, float *ticknow);
int ManagerTexture(void *unused);
#endif
