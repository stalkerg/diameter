#include "./loadworld.h"

WorldObjects *GlobWObject;
SpriteList *load_slist;
ModelList *load_mlist;
float *e_time, *n_time;
int N_Level=0;
vec2 **load_CamCor;
Object **load_CamObject, **load_PlayerObject;
Particle *load_particle;

void LoadModel(TiXmlElement *element)
{
std::string tmp_string;
vec3 cord;
color4 color;
DecorationObject *TempDecorObject;
TempDecorObject = new DecorationObject;
TempDecorObject->SetModel(GetMFName(element->Attribute("name"), load_mlist));

for(element = element->FirstChildElement();
	element;
	element = element->NextSiblingElement())
	{
	if ((tmp_string = element->Value()) == "cord")
		{
		cord.x = atof(element->Attribute("x"));
		cord.y = atof(element->Attribute("y"));
		cord.z = atof(element->Attribute("z"));
		#ifdef DEBUG
			std::cout<<"cord x:"<<cord.x<<" y:"<<cord.y<<" z:"<<cord.z<<std::endl;
		#endif
		TempDecorObject->SetCord(cord);
		continue;
		}
	if ((tmp_string = element->Value()) == "rot")
		{
		#ifdef DEBUG
			std::cout<<"rot num:"<<element->Attribute("num")<<std::endl;
		#endif
		TempDecorObject->SetRot(atof(element->Attribute("num")));
		continue;
		}
	if ((tmp_string = element->Value()) == "SetColor")
		{
		color.r = atof(element->Attribute("r"));
		color.g = atof(element->Attribute("g"));
		color.b = atof(element->Attribute("b"));
		color.a = atof(element->Attribute("a"));
		#ifdef DEBUG
			std::cout<<"color r:"<<color.r<<" g:"<<color.g<<
			" b:"<<color.b<<" a:"<<color.a<<std::endl;
		#endif
		TempDecorObject->SetColor(color);
		continue;
		}
	if ((tmp_string = element->Value()) == "scale")
		{
		TempDecorObject->SetSca(atoi(element->Attribute("s")));
		#ifdef DEBUG
			std::cout<<"scale s:"<<atoi(element->Attribute("s"))<<std::endl;
		#endif
		continue;
		}
	if ((tmp_string = element->Value()) == "SetColorMaterial")
		{
		if((tmp_string=element->Attribute("bool")) == "true")
			{
			TempDecorObject->SetColorMaterial(true);
			#ifdef DEBUG
				std::cout<<"SetColorMaterial(true)"<<std::endl;
			#endif
			}
		else
			{
			TempDecorObject->SetColorMaterial(false);
			#ifdef DEBUG
				std::cout<<"SetColorMaterial(flase)"<<std::endl;
			#endif
			}
		continue;
		}
	if ((tmp_string = element->Value()) == "SetBlend")
		{
		if((tmp_string=element->Attribute("bool")) == "true")
			{
			TempDecorObject->SetBlend(true);
			#ifdef DEBUG
				std::cout<<"SetBlend(true)"<<std::endl;
			#endif
			}
		else
			{
			TempDecorObject->SetBlend(false);
			#ifdef DEBUG
				std::cout<<"SetBlend(false)"<<std::endl;
			#endif
			}
		continue;
		}
	if ((tmp_string=element->Value()) == "SetDepthMask")
		{
		if((tmp_string = element->Attribute("bool")) == "true")
			{
			TempDecorObject->SetDepthMask(true);
			#ifdef DEBUG
				std::cout<<"SetDepthMask(true)"<<std::endl;
			#endif
			}
		else
			{
			TempDecorObject->SetDepthMask(false);
			#ifdef DEBUG
				std::cout<<"SetDepthMask(false)"<<std::endl;
			#endif
			}
		continue;
		}
	if ((tmp_string = element->Value()) == "SetBlendFunction")
		{
		if((tmp_string = element->Attribute("name")) == "GL_ONE_MINUS_SRC_ALPHA")
			{
			TempDecorObject->SetBlendFunction(GL_ONE_MINUS_SRC_ALPHA);
			}
		if((tmp_string = element->Attribute("name")) == "GL_ONE")
			{
			TempDecorObject->SetBlendFunction(GL_ONE);
			}
		continue;
		}
	}

GlobWObject->GetSub(N_Level)->GetDecorationList()->push_back(*TempDecorObject);
delete TempDecorObject;
}


