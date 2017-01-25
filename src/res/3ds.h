#ifndef __3DSH__
#define __3DSH__
#define GL_GLEXT_PROTOTYPES

#include <GL/gl.h>
#include <SDL.h>
#include <string>
#include <iostream>

#include "3dsloader.h"

class glm3ds {
	obj_type *object;
	GLuint vbo_buffer;
	GLuint vertex_count;
	float in_scale;
	std::string file_name;

	public:
	bool enable,need_disable;
	int time_last_draw;

	glm3ds() {
		enable = false;
		need_disable = false;
	}
	~glm3ds();
	void Unable();
	void LoadModel(std::string chin,float rtmin);
	void LoadModel(std::string chin){LoadModel(chin,1.0);}
	void DeleteObj(){delete object;}
	void Draw();
	float GetRadius(float rtmin);
};


#endif

