#ifndef __3DSH__
#define __3DSH__
#include <GL/gl.h>
#include <string>
#include <iostream>

#include "3dsloader.h"

class glm3ds
{
obj_type *object;
GLint nList;
float in_scale;
std::string file_name;
public:
bool enable,need_disable;
int time_last_draw;
glm3ds()
	{
	enable = false;
	need_disable = false;
	}
~glm3ds()
	{
	#ifdef DEBUG
		std::cout<<"Delete ModelList "<<file_name<<"  id:"<<nList<<std::endl;
	#endif
	glDeleteLists(nList,1);
	}
void Unable()
	{
	std::cout<<"Unable 3ds modele: "<<file_name<<std::endl;
	glDeleteLists(nList,1);
	}
void LoadModel(std::string chin,float rtmin);
void LoadModel(std::string chin){LoadModel(chin,1.0);}
void DeleteObj(){delete object;}
void Draw();
float GetRadius(float rtmin);
};


#endif