void LoadSprite(TiXmlElement *element)
{
std::string tmp_string;
vec3 cord;
color4 color;
DecorationObject *TempDecorObject;
TempDecorObject = new DecorationObject;
TempDecorObject->SetSprite(GetSFName(element->Attribute("name"), load_slist));

for(element = element->FirstChildElement();
	element;
	element = element->NextSiblingElement())
	{
	if ((tmp_string = element->Value()) == "cord")
		{
		cord.x = atof(element->Attribute("x"));
		cord.y = atof(element->Attribute("y"));
		cord.z = atof(element->Attribute("z"));
		#ifdef DEBUG
			std::cout<<"cord x:"<<cord.x<<" y:"<<cord.y<<" z:"<<cord.z<<std::endl;
		#endif
		TempDecorObject->SetCord(cord);
		continue;
		}
	if ((tmp_string = element->Value()) == "rot")
		{
		#ifdef DEBUG
			std::cout<<"rot num:"<<element->Attribute("num")<<std::endl;
		#endif
		TempDecorObject->SetRot(atof(element->Attribute("num")));
		continue;
		}
	if ((tmp_string = element->Value()) == "SetColor")
		{
		color.r = atof(element->Attribute("r"));
		color.g = atof(element->Attribute("g"));
		color.b = atof(element->Attribute("b"));
		color.a = atof(element->Attribute("a"));
		#ifdef DEBUG
			std::cout<<"color r:"<<color.r<<" g:"<<color.g<<
			" b:"<<color.b<<" a:"<<color.a<<std::endl;
		#endif
		TempDecorObject->SetColor(color);
		continue;
		}
	if ((tmp_string = element->Value()) == "scale")
		{
		TempDecorObject->SetSca(atoi(element->Attribute("s")));
		#ifdef DEBUG
			std::cout<<"scale s:"<<atoi(element->Attribute("s"))<<std::endl;
		#endif
		continue;
		}
	if ((tmp_string = element->Value()) == "SetColorMaterial")
		{
		if((tmp_string=element->Attribute("bool")) == "true")
			{
			TempDecorObject->SetColorMaterial(true);
			#ifdef DEBUG
				std::cout<<"SetColorMaterial(true)"<<std::endl;
			#endif
			}
		else
			{
			TempDecorObject->SetColorMaterial(false);
			#ifdef DEBUG
				std::cout<<"SetColorMaterial(flase)"<<std::endl;
			#endif
			}
		continue;
		}
	if ((tmp_string = element->Value()) == "SetBlend")
		{
		if((tmp_string=element->Attribute("bool")) == "true")
			{
			TempDecorObject->SetBlend(true);
			#ifdef DEBUG
				std::cout<<"SetBlend(true)"<<std::endl;
			#endif
			}
		else
			{
			TempDecorObject->SetBlend(false);
			#ifdef DEBUG
				std::cout<<"SetBlend(false)"<<std::endl;
			#endif
			}
		continue;
		}
	if ((tmp_string=element->Value()) == "SetDepthMask")
		{
		if((tmp_string = element->Attribute("bool")) == "true")
			{
			TempDecorObject->SetDepthMask(true);
			#ifdef DEBUG
				std::cout<<"SetDepthMask(true)"<<std::endl;
			#endif
			}
		else
			{
			TempDecorObject->SetDepthMask(false);
			#ifdef DEBUG
				std::cout<<"SetDepthMask(false)"<<std::endl;
			#endif
			}
		continue;
		}
	if ((tmp_string = element->Value()) == "SetBlendFunction")
		{
		if((tmp_string = element->Attribute("name")) == "GL_ONE_MINUS_SRC_ALPHA")
			{
			TempDecorObject->SetBlendFunction(GL_ONE_MINUS_SRC_ALPHA);
			}
		if((tmp_string = element->Attribute("name")) == "GL_ONE")
			{
			TempDecorObject->SetBlendFunction(GL_ONE);
			}
		continue;
		}
	}

GlobWObject->GetSub(N_Level)->GetDecorationList()->push_back(*TempDecorObject);
delete TempDecorObject;
}

