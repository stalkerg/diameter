#include <iostream>
#include <fstream>
#ifdef __unix__
#else
#include <io.h>
#endif

#include "./xml/tinyxml.h"
#include "../uni.h"

#include <config.h>

void init_option()
{
int b=0;
string temp;
TiXmlDocument doc;

std::cout<<"PKGDATADIR:"<<PKGDATADIR<<std::endl;
option.path_to_data = PKGDATADIR;

#ifdef __unix__
std::string conffile = std::string(getenv("HOME")) + "/.diameter.xml";
#else
std::string conffile = "./diameter.xml";
#endif

std::cout<<"conf_file:"<<conffile<<std::endl;

if (access(conffile.c_str(), F_OK) != 0)
	{
	std::fstream new_file(conffile.c_str(), ios_base::trunc|ios_base::out);
	new_file<<
"<options>\n \
\t<window x=\"800\" y=\"600\" bit=\"32\"/>\n \
\t<fullscreen yes=\"0\"/>\n \
\t<sound yes=\"1\" buffer=\"2048\"/>\n \
\t<language text=\"eng\"/>\n \
\t<input mouse=\"1\"/>\n \
\t<texture_manager live=\"60000\" loop_pause=\"20000\" iteration_pause=\"500\"/>\n \
\t<model_manager live=\"60000\" loop_pause=\"20000\" iteration_pause=\"500\"/>\n \
</options>";
	new_file.close();
	}

option.path_to_conffile = conffile;

if(doc.LoadFile(conffile.c_str()) == false)
	{
	cout<<conffile<<":"<< doc.ErrorDesc()<<endl;
	exit(0);
	}
TiXmlElement *element=doc.FirstChildElement();

while (element)
	{
	while (true)
		{
		if(b==1)
			{
			if ((temp=element->Value())=="window")
				{
				option.winW=atoi(element->Attribute("x"));
				option.winH=atoi(element->Attribute("y"));
				option.bit=atoi(element->Attribute("bit"));
				}
			if ((temp=element->Value())=="fullscreen")
				{
				option.fs=atoi(element->Attribute("yes"));
				}
			if ((temp=element->Value())=="sound")
				{
				option.sound=atoi(element->Attribute("yes"));
				option.snd_buffer=atoi(element->Attribute("buffer"));
				}
			if ((temp=element->Value())=="language")
				{
				option.language=element->Attribute("text");
				}
			if ((temp=element->Value())=="input")
				{
				option.input=atoi(element->Attribute("mouse"));
				}
			if ((temp=element->Value())=="texture_manager")
				{
				option.tm_live_texture=atoi(element->Attribute("live"));
				option.tm_loop_pause=atoi(element->Attribute("loop_pause"));
				option.tm_iteration_pause=atoi(element->Attribute("iteration_pause"));
				}
			if ((temp=element->Value())=="model_manager")
				{
				option.mm_live_model=atoi(element->Attribute("live"));
				option.mm_loop_pause=atoi(element->Attribute("loop_pause"));
				option.mm_iteration_pause=atoi(element->Attribute("iteration_pause"));
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






