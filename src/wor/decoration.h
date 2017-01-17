#ifndef DECORATION
#define DECORATION

#include <list>

#include "../gra/model.h"
#include "../gra/sprite.h"


class DecorationObject {
	Model *model;
	Sprite *sprite;
	vec3 cord;
	vec4 color;
	float rot, sca;
	bool light, blend, depthmask, colormaterial;
	int blend_function;

	public:
	DecorationObject();

	void SetModel(Model *in_model);
	void SetSprite(Sprite *in_sprite);
	void SetCord(vec3 in_cord);
	void SetRot(float in_rot);
	void SetSca(float in_sca);
	void SetColor(vec4 in_color);

	void SetLight(bool in_light);
	void SetBlend(bool in_blend);
	void SetDepthMask(bool in_depthmask);
	void SetColorMaterial(bool in_colormaterial);
	void SetBlendFunction(int in_blend_function);

	void Draw();
};

typedef std::list < DecorationObject > DecorationObjectList;

#endif