void LoadDecoration(TiXmlElement *element, bool inc = false)
{
std::string tmp_string;
if(!inc)
	{
	element = element->FirstChildElement();
	}
for(;	element;
	element = element->NextSiblingElement())
	{
	if ((tmp_string = element->Value()) == "sprite")
		{
		LoadSprite(element);
		continue;
		}
	if ((tmp_string = element->Value()) == "model")
		{
		LoadModel(element);
		continue;
		}

	if ((tmp_string = element->Value()) == "include")
		{
		TiXmlDocument temp_doc;
		if(temp_doc.LoadFile(element->Attribute("path")) == false)
			{
			cout<<temp_doc.ErrorDesc()<<endl;
			exit(0);
			}
		TiXmlElement *temp_element = temp_doc.FirstChildElement();
		LoadDecoration(temp_element, true);
		}
	}
}

void LoadGaoObjectHS(TiXmlElement *element, GaoObject *TempGaoObject)
{
std::string tmp_string;
for(element = element->FirstChildElement();
	element;
	element = element->NextSiblingElement())
	{
	if ((tmp_string = element->Value()) == "health")
		{
		TempGaoObject->GetParamsHS()->Health = atof(element->Attribute("num"));
		continue;
		}
	
	if ((tmp_string = element->Value()) == "max_health")
		{
		TempGaoObject->GetParamsHS()->MaxHealth = atof(element->Attribute("num"));
		continue;
		}

	if ((tmp_string = element->Value()) == "shield")
		{
		TempGaoObject->GetParamsHS()->Shield = atof(element->Attribute("num"));
		continue;
		}

	if ((tmp_string = element->Value()) == "max_shield")
		{
		TempGaoObject->GetParamsHS()->MaxShield = atof(element->Attribute("num"));
		continue;
		}

	if ((tmp_string = element->Value()) == "speed_reg_shield")
		{
		TempGaoObject->GetParamsHS()->SpeedRShield = atof(element->Attribute("num"));
		continue;
		}

	if ((tmp_string = element->Value()) == "gun_energy")
		{
		TempGaoObject->GetParamsHS()->GunEnergy = atof(element->Attribute("num"));
		continue;
		}

	if ((tmp_string = element->Value()) == "max_gun_energy")
		{
		TempGaoObject->GetParamsHS()->MaxGunEnergy = atof(element->Attribute("num"));
		continue;
		}

	if ((tmp_string = element->Value()) == "speed_reg_gun_energy")
		{
		TempGaoObject->GetParamsHS()->SpeedRGunEnergy = atof(element->Attribute("num"));
		continue;
		}

	}
}

void LoadGaoObjectPFS(TiXmlElement *element, GaoObject *TempGaoObject)
{
std::string tmp_string;
for(element = element->FirstChildElement();
	element;
	element = element->NextSiblingElement())
	{
	if ((tmp_string = element->Value()) == "max_power")
		{
		TempGaoObject->GetPFS()->max_power = atof(element->Attribute("num"));
		continue;
		}

	if ((tmp_string = element->Value()) == "mass")
		{
		TempGaoObject->GetPFS()->mass = atof(element->Attribute("num"));
		continue;
		}

	if ((tmp_string = element->Value()) == "speed_rotation")
		{
		TempGaoObject->GetPFS()->speed_rotation = atof(element->Attribute("num"));
		continue;
		}

	if ((tmp_string = element->Value()) == "cord")
		{
		TempGaoObject->GetPFS()->cord.x = atof(element->Attribute("x"));
		TempGaoObject->GetPFS()->cord.y = atof(element->Attribute("y"));
		continue;
		}

	if ((tmp_string = element->Value()) == "player")
		{
		TempGaoObject->GetPFS()->player=true;
		*load_PlayerObject = TempGaoObject;
		continue;
		}
	}
}

