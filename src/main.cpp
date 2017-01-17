#include <Python.h>

#include <SDL.h>
#include <SDL_thread.h>
#include <SDL_mixer.h>
#include <GL/gl.h>
#include <GL/glu.h>


#include <string.h>
#include <string>

#ifdef _POSIX_C_SOURCE	// shut up pyconfig.h complaints
#undef _POSIX_C_SOURCE
#endif


#ifdef __unix__
#else
#include <windows.h>
#endif


#include "./uni.h"
Options option;
#include "./gra/mathlib.h"
#include "./res/texture.h"
#include "./gra/effect/cloud.h"
#include "./gra/effect/particle.h"
#include "./gra/effect/stars.h"
#include "./gra/model.h"
#include "./gra/model_init.h"

float ticklast=0, ticknow=0,ticknow2=0, ticklast2=0, reltime=0,
time_gone=0, tmpp=0, fROT=0, fps=0, bfps=0, z=0;
static float ITfiz=0.02;
#include "./wor/objects/gao.h"
#include "./wor/objects/pul.h"
#include "./wor/fiz.h"
#include "./snd/snd.h"
#include "./gra/2d/simple2d.h"
#include "./gra/2d/gui.h"

#include "./res/res.h"
#include "./res/loadworld.h"
#include "./wor/pylevel.h"

TextureList TTemp;
UTextureList TextureDelet;
UTextureList::iterator IteratorUTL;
Texture **THesh, *ttemp1;
Mix_Music *music;
DGUI MainGui;
int statetime=0, tknow=0, test=0;
int done;

Sprite *stemp, *back, *curs_center,
       *curs_ring, *curs_wliser, *curs_wplasma,
       *curs_wrocket;
Ef_Clouds testC;
Particle PartTest(30);
PlayFizState *CommonPF,NullPF;
vec2 **CamCor, curs_cord;
vec3 tempVec;
StarSystem ss1;
Stars Starss1;
ModelList gmlist;
UModelList ModelDelet;
UModelList::iterator IteratorUML;

SpriteList gslist;
char StringTemp[20],StringTemp2[100];

WorldObjects *World1;
int nWorld=0,ShipKill=0,AttackShip=0;
Object *CamObject,*PlayerObject;
GaoObject TObject;
AI *CamAI,*TempAI,*AddObject=NULL,*TempAI2=NULL;
WeaponSM PSTemp;

ObjectList::iterator object_iterator_1, object_iterator_2;
ObjectList ColPhysList, TempItList;
DecorationObjectList::iterator decoraton_iterator;
bool CalcSim=false;
bool Thread=true;
bool PlayerStart=false;
bool Game=false;

