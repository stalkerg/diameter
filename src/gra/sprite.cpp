#include "./sprite.h"

void Sprite::Draw(vec3 in, float rot)
{
intexture->Bind();
glPushMatrix();
glTranslatef(in.x, in.y, in.z);
glPushMatrix();
	glRotatef(rot, 0, 0, 1);
	glBegin( GL_QUADS );
	glNormal3f(0, 0, 1.0);
	glTexCoord2f( 0.0f, 0.0f );
	glVertex3f( (-0.5f+sx1)*insca, (0.5f+sy1)*insca, 0 );
	glTexCoord2f( 1.0f, 0.0f );
	glVertex3f( (0.5f+sx2)*insca, (0.5f+sy1)*insca,  0 );
	glTexCoord2f( 1.0f, 1.0f );
	glVertex3f( (0.5f+sx2)*insca, (-0.5f+sy2)*insca, 0 );
	glTexCoord2f( 0.0f, 1.0f );
	glVertex3f( (-0.5f+sx1)*insca, (-0.5f+sy2)*insca, 0);
	glEnd( );
glPopMatrix();
glPopMatrix();
}

void Sprite::Draw(vec3 in, float rot, float sca)
{
intexture->Bind();
glPushMatrix();
glTranslatef(in.x, in.y, in.z);
//glPushMatrix();
	glRotatef(rot, 0, 0, 1);
	glBegin( GL_QUADS );
	glNormal3f(0, 0, 1.0);
	glTexCoord2f( 0.0f, 0.0f );
	glVertex3f( (-0.5f+sx1)*sca*insca, (0.5f+sy1)*sca*insca, 0 );
	glTexCoord2f( 1.0f, 0.0f );
	glVertex3f( (0.5f+sx2)*sca*insca, (0.5f+sy1)*sca*insca,  0 );
	glTexCoord2f( 1.0f, 1.0f );	
	glVertex3f( (0.5f+sx2)*sca*insca, (-0.5f+sy2)*sca*insca, 0 );
	glTexCoord2f( 0.0f, 1.0f );
	glVertex3f( (-0.5f+sx1)*sca*insca, (-0.5f+sy2)*sca*insca, 0);
	glEnd( );
//glPopMatrix();
glPopMatrix();
}

void SpriteInit(string file, SpriteList *inlist, TextureList *inlist2)
{
int b=0;
string temp;
TiXmlDocument doc;
if(doc.LoadFile(file.c_str()) == false)
	{
	cout<< doc.ErrorDesc()<<endl;
	exit(0);
	}
TiXmlElement *element=doc.FirstChildElement();
Sprite SpriteTemp;

while (element)
	{
	while (true)
		{
		if(b==1)
			{
			if ((temp=element->Value())=="sprite")
				{
				SpriteTemp.sx1=atof(element->Attribute("sx1"));
				SpriteTemp.sx2=atof(element->Attribute("sx2"));
				SpriteTemp.sy1=atof(element->Attribute("sy1"));
				SpriteTemp.sy2=atof(element->Attribute("sy2"));
				SpriteTemp.insca=atof(element->Attribute("sca"));
				SpriteTemp.intexture=GetTFName(element->Attribute("tex"),inlist2);
				SpriteTemp.WriteName(element->Attribute("name"));
				inlist->push_front(SpriteTemp);
				}
			}	
		if (element->NextSiblingElement())
			element=element->NextSiblingElement();
		else
			break;
		}
	element=element->FirstChildElement();
	b=1;
	}
}

Sprite *GetSFName(string name,SpriteList *inlist)
{
SpriteList::iterator i;
for(i=inlist->begin(); i!=inlist->end(); i++)
	{
	if (name==i->GetName())
		return &(*i);
	}
cout<<"Not found sprite ("<<name<<") return NULL!!!"<<endl;
return NULL;
}