void LoadGaoObjectParticle(TiXmlElement *element)
{
std::string tmp_string;
for(element = element->FirstChildElement();
	element;
	element = element->NextSiblingElement())
	{
	if ((tmp_string = element->Value()) == "nDirection")
		{
		load_particle->nDirection.x = atof(element->Attribute("x"));
		load_particle->nDirection.y = atof(element->Attribute("y"));
		load_particle->nDirection.z = atof(element->Attribute("z"));
		continue;
		}

	if ((tmp_string = element->Value()) == "cor")
		{
		load_particle->cor.x = atof(element->Attribute("x"));
		load_particle->cor.y = atof(element->Attribute("y"));
		load_particle->cor.z = atof(element->Attribute("z"));
		continue;
		}

	if ((tmp_string = element->Value()) == "start_color")
		{
		load_particle->nColor.r = atof(element->Attribute("r"));
		load_particle->nColor.g= atof(element->Attribute("g"));
		load_particle->nColor.b = atof(element->Attribute("b"));
		load_particle->nColor.a = atof(element->Attribute("a"));
		continue;
		}

	if ((tmp_string = element->Value()) == "end_color")
		{
		load_particle->kColor.r = atof(element->Attribute("r"));
		load_particle->kColor.g= atof(element->Attribute("g"));
		load_particle->kColor.b = atof(element->Attribute("b"));
		load_particle->kColor.a = atof(element->Attribute("a"));
		continue;
		}

	if ((tmp_string = element->Value()) == "nspeed")
		{
		load_particle->nSpeed = atof(element->Attribute("num"));
		continue;
		}

	if ((tmp_string = element->Value()) == "fspeed_x")
		{
		load_particle->fSpeed_x = atoi(element->Attribute("num"));
		continue;
		}

	if ((tmp_string = element->Value()) == "fspeed_y")
		{
		load_particle->fSpeed_y = atoi(element->Attribute("num"));
		continue;
		}

	if ((tmp_string = element->Value()) == "life")
		{
		load_particle->life = atof(element->Attribute("num"));
		continue;
		}
	}
load_particle->tnow = n_time;
load_particle->t = e_time;
load_particle->Init();
}

void LoadGaoObject(TiXmlElement *element, bool inc = false, GaoObject *TempGaoObject = NULL)
{
std::string tmp_string;
if(!inc)
	{
	element = element->FirstChildElement();
	TempGaoObject = new GaoObject();
	TempGaoObject->GetPFS()->reltime = e_time;
	TempGaoObject->GetPFS()->tnow = n_time;
	TempGaoObject->WriteTypeGun(1);
	TempGaoObject->WriteCamCor(load_CamCor);
	}
for(;	element;
	element = element->NextSiblingElement())
	{
	if ((tmp_string = element->Value()) == "ship_name")
		{
		TempGaoObject->WriteName(element->Attribute("name"));
		continue;
		}

	if ((tmp_string = element->Value()) == "ship_type")
		{
		tmp_string = element->Attribute("name");
		if(tmp_string == "ShipWrrior")
			TempGaoObject->WriteType(O_ShipWrrior);
			
		if(tmp_string == "ShipTrade")
			TempGaoObject->WriteType(O_ShipTrade);
		continue;
		}

	if ((tmp_string = element->Value()) == "model")
		{
		TempGaoObject->WriteModel(GetMFName(element->Attribute("name"), load_mlist));
		continue;
		}

	if ((tmp_string = element->Value()) == "explosion_small")
		{
		TempGaoObject->ExplosionSmall=GetSFName(element->Attribute("name"), load_slist);
		continue;
		}

	if ((tmp_string = element->Value()) == "explosion_big")
		{
		TempGaoObject->ExplosionBig=GetSFName(element->Attribute("name"), load_slist);
		continue;
		}

	if ((tmp_string = element->Value()) == "hs")
		{
		LoadGaoObjectHS(element, TempGaoObject);
		continue;
		}

	if ((tmp_string = element->Value()) == "pfs")
		{
		LoadGaoObjectPFS(element, TempGaoObject);
		continue;
		}

	if ((tmp_string = element->Value()) == "particle")
		{
		vec2 tempvec;
		load_particle = new Particle(atoi(element->Attribute("num_pat")));
		load_particle->inSprite = GetSFName(element->Attribute("sprite"), load_slist);
		LoadGaoObjectParticle(element);
		TempGaoObject->WriteParticle(load_particle);
		tempvec.x = atof(element->Attribute("x"));
		tempvec.y = atof(element->Attribute("y"));
		TempGaoObject->WriteParticlePos(tempvec);
		tempvec.x = atof(element->Attribute("sx"));
		tempvec.y = atof(element->Attribute("sy"));
		TempGaoObject->WriteParticlePos2(tempvec);
		continue;
		}

	if ((tmp_string = element->Value()) == "camera_on")
		{
		*load_CamObject = TempGaoObject;
		continue;
		}
	
	if ((tmp_string = element->Value()) == "include")
		{
		TiXmlDocument temp_doc;
		string path = element->Attribute("path");
		string full_path = PKGDATADIR+path;
		if(temp_doc.LoadFile(full_path.c_str()) == false)
			{
			cout<<temp_doc.ErrorDesc()<<endl;
			exit(0);
			}
		TiXmlElement *temp_element = temp_doc.FirstChildElement();
		LoadGaoObject(temp_element, true, TempGaoObject);
		continue;
		}
	}
if(!inc)
	{
	UObject tob;
	tob.in = TempGaoObject;
	GlobWObject->GetSub(N_Level)->GetSO()->push_front(tob);
	}
}

