#ifndef EF_CLOUD
#define EF_CLOUD

#include "../sprite.h"

struct Ef_Cl
{
//Sprite *inSprite;
vec3 popr, cor;
float r, ro;
bool z;
};

typedef list <Ef_Cl> ClList;

struct Ef_Clouds
{
ClList CL;
Sprite *inSprite;
int n;
float speed, rot, *t;
vec3 cor, splo;
vec2 spopr;
void Draw();
void Init();
};

#endif


