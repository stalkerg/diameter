#ifndef LOADWORLD
#define LOADWORLD

#include "../gra/sprite.h"
#include "../gra/model.h"
#include "../wor/object.h"
#include "../wor/objects/gao.h"
#include "../uni.h"

/**          Load world from xml file.
*/
WorldObjects *LoadWorld(std::string file,SpriteList *gslist, ModelList *gmlist,
		float *time_n, float *time_e, vec2 **CamCor_in,
		Object **CamObject_in, Object **PlayerObject_in);

#endif