//Lights settings
GLfloat light_ambient[]= { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat light_diffuse[]= { 1.0f, 0.4f, 1.0f, 0.0f };
GLfloat light_specular[]= { 1.0f, 1.0f, 1.0f, 0.0f };
GLfloat light_position[]= { -70.0f, 7.0f, 0.0f, 1.0f };

GLfloat light_ambient1[]= { 0.3f, 0.3f, 0.3f, 1.0f };
GLfloat light_diffuse1[]= { 1.0f, 0.8f, 1.0f, 1.0f };
GLfloat light_position1[]= { 0.0f, 0.0f, 0.0f, 1.0f };

GLfloat light_spot_dir1[]= { 0.0f, 0.0f, -1.0f};
GLfloat light_spot_cut1[]= { 90.0f };
GLfloat light_spot_exp1[]= { 64.0f };

//Materials settings
GLfloat mat_ambient[]= { 0.2f, 0.2f, 0.2f, 1.0f };
GLfloat mat_diffuse[]= { 0.2f, 0.2f, 0.2f, 1.0f };
GLfloat mat_specular[]= { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat mat_shininess[]= { 1.0f };

void Render() {
	//Fizic	
	if(Game) {
		while(time_gone>=ITfiz) {
			PySublimatObjects::SetPythonSublimatObjects(World1->GetSub(nWorld));
			if (World1->GetSub(nWorld)->GetPyNextTime()<SDL_GetTicks()) {
				World1->GetSub(nWorld)->SetPyNextTime(SDL_GetTicks()+2000);
				World1->GetSub(nWorld)->RunPython();
			}
			Colizion(World1->GetSub(nWorld),*World1->GetSub(nWorld)->GetSO());
			for(object_iterator_1=World1->GetSub(nWorld)->GetSO()->begin();
			    object_iterator_1!=World1->GetSub(nWorld)->GetSO()->end();
			    ++object_iterator_1)
				{
				object_iterator_2=object_iterator_1;
				--object_iterator_2;
				if(object_iterator_1->in->Calc()==1)
					object_iterator_1=object_iterator_2;
				}
			time_gone-=ITfiz;
			ticklast2=ticknow2;
			ticknow2=SDL_GetTicks();
			time_gone+=(ticknow2-ticklast2)/1000.0;
		}
	} else {
		ticklast2=ticknow2;
		ticknow2=SDL_GetTicks();
	}
	//Draw
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glColor3f(1.0,1.0,1.0);
	glEnable(GL_POINT_SMOOTH);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0);
	glEnable(GL_DEPTH_TEST);

	// 3D Zone___start____________
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective (60, (float)option.winW / option.winH, 0.1, 10000);
	//Lights initialization and activation
	glLightfv (GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv (GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv (GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv (GL_LIGHT0, GL_POSITION, light_position);
	glLightfv (GL_LIGHT0, GL_SPOT_CUTOFF, light_spot_cut1);
	//glLightfv (GL_LIGHT0, GL_SPOT_DIRECTION, light_spot_dir1);
	glLightfv (GL_LIGHT0, GL_SPOT_DIRECTION, light_spot_exp1);
	glLightf (GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0);
	glLightf (GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.05);
	//glEnable (GL_LIGHT0);
	glLightfv (GL_LIGHT1, GL_AMBIENT, light_ambient1);
	glLightfv (GL_LIGHT1, GL_DIFFUSE, light_diffuse1);
	glLightfv (GL_LIGHT1, GL_SPECULAR, light_specular);
	glLightfv (GL_LIGHT1, GL_POSITION, light_position1);

	glEnable (GL_LIGHT1);
	//glShadeModel(GL_SMOOTH);

	glMatrixMode(GL_MODELVIEW);
	// 3D Zone___body____________

	glEnable(GL_ALPHA_TEST);
	glEnable(GL_DEPTH_TEST);
	glDisable (GL_LIGHTING);
	glPushMatrix();
		glRotatef(12,-1,0,0);
		glTranslatef(-(*CamCor)->x,-(*CamCor)->y,-10+z);
		glPushMatrix();
			glRotatef(fROT,0,0,1);
			
			/*glPushMatrix();
				glColor4f(1.0,1.0,1.0,1.0);
				glTranslatef(2,0,-30);
				back->Draw(0,90);
			glPopMatrix();
			glPushMatrix();
				glColor4f(1.0,1.0,1.0,0.5);
				glTranslatef(2,0,-12);
				back->Draw(0,90);
				glColor4f(1.0,1.0,1.0,1.0);
			glPopMatrix();*/
			for (decoraton_iterator=World1->GetSub(nWorld)->GetDecorationList()->begin();
			     decoraton_iterator!=World1->GetSub(nWorld)->GetDecorationList()->end();
			     ++decoraton_iterator)
				decoraton_iterator->Draw();
			
			glDepthMask (GL_FALSE);
			glEnable (GL_BLEND);
			glEnable(GL_COLOR_MATERIAL);
			glPushMatrix();
				ss1.Draw();
			glPopMatrix();
			glDepthMask (GL_TRUE);
		glPopMatrix();
		//testC.Draw();
	glPopMatrix();
	glDisable (GL_BLEND);
	glPushMatrix();
		glTranslatef(0,0,z-18);
		glRotatef(12,-1.0,0,0);
		glPushMatrix();
			glRotatef(fROT,0,0,1);
			CamAI=(AI*)CamObject;
			
			glTranslatef(-(*CamCor)->x,-(*CamCor)->y,0);
			/*
				1 2 3
				4 5 6
				7 8 9
			*/
				
			ObjectList DrawList=GetViewObjectList(World1->GetSub(nWorld)->GetSeO(),CamAI->GetnSector(),
			World1->GetSub(nWorld)->Get4Sector(World1->GetSub(nWorld)->GetSectorN(**CamCor),(*CamCor)->x,(*CamCor)->y),
			World1->GetSub(nWorld)->GetlenghS(), World1->GetSub(nWorld)->GetnSectors());
			glEnable (GL_LIGHTING);
			
			for (object_iterator_1=DrawList.begin();
			     object_iterator_1!=DrawList.end();
			     ++object_iterator_1)
				{
				object_iterator_1->in->Draw();
				}
			glPopMatrix();
	glPopMatrix();
	glDisable (GL_LIGHTING);

	// 3D Zone___end____________
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (option.winW <= option.winH)
		glOrtho (-10.0, 10.0, -10.0 * (GLfloat) option.winH / (GLfloat) option.winW,
		          10.0 * (GLfloat) option.winH / (GLfloat) option.winW, -100.0, 100.0);
	else
		glOrtho (-10.0 * (GLfloat) option.winW / (GLfloat) option.winH,
		          10.0 * (GLfloat) option.winW / (GLfloat) option.winH,
			 -10.0, 10.0, -100.0, 100.0);

	glMatrixMode(GL_MODELVIEW);
	// 2D Gra and UI
	DrawRadar(World1, PlayerObject, nWorld);

	MainGui.Draw();

	MainGui.SetFpsLabel(StringTemp);
	sprintf(StringTemp2, "x:%f y:%f r:%i", (*CamCor)->x, (*CamCor)->y, World1->GetSub(nWorld)->GetSectorN(**CamCor));
	MainGui.SetCordLabel(StringTemp2);
	if(PlayerObject!=NULL)
		sprintf(StringTemp2,
				"+Health:%i #Shield:%i -GunEnergy:%i  ShipKill:%i  AttackShip:%i",
				(int)((AI*)PlayerObject)->GetParamsHS()->Health,
				(int)((AI*)PlayerObject)->GetParamsHS()->Shield,
				(int)((AI*)PlayerObject)->GetParamsHS()->GunEnergy,
				((AI*)PlayerObject)->GetFrag(),
				AttackShip-((AI*)PlayerObject)->GetFrag()
		);
	MainGui.SetParamLabel(StringTemp2);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, (double)option.winW, (double)option.winH, 0.0, -100.0, 100.0);

	/* Enable Blending */
	glEnable (GL_BLEND);
	/* Type Of Blending To Perform */
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_ALPHA_TEST);
	glColor4f(1,1,1,1.0);
	curs_center->Draw(curs_cord);
	glPushMatrix();
	glTranslatef(0,0,1);
	if(PlayerObject!=NULL) {
		float color_ring=((AI*) PlayerObject)->GetParamsHS()->GunEnergy/
						 ((AI*) PlayerObject)->GetParamsHS()->MaxGunEnergy;
		glColor4f(color_ring, color_ring,color_ring, 1);
		curs_ring->Draw(curs_cord,180);
	}
	glColor4f(1, 1, 1, 1.0);
	glTranslatef(0, 0, 3);
	if(PlayerObject != NULL) {
		switch(((AI*) PlayerObject)->GetTypeGun()) {
			case 1: curs_wplasma->Draw(curs_cord,180); break;
			case 2: curs_wliser->Draw(curs_cord,180); break;
			case 3: curs_wrocket->Draw(curs_cord,180); break;
		};
	}
	glPopMatrix();
	glPopMatrix();
	SDL_GL_SwapBuffers();

	if(PlayerStart == false && CalcSim && PlayerObject != NULL) {
		CalcSim = false;	
		((AI*)PlayerObject)->AddObjectToSO(AddObject);
	}

	ticklast = ticknow;
	ticknow = SDL_GetTicks();
	ticknow2 = ticknow;
	reltime = (ticknow - ticklast) / 1000.0;
	if(Game) time_gone+=reltime;
	bfps+=(ticknow-ticklast);
	fps++;
	if (bfps>1000) {
		bfps=0;
		cout<<"FPS:"<<fps<<"\tObjects:"<<World1->GetSub(0)->GetSO()->size()<<endl;
		sprintf (StringTemp, "FPS:%i", (int)fps);
		fps=0;
		if(TextureDelet.size() != 0) {
			for(IteratorUTL=TextureDelet.begin(); IteratorUTL != TextureDelet.end(); ++IteratorUTL)
				(*IteratorUTL)->Unable();
			TextureDelet.clear();
		}
		if(ModelDelet.size()!=0) {
			for(IteratorUML=ModelDelet.begin(); IteratorUML != ModelDelet.end(); ++IteratorUML)
				(*IteratorUML)->Unable();
			ModelDelet.clear();
		}
	}

	if(PlayerStart&&CalcSim) {
		cout<<"PlayerC"<<endl;
		PlayerStart=false;
		CalcSim=false;
		World1->DeleteWorld();
		delete World1;
		World1=LoadWorld(MainGui.GetSFileWorld(),&gslist,&gmlist, &ticknow, &ITfiz, CamCor, &CamObject, &PlayerObject);
		WorldInit(World1);
		((GaoObject*)PlayerObject)->WriteWeaponSM(PSTemp);
		*CamCor=((AI*)CamObject)->GetUCord();
		ss1.playercord=((AI*)CamObject)->GetUCord();
		CommonPF=((AI*)PlayerObject)->GetPFS();
		cout<<"End"<<endl;
	}

	if(PlayerObject!=NULL&&((AI*)PlayerObject)->GetStepKill()) {
		cout<<"You Die!!!"<<endl;
		PlayerStart=true;
		if(MainGui.GetBNewGame()) {
			CamObject=((AI*)&TObject);
			MainGui.SetBNewGame(false);
			CalcSim=true;
		} else
			CamObject=((AI*)PlayerObject)->GetLastAttackReObject();
		PlayerObject=NULL;
		*CamCor=((AI*)CamObject)->GetUCord();
		ss1.playercord=((AI*)CamObject)->GetUCord();
		CommonPF=&NullPF;
		ShipKill=0;
		AttackShip=0;
	}
		
}

void TexInit()
{
//glEnable(GL_TEXTURE);
glEnable(GL_TEXTURE_2D);
//glEnable(GL_COLOR_MATERIAL);
std::string temp_string = "texture/textures.xml";
LoadTextureList(PKGDATADIR+temp_string, &TTemp, &ticknow);
}

void ResInit()
{
vec2 temp_vec, temp_vec2, temp_vec3, temp_vec4;
vec3 vec3_temp;
color4 color4_temp;
CamCor=new vec2*;
World1=LoadWorld("world/arena.xml",&gslist,&gmlist, &ticknow, &ITfiz, CamCor, &CamObject, &PlayerObject);
curs_center=GetSFName("CursCenter", &gslist);
curs_ring=GetSFName("CursRing", &gslist);
curs_wliser=GetSFName("CursWLiser", &gslist);
curs_wplasma=GetSFName("CursWPlasma", &gslist);
curs_wrocket=GetSFName("CursWRocket", &gslist);
back=GetSFName("sp001", &gslist);

PSTemp.PulsGun=GetSFName("sp008", &gslist);
PSTemp.PulsGunEx=GetSFName("sp011", &gslist);
PSTemp.Liser=GetSFName("sp010", &gslist);
PSTemp.LiserEx=GetSFName("sp013", &gslist);
PSTemp.Rocket1=GetMFName("Rocket1", &gmlist);
PSTemp.gslist=&gslist;
PSTemp.gmlist=&gmlist;

PyDGUI::InitPythonDGUI(&MainGui);
PySublimatObjects::InitPythonSublimatObjects(&PlayerStart, &CalcSim);
PyParticle::InitPythonParticle(&gslist, &ticknow, &ITfiz);
PyGaoObject::InitGaoObject(&gslist, &gmlist, &ticknow,
			   &ITfiz, PSTemp, CamCor);

WorldInit(World1);
((GaoObject*)PlayerObject)->WriteWeaponSM(PSTemp);
*CamCor=((AI*)CamObject)->GetUCord();
ss1.playercord=((AI*)CamObject)->GetUCord();
CommonPF=((AI*)PlayerObject)->GetPFS();
}


void InitGL()
{
#ifdef __unix__
#else
typedef void (APIENTRY * WGLSWAPINTERVALEXT) ( int ) ;
WGLSWAPINTERVALEXT wglSwapIntervalEXT =
(WGLSWAPINTERVALEXT) wglGetProcAddress( "wglSwapIntervalEXT" ) ;
if ( wglSwapIntervalEXT != 0 ) 
	{
	// Disable vertical synchronisation :
	wglSwapIntervalEXT( 0 ) ;
	}
#endif
glEnable(GL_POINT_SMOOTH);
glEnable (GL_BLEND);
glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
glEnable(GL_DEPTH_TEST);
glEnable(GL_ALPHA_TEST);
}

#ifdef __unix__
int main(int argc,char **argv)
#else
int WINAPI
WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nFunsterStil)
#endif
{
#ifdef __unix__
cout<<"Path:"<<argv[0]<<endl;
#endif
SDL_Thread *ThreadMTexture, *ThreadMModel;
init_option();

Py_Initialize ();
int optinsdl;
if (option.fs) optinsdl=SDL_OPENGL|SDL_DOUBLEBUF|SDL_FULLSCREEN; else
optinsdl=SDL_OPENGL|SDL_DOUBLEBUF; 
SDL_Init(SDL_INIT_VIDEO);
SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 6);
SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5); 
SDL_SetVideoMode(option.winW,option.winH,option.bit,optinsdl);
SDL_WM_SetCaption("Diameter 0.4.0","Diameter");
SDL_EnableUNICODE(1);
SDL_ShowCursor(SDL_DISABLE);