void LoadObjects(TiXmlElement *element, bool inc = false)
{
std::string tmp_string;
if(!inc)
	{
	element = element->FirstChildElement();
	}
for(;	element;
	element = element->NextSiblingElement())
	{
	if ((tmp_string = element->Value()) == "GaoObject")
		{
		LoadGaoObject(element);
		continue;
		}

	if ((tmp_string = element->Value()) == "include")
		{
		TiXmlDocument temp_doc;
		string path = element->Attribute("path");
		string full_path = PKGDATADIR+path;
		if(temp_doc.LoadFile(full_path.c_str()) == false)
			{
			cout<<temp_doc.ErrorDesc()<<endl;
			exit(0);
			}
		TiXmlElement *temp_element = temp_doc.FirstChildElement();
		LoadObjects(temp_element, true);
		continue;
		}
	}
}

void LoadLevel(TiXmlElement *element, bool inc = false)
{
std::string tmp_string;
if(!inc)
	{
	N_Level = atoi(element->Attribute("n"));
	string py_filename = element->Attribute("script");	
	GlobWObject->GetSub(N_Level)->Init(atoi(element->Attribute("scale")));
	GlobWObject->GetSub(N_Level)->SetTime(n_time, e_time);
	GlobWObject->GetSub(N_Level)->SetPyFile(PKGDATADIR+py_filename);
	element = element->FirstChildElement();
	}
for(;	element;
	element = element->NextSiblingElement())
	{
	if ((tmp_string = element->Value()) == "decoration")
		{
		LoadDecoration(element);
		continue;
		}

	if ((tmp_string = element->Value()) == "objects")
		{
		LoadObjects(element);
		continue;
		}

	if ((tmp_string = element->Value()) == "include")
		{
		TiXmlDocument temp_doc;
		string path = element->Attribute("path");
		string full_path = PKGDATADIR+path;
		if(temp_doc.LoadFile(full_path.c_str()) == false)
			{
			cout<<temp_doc.ErrorDesc()<<endl;
			exit(0);
			}
		TiXmlElement *temp_element=temp_doc.FirstChildElement();
		LoadLevel(temp_element, true);
		continue;
		}
	}
}

WorldObjects *LoadWorld(std::string file, SpriteList *in_gslist, ModelList *in_gmlist,
		float *time_n, float *time_e, vec2 **CamCor_in,
		Object **CamObject_in,  Object **PlayerObject_in)
{
WorldObjects  *tmp_obj;
std::string tmp_string = file;
tmp_string = PKGDATADIR+tmp_string;
TiXmlDocument doc;
if(doc.LoadFile(tmp_string.c_str()) == false)
	{
	cout<<tmp_string<<":"<< doc.ErrorDesc()<<endl;
	exit(0);
	}
TiXmlElement *element = doc.FirstChildElement();
tmp_obj = new WorldObjects(atoi(element->Attribute("n")));
GlobWObject = tmp_obj;
load_slist = in_gslist;
load_mlist = in_gmlist;
n_time = time_n;
e_time = time_e;
load_CamCor = CamCor_in;
load_CamObject = CamObject_in;
load_PlayerObject = PlayerObject_in;

for(element = element->FirstChildElement();
	element;
	element = element->NextSiblingElement())
	{
	if ((tmp_string=element->Value()) == "level")
		LoadLevel(element);
	
	}

return tmp_obj;
}
