#ifndef EF_STARS
#define EF_STARS

#include <GL/gl.h>
#include <stdlib.h>
#include <iostream>
#include "../mathlib.h"

using namespace std;

struct Stars
{
Stars();
GLfloat *color, *cord;
void Draw();
};

class StarSystem
{
public:
StarSystem();
vec2 *playercord, default_playercord;
Stars StarQuant[9];
Stars tStarQuant[3];
vec2 vQuant[9];
bool BoolQuant[9], tcb;
int tcx, tcy;
void Draw();

};
#endif