MainGui.Init(option);
MainGui.InitMainWidgets();
MainGui.SetGame(&Game);

TexInit();
string temp_string = "models/models.xml";
ModelInit(PKGDATADIR+temp_string,&gmlist,&TTemp);
temp_string = "sprites/sprites.xml";
SpriteInit(PKGDATADIR+temp_string,&gslist,&TTemp);



ResInit();

InitGL();
if(option.sound)
	InitSound(option.snd_buffer);

temp_string = "music/AmbDune.ogg";
temp_string = PKGDATADIR+temp_string;
music = Mix_LoadMUS (temp_string.c_str());
PlayMusic(music,-1);

DueTList TempDTlist;
TempDTlist.Main=&TTemp;
TempDTlist.Slave=&TextureDelet;
TempDTlist.in_options=&option;
ThreadMTexture = SDL_CreateThread(ManagerTexture, &TempDTlist);
if ( ThreadMTexture == NULL ) 
	{
	fprintf(stderr, "Unable to create thread: %s\n", SDL_GetError());
	return 0;
	}
DueMList TempDMlist;
TempDMlist.Main=&gmlist;
TempDMlist.Slave=&ModelDelet;
TempDMlist.in_options=&option;
ThreadMModel = SDL_CreateThread(ManagerModel, &TempDMlist);
if ( ThreadMModel == NULL ) 
	{
	fprintf(stderr, "Unable to create thread: %s\n", SDL_GetError());
	return 0;
	}

