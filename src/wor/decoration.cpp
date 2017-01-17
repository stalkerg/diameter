#include "decoration.h"

DecorationObject::DecorationObject()
{
model=NULL;
sprite=NULL;
rot=0;
sca=1;
light = false;
blend = false;
depthmask = true;
colormaterial = false;
blend_function = GL_ONE;
color[0]=1.0;
color[1]=1.0;
color[2]=1.0;
color[3]=1.0;
}

void DecorationObject::SetModel(Model *in_model)
{
model = in_model;
}

void DecorationObject::SetSprite(Sprite *in_sprite)
{
sprite = in_sprite;
}

void DecorationObject::SetCord(vec3 in_cord)
{
cord = in_cord;
}

void DecorationObject::SetRot(float in_rot)
{
rot = in_rot;
}

void DecorationObject::SetSca(float in_sca)
{
sca = in_sca;
}

void DecorationObject::SetColor(vec4 in_color)
{
color = in_color;
}

void DecorationObject::SetBlendFunction(int in_blend_function)
{
blend_function = in_blend_function;
}

void DecorationObject::SetLight(bool in_light)
{
light = in_light;
}

void DecorationObject::SetBlend(bool in_blend)
{
blend = in_blend;
}

void DecorationObject::SetDepthMask(bool in_depthmask)
{
depthmask = in_depthmask;
}

void DecorationObject::SetColorMaterial(bool in_colormaterial)
{
colormaterial = in_colormaterial;
}

void DecorationObject::Draw()
{
if (model != NULL)
	{
	if(blend)
		{
		glEnable (GL_BLEND);
		glBlendFunc (GL_SRC_ALPHA, blend_function);
		}
	glHint (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	
	glHint (GL_POINT_SMOOTH_HINT, GL_NICEST);
	if(!depthmask)
		glDepthMask (GL_FALSE);
	if(depthmask)
		glDepthMask (GL_TRUE);
	if(colormaterial)
		glDisable(GL_COLOR_MATERIAL);
	glColor4f(color.r,color.g,color.b,color.a);
	model->Draw (cord, rot, 0);
	if(colormaterial)
		glDisable(GL_COLOR_MATERIAL);
	if(blend)
		glDisable (GL_BLEND);
	if(!depthmask)
		glDepthMask (GL_TRUE);
	}
if (sprite != NULL)
	{
	if(blend)
		{
		glEnable (GL_BLEND);
		glBlendFunc (GL_SRC_ALPHA, blend_function);
		}
	glHint (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	
	glHint (GL_POINT_SMOOTH_HINT, GL_NICEST);
	if(!depthmask)
		glDepthMask (GL_FALSE);
	if(depthmask)
		glDepthMask (GL_TRUE);
	if(colormaterial)
		glEnable(GL_COLOR_MATERIAL);
	glColor4f(color.r,color.g,color.b,color.a);
	sprite->Draw (cord, rot, sca);
	if(colormaterial)
		glDisable(GL_COLOR_MATERIAL);
	if(blend)
		glDisable (GL_BLEND);
	if(!depthmask)
		glDepthMask (GL_TRUE);
	}
}



