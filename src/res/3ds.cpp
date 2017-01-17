#include "3ds.h"
#include <cmath>
#include <iostream>
#include <SDL.h>

void glm3ds::LoadModel(std::string chin, float rtmin)
{
int l_index;
in_scale = rtmin;
file_name = chin;
object = new obj_type;
if(!Load3DS (object,(char *)chin.c_str()))
	exit(0);
ObjCalcNormals(object);
nList=glGenLists(1);
glNewList(nList,GL_COMPILE);
glBegin(GL_TRIANGLES);
for (l_index=0;l_index<object->polygons_qty;l_index++)
	{
	//----------------- FIRST VERTEX -----------------
	//Normal coordinates of the first vertex
	glNormal3f(object->normal[ object->polygon[l_index].a ].x,
			object->normal[ object->polygon[l_index].a ].y,
			object->normal[ object->polygon[l_index].a ].z);
	// Texture coordinates of the first vertex
	glTexCoord2f( object->mapcoord[ object->polygon[l_index].a ].u,
		      object->mapcoord[ object->polygon[l_index].a ].v);
	// Coordinates of the first vertex
	glVertex3f( object->vertex[ object->polygon[l_index].a ].x*rtmin,
		    object->vertex[ object->polygon[l_index].a ].y*rtmin,
		    object->vertex[ object->polygon[l_index].a ].z*rtmin); //Vertex definition

	//----------------- SECOND VERTEX -----------------
	//Normal coordinates of the second vertex
	glNormal3f( object->normal[ object->polygon[l_index].b ].x,
			object->normal[ object->polygon[l_index].b ].y,
			object->normal[ object->polygon[l_index].b ].z);
	// Texture coordinates of the second vertex
	glTexCoord2f( object->mapcoord[ object->polygon[l_index].b ].u,
		      object->mapcoord[ object->polygon[l_index].b ].v);
	// Coordinates of the second vertex
	glVertex3f( object->vertex[ object->polygon[l_index].b ].x*rtmin,
		    object->vertex[ object->polygon[l_index].b ].y*rtmin,
		    object->vertex[ object->polygon[l_index].b ].z*rtmin);

        //----------------- THIRD VERTEX -----------------
	//Normal coordinates of the third vertex
	glNormal3f( object->normal[ object->polygon[l_index].c ].x,
			object->normal[ object->polygon[l_index].c ].y,
			object->normal[ object->polygon[l_index].c ].z);
	// Texture coordinates of the third vertex
	glTexCoord2f( object->mapcoord[ object->polygon[l_index].c ].u,
		      object->mapcoord[ object->polygon[l_index].c ].v);
	// Coordinates of the Third vertex
	glVertex3f( object->vertex[ object->polygon[l_index].c ].x*rtmin,
		    object->vertex[ object->polygon[l_index].c ].y*rtmin,
		    object->vertex[ object->polygon[l_index].c ].z*rtmin);
	}
glEnd();
glEndList();
time_last_draw=SDL_GetTicks();
enable = true;
}

void glm3ds::Draw()
{
time_last_draw=SDL_GetTicks();
if(!enable)
	{
	std::cout<<"ReLoad model: "<<file_name<<std::endl;
	LoadModel(file_name, in_scale);
	delete object;
	}
glCallList(nList);
}

float glm3ds::GetRadius(float rtmin)
{
int l_index;
float R=0, tr=0, R2;
for (l_index=0;l_index<object->polygons_qty;l_index++)
	{
	// Coordinates of the first vertex
	if((tr=sqrt(object->vertex[ object->polygon[l_index].a ].x*object->vertex[ object->polygon[l_index].a ].x
	+object->vertex[ object->polygon[l_index].a ].y*object->vertex[ object->polygon[l_index].a ].y))>R) R=tr; 
	// Coordinates of the second vertex
	if((tr=sqrt(object->vertex[ object->polygon[l_index].b ].x*object->vertex[ object->polygon[l_index].b ].x
	+object->vertex[ object->polygon[l_index].b ].y*object->vertex[ object->polygon[l_index].b ].y))>R) R=tr;
	// Coordinates of the Third vertex
	if((tr=sqrt(object->vertex[ object->polygon[l_index].c ].x*object->vertex[ object->polygon[l_index].c ].x
	+object->vertex[ object->polygon[l_index].c ].y*object->vertex[ object->polygon[l_index].c ].y))>R) R=tr;
	}
R2=sqrt(object->vertex[ object->polygon[0].a ].x*object->vertex[ object->polygon[0].a ].x
	+object->vertex[ object->polygon[0].a ].y*object->vertex[ object->polygon[0].a ].y);
for (l_index=0;l_index<object->polygons_qty;l_index++)
	{
	// Coordinates of the first vertex
	if((tr=sqrt(object->vertex[ object->polygon[l_index].a ].x*object->vertex[ object->polygon[l_index].a ].x
	+object->vertex[ object->polygon[l_index].a ].y*object->vertex[ object->polygon[l_index].a ].y))<R2) R2=tr; 
	// Coordinates of the second vertex
	if((tr=sqrt(object->vertex[ object->polygon[l_index].b ].x*object->vertex[ object->polygon[l_index].b ].x
	+object->vertex[ object->polygon[l_index].b ].y*object->vertex[ object->polygon[l_index].b ].y))<R2) R2=tr;   
	// Coordinates of the Third vertex
	if((tr=sqrt(object->vertex[ object->polygon[l_index].c ].x*object->vertex[ object->polygon[l_index].c ].x
	+object->vertex[ object->polygon[l_index].c ].y*object->vertex[ object->polygon[l_index].c ].y))<R2) R2=tr;
	}
if(R2<0)
	R2*=-1;
if(R2>R)
	return R2*rtmin;
else
	return R*rtmin;
}

