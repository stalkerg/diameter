#ifndef UI2D_GUI
#define UI2D_GUI

#include <guichan.hpp>
#include <guichan/sdl.hpp>
#include <guichan/opengl.hpp>
#include <guichan/opengl/openglsdlimageloader.hpp>
#include <GL/gl.h>
#include <sstream>

#ifdef _POSIX_C_SOURCE	// shut up pyconfig.h complaints
#undef _POSIX_C_SOURCE
#endif
#include <Python.h>

#include "../../uni.h"
#include "image_button.h"
#include "fonts_button.h"
#include "text_checkbox.h"
#include "icon_ext.h"
#include "../../res/xml/tinyxml.h"

class DGUI
{
gcn::SDLInput* input;
gcn::OpenGLGraphics* graphics;
gcn::OpenGLSDLImageLoader* imageLoader;
gcn::SDLImageLoader* hostImageLoader;

/*
 * Guichan stuff we need
 */
gcn::Gui* gui;            // A Gui object - binds it all together
gcn::ImageFont* font;     // A font
gcn::ImageFont* font2;
gcn::ImageFont *font_blue_en, *font_gold_en, *font_gold_glow_en;

gcn::Container* top;                 // A top container
gcn::Container* play_container;
gcn::Container* play_menu_container;
gcn::Container* credits_container;
gcn::Container* option_container;
gcn::Container* popup_container;

gcn::Icon *diameter_icon;
gcn::IconExt *face_icon;
gcn::Image *face_image;
gcn::Label* cord_label;
gcn::Label* param_label;
gcn::Label* fps_label;
gcn::Icon* icon;  
gcn::Label* credits_label_idea;
gcn::Label* credits_label_programming;
gcn::Label* credits_label_3dmodeling;
gcn::Label* credits_label_art;
gcn::Label* credits_label_music;
gcn::FontsButton *b_StartGame, *b_StartMission;
gcn::FontsButton *b_ExitGame;
gcn::FontsButton *b_CMainMenu;
gcn::FontsButton *b_Credits;
gcn::FontsButton *b_Resume;
gcn::FontsButton *b_PMainMenu;
gcn::FontsButton *b_Option, *b_AppliedOptions;
gcn::DImageButton *b_popup_next, *b_popup_prev, *b_popup_ok;

gcn::Label* option_label_resolution;
gcn::Label* option_label_resolution_x;
gcn::TextField  *option_textfield_resolution_x;
gcn::TextField  *option_textfield_resolution_y;
gcn::Label* option_label_fullscreen;
gcn::Label* option_label_music;
gcn::Label* option_label_mouse;
gcn::Label* option_label_applied;
gcn::Label* option_label_applied2;
gcn::TextCheckBox *option_checkbox_fullscreen;
gcn::TextCheckBox *option_checkbox_mouse;
gcn::TextCheckBox *option_checkbox_music;

gcn::Window *popup_window;
gcn::TextBox *popup_textbox;

std::string s_popup_next, s_popup_prev, s_popup_ok;

Options option;
bool NewGame;
bool Play;
bool Done;
bool FirstGame;
bool *Game;
bool Mouse;
std::string FileWorld;
void CheckEvent();
void AppliedOptions();


public:
DGUI()
	{
	NewGame=false;
	Done=false;
	Play=false;
	FirstGame=true;
	Mouse=true;
	}
bool GetBMouse(){return Mouse;}
bool GetBPlay(){return Play;}
bool GetBDone(){return Done;}
bool GetBNewGame(){return NewGame;}
std::string GetSFileWorld(){return FileWorld;}
void SetBNewGame(bool in){NewGame=in;}
void SetGame(bool *in){Game=in;}
void SetMenu();
void SetPlayMenu();
void SetPopupVisible(bool in);
void SetPopupSize(int x, int y);
void SetPopupPosition(int x, int y);
void SetPopupText(std::string text);
void SetPopupCaretRow(int row);
void SetPopupEnableButtons(bool prev, bool next, bool ok);
void SetPopupScriptNext(std::string file);
void SetPopupScriptPrev(std::string file);
void SetPopupScriptOk(std::string file);
void SetPopupFaceImage(std::string file);

void PauseGame(bool in);

void Init(Options in_option);
void InitMainWidgets();
void Draw();
void FullDraw();

void SetCordLabel(std::string in_text);
void SetFpsLabel(std::string in_text);
void SetParamLabel(std::string in_text);
gcn::SDLInput *GetInput(){return input;}

void RunPythonOnce(std::string name);
};

namespace PyDGUI
{
void InitPythonDGUI(DGUI *gui);
}


#endif
