#include <SDL.h>
#include "./model.h"
#include "../uni.h"


void Model::Draw(int inLod)
{
if (inLod>lod)
	return;
int p1=0;
glPushMatrix ();
glTranslatef (CD.x, CD.y, CD.z);
glRotated (RT.x, 1, 0, 0);
glPushMatrix ();
glRotated (RT.y, 0, 1, 0);
glPushMatrix ();
glRotatef (RT.z, 0, 0, 1);
LodModelList::iterator i1;
SubModelList::iterator i2;
glEnable (GL_LIGHTING);
glColor4f(0.9,0.9,0.9,0.9);
for (i1=slist.begin(); i1!=slist.end(); ++i1)
	{
	if (p1==inLod)
		{
		for (i2=i1->begin(); i2!=i1->end(); ++i2)
			{
			glPushMatrix ();
			glTranslatef (i2->CD.x, i2->CD.y, i2->CD.z);
			glRotated (i2->RT.x, 1, 0, 0);
			glPushMatrix ();
			glRotated (i2->RT.y, 0, 1, 0);
			glPushMatrix ();
			glRotatef (i2->RT.z, 0, 0, 1);
			glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT, i2->AmbientMaterial);
			glMaterialfv (GL_FRONT_AND_BACK, GL_DIFFUSE, i2->DiffuseMaterial);
			glMaterialfv (GL_FRONT_AND_BACK, GL_SPECULAR, i2->SpecularMaterial);
			glMaterialfv (GL_FRONT_AND_BACK, GL_EMISSION, i2->EmissionMaterial);
			glMateriali (GL_FRONT_AND_BACK, GL_SHININESS, i2->ShininessMaterial);
			i2->intexture->Bind();
			i2->inmodel3ds->Draw();
			glPopMatrix();
			glPopMatrix();
			glPopMatrix();
			}
		}
	p1++;
	}
glPopMatrix();
glPopMatrix();
glPopMatrix();
} 

bool Model::TimeTest(Options *in_option)
{
bool need = false;
LodModelList::iterator i1;
SubModelList::iterator i2;
for (i1=slist.begin(); i1!=slist.end(); ++i1)
	{
	for (i2=i1->begin(); i2!=i1->end(); ++i2)
		{
		if(i2->inmodel3ds->enable&&SDL_GetTicks()-i2->inmodel3ds->time_last_draw>
			in_option->mm_live_model)
			{
			i2->inmodel3ds->need_disable = true;
			need = true;
			}
		}
	}
return need;
}

void Model::Unable()
{
LodModelList::iterator i1;
SubModelList::iterator i2;
for (i1=slist.begin(); i1!=slist.end(); ++i1)
	{
	for (i2=i1->begin(); i2!=i1->end(); ++i2)
		{
		if(i2->inmodel3ds->need_disable)
			{
			i2->inmodel3ds->Unable();
			i2->inmodel3ds->need_disable = false;
			i2->inmodel3ds->enable=false;
			}
		}
	}
}

Model *GetMFName(string name, ModelList *inlist)
{
ModelList::iterator i;

for(i=inlist->begin(); i!=inlist->end(); ++i)
	{
	if (name==i->GetName())
		return &(*i);
	}
return NULL;
}

int ManagerModel(void *unused)
{
while(true)
	{
	ModelList::iterator i;
	for(i=((DueMList*)unused)->Main->begin(); i!=((DueMList*)unused)->Main->end(); ++i)
		{
		if(i->TimeTest(((DueMList*)unused)->in_options))
			((DueMList*)unused)->Slave->push_front(&(*i));
		SDL_Delay(((DueMList*)unused)->in_options->mm_iteration_pause);
		}
	SDL_Delay(((DueMList*)unused)->in_options->mm_loop_pause);
	}
return 0;
}

