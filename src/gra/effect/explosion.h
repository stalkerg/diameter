#ifndef EF_EXPLOSION
#define EF_EXPLOSION
#include "./particle.h"

class Explosion:public Particle
{
public:
Explosion(int in): Particle(in)
	{
	k_deflection=1;
	}
vec3 main_dir;
float k_deflection;
virtual void Init();
virtual void Calc();
};

#endif