bool move=false;
bool atack=true;
bool kmove=false;

done = 0;

while(!done)
	{
	SDL_Event event;
	while(SDL_PollEvent(&event)) 
		{
		if(event.type==SDL_MOUSEMOTION)
			{
			curs_cord.x=event.motion.x;
			curs_cord.y=event.motion.y;
			}
		if(!Game)
			switch(event.type) 
				{
				case SDL_QUIT:
					done = 1;
					break;
				}
		if(Game)
		switch(event.type) 
			{
			case SDL_QUIT:
				done = 1;
				break;
			case SDL_KEYDOWN:
				if ( event.key.keysym.sym == SDLK_1 )
					{
					if(PlayerObject!=NULL)
						((AI*) PlayerObject)->WriteTypeGun(1); 
					}
				if ( event.key.keysym.sym == SDLK_2 )
					{
					if(PlayerObject!=NULL)
						((AI*) PlayerObject)->WriteTypeGun(2);
					}
				if ( event.key.keysym.sym == SDLK_3 )
					{
					//if(PlayerObject!=NULL)
					//	((AI*) PlayerObject)->WriteTypeGun(3);
					}
				if ( event.key.keysym.sym == SDLK_a
				  || event.key.keysym.sym == SDLK_LEFT)
					{
					CommonPF->calc_rot_left=true;
					}
				if ( event.key.keysym.sym == SDLK_d
				  || event.key.keysym.sym == SDLK_RIGHT)
					{
					CommonPF->calc_rot_right=true;
					}
				if ( event.key.keysym.sym == SDLK_g )
					{
					Game=true;
					}
				if ( event.key.keysym.sym == SDLK_RCTRL
				  || event.key.keysym.sym == SDLK_LCTRL )
					{
					atack=false;
					}
				if ( event.key.keysym.sym == SDLK_ESCAPE )
					{
					MainGui.SetMenu();
					Game=false;
					}
				if ( event.key.keysym.sym == SDLK_KP_PLUS )
					{
					z+=1;
					}
				if ( event.key.keysym.sym == SDLK_KP_MINUS )
					{
					z-=1;
					}
				if ( event.key.keysym.sym == SDLK_q )
					{
					CommonPF->streif=-1;
					}
				if ( event.key.keysym.sym == SDLK_e )
					{
					CommonPF->streif=1;
					}
				if (event.key.keysym.sym == SDLK_w ||
				    event.key.keysym.sym == SDLK_UP)
					{
					CommonPF->now_power=1.0;
					CommonPF->send_only_cord=false;
					kmove=true;
					}
				break;
				
			case SDL_KEYUP:
				if ( event.key.keysym.sym == SDLK_q )
					{
					CommonPF->streif=0;
					}
				if ( event.key.keysym.sym == SDLK_e )
					{
					CommonPF->streif=0;
					}
				if (event.key.keysym.sym == SDLK_w ||
				    event.key.keysym.sym == SDLK_UP)
					{
					kmove=false;
					}
				if ( event.key.keysym.sym == SDLK_a
				  || event.key.keysym.sym == SDLK_LEFT)
					{
					CommonPF->calc_rot_left=false;
					}
				if ( event.key.keysym.sym == SDLK_d
				  || event.key.keysym.sym == SDLK_RIGHT)
					{
					CommonPF->calc_rot_right=false;
					}
				if ( event.key.keysym.sym == SDLK_RCTRL
				  || event.key.keysym.sym == SDLK_LCTRL )
					{
					atack=true;
					}
				break;
			case SDL_MOUSEMOTION:
				{
				if(option.input && MainGui.GetBMouse())
					CommonPF->SetToRot(event.button.x,event.button.y,option);
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button==3 && option.input && MainGui.GetBMouse()) 
					{
					move=true;
					CommonPF->send_only_cord=false;
					CommonPF->SetToRot(event.button.x,event.button.y,option);
					}
				if (event.button.button==1 && option.input && MainGui.GetBMouse())
					{
					atack=false;
					}
				break;
			case SDL_MOUSEBUTTONUP:
				 if (event.button.button==3 && option.input && MainGui.GetBMouse())
					move=false;
				 if (event.button.button==1 && option.input && MainGui.GetBMouse())
					{
					atack=true;
					}
				break;
		}
	//std::cout<<"TD:"<<event.key.keysym.unicode<<std::endl;
	MainGui.GetInput()->pushInput(event);
	}
	
	if (move||kmove) 
		{
		if(CommonPF!=NULL)
			CommonPF->send_only_cord=false;
		}
	else 
		{
		if(CommonPF!=NULL)
			CommonPF->send_only_cord=true;
		}
	if(atack==false)
		{
		if(PlayerObject!=NULL)
			((AI*) PlayerObject)->Shoot();
		}
	Render();
	Game=MainGui.GetBPlay();
	if(PlayerObject!=NULL)
		((AI*) PlayerObject)->StepKill(MainGui.GetBNewGame());
	
	if(MainGui.GetBDone())
		break;
}
Thread=false;
//SDL_WaitThread(thread, NULL);
Py_Finalize ();
World1->DeleteWorld();
CloseSound(music);
SDL_Quit();
return 0;
}
