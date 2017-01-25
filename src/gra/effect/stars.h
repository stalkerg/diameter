#ifndef EF_STARS
#define EF_STARS
#define GL_GLEXT_PROTOTYPES

#include <GL/gl.h>
#include <stdlib.h>
#include <iostream>
#include "../mathlib.h"

using namespace std;

class Stars {
	GLuint vbo_buffer;
	GLfloat *color, *cord;
	static const uint amount_stars = 100;

	public:
	Stars();
	void Draw();
};

class StarSystem {
	public:
	vec2 *playercord, default_playercord;
	Stars StarQuant[9];
	Stars tStarQuant[3];
	vec2 vQuant[9];
	bool BoolQuant[9], tcb;
	int tcx, tcy;

	StarSystem();
	void Draw();
};
#endif
