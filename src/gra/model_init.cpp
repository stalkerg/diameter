#include "model_init.h"

ModelList *model_init_modellist;
TextureList *model_init_texturelist;
Model model_init_model;
LodModelList model_init_lodmodellist;
SubModelList model_init_submodellist;
SubModel model_init_submodel;


void miLoadSubModel(TiXmlElement *element)
{
string tmp_string;
float rtm=1;
model_init_submodel.intexture=GetTFName("NULL",model_init_texturelist);
for(element = element->FirstChildElement();
	element;
	element = element->NextSiblingElement())
	{
	if ((tmp_string=element->Value())=="CD")
		{
		model_init_submodel.CD.x=atof(element->Attribute("x"));
		model_init_submodel.CD.y=atof(element->Attribute("y"));
		model_init_submodel.CD.z=atof(element->Attribute("z"));
		}
	if ((tmp_string=element->Value())=="RT")
		{
		model_init_submodel.RT.x=atof(element->Attribute("x"));
		model_init_submodel.RT.y=atof(element->Attribute("y"));
		model_init_submodel.RT.z=atof(element->Attribute("z"));
		}
	if ((tmp_string=element->Value())=="SA")
		{
		model_init_submodel.SA.x=atof(element->Attribute("x"));
		model_init_submodel.SA.y=atof(element->Attribute("y"));
		model_init_submodel.SA.z=atof(element->Attribute("z"));
		}
	if ((tmp_string=element->Value())=="mAM")
		{
		model_init_submodel.AmbientMaterial[0]=atof(element->Attribute("r"));
		model_init_submodel.AmbientMaterial[1]=atof(element->Attribute("g"));
		model_init_submodel.AmbientMaterial[2]=atof(element->Attribute("b"));
		model_init_submodel.AmbientMaterial[3]=atof(element->Attribute("a"));
		}
	if ((tmp_string=element->Value())=="mDM")
		{
		model_init_submodel.DiffuseMaterial[0]=atof(element->Attribute("r"));
		model_init_submodel.DiffuseMaterial[1]=atof(element->Attribute("g"));
		model_init_submodel.DiffuseMaterial[2]=atof(element->Attribute("b"));
		model_init_submodel.DiffuseMaterial[3]=atof(element->Attribute("a"));
		}
	if ((tmp_string=element->Value())=="mSM")
		{
		model_init_submodel.SpecularMaterial[0]=atof(element->Attribute("r"));
		model_init_submodel.SpecularMaterial[1]=atof(element->Attribute("g"));
		model_init_submodel.SpecularMaterial[2]=atof(element->Attribute("b"));
		model_init_submodel.SpecularMaterial[3]=atof(element->Attribute("a"));
		}
	if ((tmp_string=element->Value())=="mEM")
		{
		model_init_submodel.EmissionMaterial[0]=atof(element->Attribute("r"));
		model_init_submodel.EmissionMaterial[1]=atof(element->Attribute("g"));
		model_init_submodel.EmissionMaterial[2]=atof(element->Attribute("b"));
		model_init_submodel.EmissionMaterial[3]=atof(element->Attribute("a"));
		}
	if ((tmp_string=element->Value())=="mShinM")
		{
		model_init_submodel.ShininessMaterial=atoi(element->Attribute("i"));
		}
	if ((tmp_string=element->Value())=="ScaleRadius")
		{
		rtm=atof(element->Attribute("SR"));
		}
	if ((tmp_string=element->Value())=="file") 
		{
		char *ch=(char *)(element->Attribute("path"));
		string t1=strrchr(ch,'.'), path = element->Attribute("path");
		string full_path = PKGDATADIR+path;
		if(t1==".3ds"||t1==".3DS") 
			{
			model_init_submodel.inmodel3ds=new glm3ds;
			model_init_submodel.inmodel3ds->LoadModel(full_path,rtm);
			model_init_model.Radius=model_init_submodel.inmodel3ds->GetRadius(rtm);
			model_init_submodel.inmodel3ds->DeleteObj();
			}
		}
	if ((tmp_string=element->Value())=="texture") 
		{
		model_init_submodel.intexture=GetTFName(element->Attribute("name"),
							model_init_texturelist);
		}
	}
}

void miLoadLodModel(TiXmlElement *element)
{
string tmp_string;
for(element = element->FirstChildElement();
	element;
	element = element->NextSiblingElement())
	{
	if ((tmp_string=element->Value())=="subm")
		{
		miLoadSubModel(element);
		model_init_submodellist.push_front(model_init_submodel);
		}
	}
}

void miLoadModel(TiXmlElement *element)
{
string tmp_string;
for(element = element->FirstChildElement();
	element;
	element = element->NextSiblingElement())
	{
	if ((tmp_string=element->Value())=="gCD")
		{
		model_init_model.CD.x=atof(element->Attribute("x"));
		model_init_model.CD.y=atof(element->Attribute("y"));
		model_init_model.CD.z=atof(element->Attribute("z"));
		}
	if ((tmp_string=element->Value())=="gRT")
		{
		model_init_model.RT.x=atof(element->Attribute("x"));
		model_init_model.RT.y=atof(element->Attribute("y"));
		model_init_model.RT.z=atof(element->Attribute("z"));
		}
	if ((tmp_string=element->Value())=="gSA")
		{
		model_init_model.SA.x=atof(element->Attribute("x"));
		model_init_model.SA.y=atof(element->Attribute("y"));
		model_init_model.SA.z=atof(element->Attribute("z"));
		}
	if ((tmp_string=element->Value())=="lod")
		{
		model_init_submodellist.clear();
		miLoadLodModel(element);
		model_init_lodmodellist.push_front(model_init_submodellist);
		}
	}
}

void miLoadModelXML(TiXmlElement *element, bool inc = false)
{
string tmp_string;

for(;
	element;
	element = element->NextSiblingElement())
	{
	if ((tmp_string=element->Value()) == "model")
		{
		model_init_model.WriteName(element->Attribute("name"));
		model_init_lodmodellist.clear();
		miLoadModel(element);
		model_init_model.WriteModelList(model_init_lodmodellist);
		model_init_modellist->push_front(model_init_model);
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
		miLoadModelXML(temp_doc.FirstChildElement());
		continue;
		}
	}

}

void ModelInit(string file, ModelList *inlist, TextureList *inlist2)
{
TiXmlDocument doc;
if(doc.LoadFile(file.c_str()) == false)
	{
	std::cout<< doc.ErrorDesc()<<std::endl;
	exit(0);
	}
model_init_modellist = inlist;
model_init_texturelist = inlist2;
miLoadModelXML(doc.FirstChildElement());
}
