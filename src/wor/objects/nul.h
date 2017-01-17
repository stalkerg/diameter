#ifndef OBJECT_AI_NUL
#define OBJECT_AI_NUL

#include "../AI.h"
#include "../fiz.h"
#include "../../gra/model.h"
#include "../../gra/sprite.h"
#include "../../gra/effect/particle.h"

class NulObject: public AI
{
PlayFizState PF;
AI *ParentObject;
public:
~NulObject()
	{
	
	}
NulObject (){WriteType(O_Nul);}
void WriteParent(AI *AIin){ParentObject=AIin;}
AI *GetParent(){return ParentObject;}

//Virtual

virtual PlayFizState *GetPFS(){return &PF;}
virtual int Draw();
virtual vec2 GetCord();
virtual vec2 *GetUCord();
virtual int Calc();
};

#endif
