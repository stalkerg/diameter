#include "gui.h"

void DGUI::Init(Options in_option)
{
option=in_option;
imageLoader = new gcn::OpenGLSDLImageLoader();
//hostImageLoader = new gcn::SDLImageLoader();
// The OpenGL imageloader cant load images by itself, it needs
// a host imageloader. So we give it an SDL imageloader.
gcn::Image::setImageLoader(imageLoader);
graphics = new gcn::OpenGLGraphics();
// We need to tell OpenGL graphics how big the screen is.
graphics->setTargetPlane(in_option.winW, in_option.winH);
input = new gcn::SDLInput();

/*
 * Last but not least it's time to initialize and create the gui
 * with Guichan stuff.
 */
top = new gcn::Container();
// Set the dimension of the top container to match the screen.
top->setBaseColor(gcn::Color(0,0,0,100));
top->setDimension(gcn::Rectangle(0, 0, in_option.winW, in_option.winH));

play_container = new gcn::Container();
play_container->setDimension(gcn::Rectangle(0, 0, in_option.winW, in_option.winH));
play_container->setBaseColor(gcn::Color(0,0,0,0));
play_container->setOpaque(false);

credits_container = new gcn::Container();
credits_container->setDimension(gcn::Rectangle(0, 0, in_option.winW, in_option.winH));
credits_container->setBaseColor(gcn::Color(0,0,0,100));

option_container = new gcn::Container();
option_container->setDimension(gcn::Rectangle(0, 0, in_option.winW, in_option.winH));
option_container->setBaseColor(gcn::Color(0,0,0,100));

popup_container = new gcn::Container();
popup_container->setDimension(gcn::Rectangle(0, 0, 200, 100));
popup_container->setBaseColor(gcn::Color(0,0,0,100));

play_menu_container = new gcn::Container();
play_menu_container->setDimension(gcn::Rectangle(0, 0, in_option.winW, in_option.winH));
play_menu_container->setBaseColor(gcn::Color(0,0,0,100));

gui = new gcn::Gui();
// Set gui to use the SDLGraphics object.
gui->setGraphics(graphics);
// Set gui to use the SDLInput object
gui->setInput(input);	
// Set the top container
gui->setTop(top);
// Load the image font.

std::string temp_string = "fonts/rpgfont_thinner_noshadow.png";
font = new gcn::ImageFont(PKGDATADIR+temp_string, " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,!?-+/():;%&`'*#");

temp_string = "fonts/font-blue-test.png";
font_blue_en = new gcn::ImageFont(PKGDATADIR+temp_string, " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,!?-+/():;%&`'\"");

temp_string = "fonts/font-gold-test.png";
font_gold_en = new gcn::ImageFont(PKGDATADIR+temp_string, " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,!?-+/():;%&`'\"");

// The global font is static and must be set.
gcn::Widget::setGlobalFont(font);
}

void DGUI::InitMainWidgets()
{
gcn::Image *TempImage1, *TempImage2;

b_StartGame = new gcn::FontsButton("Start Arena", font_gold_en, font_blue_en);
b_StartGame->setPosition(top->getWidth()/2-b_StartGame->getWidth()/2, top->getHeight()/2-50);

b_StartMission = new gcn::FontsButton("Start Mission", font_gold_en, font_blue_en);
b_StartMission->setPosition(top->getWidth()/2-b_StartGame->getWidth()/2, top->getHeight()/2);

b_Option = new gcn::FontsButton("Options", font_gold_en, font_blue_en);
b_Option->setPosition(top->getWidth()/2-b_Option->getWidth()/2, top->getHeight()/2+50);

b_Credits = new gcn::FontsButton("Credits", font_gold_en, font_blue_en);
b_Credits->setPosition(top->getWidth()/2-b_Credits->getWidth()/2, top->getHeight()/2+100);

b_ExitGame = new gcn::FontsButton("Exit Game", font_gold_en, font_blue_en);
b_ExitGame->setPosition(top->getWidth()/2-b_ExitGame->getWidth()/2, top->getHeight()/2+150);

std::string temp_string = "texture/gui/logo.png";
TempImage1 = gcn::Image::load(PKGDATADIR+temp_string);
diameter_icon = new gcn::Icon(TempImage1);
diameter_icon->setPosition(top->getWidth()/2-diameter_icon->getWidth()/2, top->getHeight()/2-150);

top->add(diameter_icon);
top->add(b_StartGame);
top->add(b_StartMission);
top->add(b_Option);
top->add(b_Credits);
top->add(b_ExitGame);


cord_label = new gcn::Label();
cord_label->setPosition(20, 5);
cord_label->setFont(font);

fps_label = new gcn::Label();
fps_label->setPosition(top->getWidth()-80, 5);
fps_label->setFont(font);

param_label = new gcn::Label();
param_label->setPosition(20, top->getHeight()-25);
param_label->setFont(font);
play_container->add(cord_label);
play_container->add(fps_label);
play_container->add(param_label);

credits_label_idea = new gcn::Label("Idea: stalkerg, Ranger");
credits_label_idea->setFont(font_blue_en);
credits_label_idea->adjustSize();
credits_label_idea->setPosition(top->getWidth()/2-credits_label_idea->getWidth()/2-100,
				top->getHeight()/2-150);

credits_label_programming = new gcn::Label("Programming: stalkerg");
credits_label_programming->setPosition(top->getWidth()/2-credits_label_idea->getWidth()/2-100,
				       top->getHeight()/2-100);
credits_label_programming->setFont(font_blue_en);
credits_label_programming->adjustSize();

credits_label_3dmodeling = new gcn::Label("3D Modeling: Genma");
credits_label_3dmodeling->setPosition(top->getWidth()/2-credits_label_idea->getWidth()/2-100,
				      top->getHeight()/2-50);
credits_label_3dmodeling->setFont(font_blue_en);
credits_label_3dmodeling->adjustSize();

credits_label_art = new gcn::Label("Art: Ranger, stalkerg, evil-bc");
credits_label_art->setPosition(top->getWidth()/2-credits_label_idea->getWidth()/2-100,
			       top->getHeight()/2);
credits_label_art->setFont(font_blue_en);
credits_label_art->adjustSize();

credits_label_music = new gcn::Label("Music: stalkerg");
credits_label_music->setPosition(top->getWidth()/2-credits_label_idea->getWidth()/2-100,
			         top->getHeight()/2+50);
credits_label_music->setFont(font_blue_en);
credits_label_music->adjustSize();

b_CMainMenu = new gcn::FontsButton("Return", font_gold_en, font_blue_en);
b_CMainMenu->setPosition(top->getWidth()/2-b_CMainMenu->getWidth()/2, top->getHeight()/2+150);

credits_container->add(credits_label_idea);
credits_container->add(credits_label_programming);
credits_container->add(credits_label_3dmodeling);
credits_container->add(credits_label_art);
credits_container->add(credits_label_music);
credits_container->add(b_CMainMenu);

b_AppliedOptions = new gcn::FontsButton("Apply", font_gold_en, font_blue_en);
b_AppliedOptions->setPosition(top->getWidth()/2-b_CMainMenu->getWidth()/2+250, top->getHeight()/2+150);

b_Resume = new gcn::FontsButton("Return", font_gold_en, font_blue_en);
b_Resume->setPosition(top->getWidth()/2-b_Resume->getWidth()/2, top->getHeight()/2-100);

b_PMainMenu = new gcn::FontsButton("Main Menu", font_gold_en, font_blue_en);
b_PMainMenu->setPosition(top->getWidth()/2-b_PMainMenu->getWidth()/2, top->getHeight()/2-50);
play_menu_container->add(b_Resume);
play_menu_container->add(b_PMainMenu);

option_label_resolution = new gcn::Label("Resolution:");
option_label_resolution->setPosition(top->getWidth()/2-option_label_resolution->getWidth()/2-300,
			         top->getHeight()/2-150);
option_label_resolution->setFont(font_blue_en);
option_label_resolution->adjustSize();
std::stringstream stream_temp;
std::string string_temp;
stream_temp<<top->getWidth();
stream_temp>>string_temp;
option_textfield_resolution_x = new gcn::TextField(string_temp+"  ");
option_textfield_resolution_x->setPosition(top->getWidth()/2-option_textfield_resolution_x->getWidth()/2,
			         top->getHeight()/2-150);
option_textfield_resolution_x->setFont(font_blue_en);
option_textfield_resolution_x->adjustSize();
option_textfield_resolution_x->setBackgroundColor(gcn::Color(0,0,0,0));
option_textfield_resolution_x->setForegroundColor(gcn::Color(0,0,255,255));

option_label_resolution_x = new gcn::Label("X");
option_label_resolution_x->setPosition(option_textfield_resolution_x->getX()+option_textfield_resolution_x->getWidth()+5,
			         top->getHeight()/2-150);
option_label_resolution_x->setFont(font_blue_en);
option_label_resolution_x->adjustSize();

string_temp.clear();
stream_temp.clear();
stream_temp<<top->getHeight();
stream_temp>>string_temp;
option_textfield_resolution_y = new gcn::TextField(string_temp+"  ");
option_textfield_resolution_y->setPosition(top->getWidth()/2
				 -option_textfield_resolution_y->getWidth()/2+200,
			         top->getHeight()/2-150);
option_textfield_resolution_y->setFont(font_blue_en);
option_textfield_resolution_y->adjustSize();
option_textfield_resolution_y->setBackgroundColor(gcn::Color(0,0,0,0));
option_textfield_resolution_y->setForegroundColor(gcn::Color(0,0,255,255));

option_label_fullscreen = new gcn::Label("Fullscreen:");
option_label_fullscreen->setPosition(top->getWidth()/2-option_label_resolution->getWidth()/2-200,
			         top->getHeight()/2-80);
option_label_fullscreen->setFont(font_blue_en);
option_label_fullscreen->adjustSize();

option_label_mouse = new gcn::Label("Mouse:");
option_label_mouse->setPosition(top->getWidth()/2-option_label_resolution->getWidth()/2-200,
			         top->getHeight()/2-10);
option_label_mouse->setFont(font_blue_en);
option_label_mouse->adjustSize();

option_label_music = new gcn::Label("Music:");
option_label_music->setPosition(top->getWidth()/2-option_label_resolution->getWidth()/2-200,
			         top->getHeight()/2+60);
option_label_music->setFont(font_blue_en);
option_label_music->adjustSize();

option_label_applied = new gcn::Label("Settings will be applied after");
option_label_applied->setPosition(top->getWidth()/2-option_label_applied->getWidth()/2-250,
			         top->getHeight()/2-300);
option_label_applied->setFont(font_blue_en);
option_label_applied->adjustSize();

option_label_applied2 = new gcn::Label("the game is restarted.");
option_label_applied2->setPosition(top->getWidth()/2-option_label_applied2->getWidth()/2-200,
			         top->getHeight()/2-250);
option_label_applied2->setFont(font_blue_en);
option_label_applied2->adjustSize();

option_checkbox_fullscreen = new gcn::TextCheckBox(option.fs);
option_checkbox_fullscreen->setPosition(top->getWidth()/2
				 -option_label_resolution->getWidth()/2
				 +200,
			         top->getHeight()/2-80);
option_checkbox_fullscreen->setFont(font_blue_en);
option_checkbox_fullscreen->adjustSize();
option_checkbox_fullscreen->setBackgroundColor(gcn::Color(0,0,0,0));
option_checkbox_fullscreen->setForegroundColor(gcn::Color(0,0,0,0));

option_checkbox_mouse = new gcn::TextCheckBox(option.input);
option_checkbox_mouse->setPosition(top->getWidth()/2
				 -option_label_resolution->getWidth()/2
				 +200,
			         top->getHeight()/2-10);
option_checkbox_mouse->setFont(font_blue_en);
option_checkbox_mouse->adjustSize();
option_checkbox_mouse->setBackgroundColor(gcn::Color(0,0,0,0));
option_checkbox_mouse->setForegroundColor(gcn::Color(0,0,0,0));

option_checkbox_music = new gcn::TextCheckBox(option.sound);
option_checkbox_music->setPosition(top->getWidth()/2
				 -option_label_resolution->getWidth()/2
				 +200,
			         top->getHeight()/2+60);
option_checkbox_music->setFont(font_blue_en);
option_checkbox_music->adjustSize();
option_checkbox_music->setBackgroundColor(gcn::Color(0,0,0,0));
option_checkbox_music->setForegroundColor(gcn::Color(0,0,0,0));

popup_textbox = new gcn::TextBox("");
popup_textbox->setEditable(false);
popup_textbox->setOpaque(0);
popup_textbox->setFrameSize(0);
popup_container->add(popup_textbox);

temp_string = "texture/gui/other/back.png";
TempImage1 = gcn::Image::load(PKGDATADIR+temp_string);
temp_string = "texture/gui/other/back_b.png";
TempImage2 = gcn::Image::load(PKGDATADIR+temp_string);
b_popup_prev = new gcn::DImageButton(TempImage2, TempImage1);
b_popup_prev->setPosition(50, 50);
b_popup_prev->setEnabled(false);
b_popup_prev->setVisible(false);
popup_container->add(b_popup_prev);

temp_string = "texture/gui/other/forward.png";
TempImage1 = gcn::Image::load(PKGDATADIR+temp_string);
temp_string = "texture/gui/other/forward_b.png";
TempImage2 = gcn::Image::load(PKGDATADIR+temp_string);
b_popup_next = new gcn::DImageButton(TempImage2, TempImage1);
b_popup_next->setPosition(50, 50);
b_popup_next->setEnabled(false);
b_popup_next->setVisible(false);
popup_container->add(b_popup_next);

temp_string = "texture/gui/other/button_ok.png";
TempImage1 = gcn::Image::load(PKGDATADIR+temp_string);
temp_string = "texture/gui/other/button_ok_b.png";
TempImage2 = gcn::Image::load(PKGDATADIR+temp_string);
b_popup_ok = new gcn::DImageButton(TempImage2, TempImage1);
b_popup_ok->setPosition(50, 50);
b_popup_ok->setEnabled(false);
b_popup_ok->setVisible(false);
popup_container->add(b_popup_ok);

temp_string = "texture/gui/other/noface.png";
face_image = gcn::Image::load(PKGDATADIR+temp_string);
face_icon = new gcn::IconExt(face_image);
popup_container->add(face_icon);

popup_window = new gcn::Window("Popup");
popup_window->add(popup_container);
popup_window->setDimension(gcn::Rectangle(0, 0, 100, 100));
popup_window->setTitleBarHeight(0);
popup_window->resizeToContent();
popup_window->setVisible(false);
popup_window->setBaseColor(gcn::Color(0,0,200,150));

play_container->add(popup_window, 100, 100);

option_container->add(b_CMainMenu);
option_container->add(b_AppliedOptions);
option_container->add(option_label_resolution);
option_container->add(option_textfield_resolution_x);
option_container->add(option_label_resolution_x);
option_container->add(option_textfield_resolution_y);
option_container->add(option_label_fullscreen);
option_container->add(option_label_mouse);
option_container->add(option_label_music);
option_container->add(option_label_applied);
option_container->add(option_label_applied2);
option_container->add(option_checkbox_fullscreen);
option_container->add(option_checkbox_mouse);
option_container->add(option_checkbox_music);

}

void DGUI::Draw()
{
CheckEvent();
// Let the gui perform it's logic (like handle input)
gui->logic();
// Draw the gui
gui->draw();
}

void DGUI::FullDraw()
{
glClearColor(0, 0, 0, 0);
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
CheckEvent();
// Let the gui perform it's logic (like handle input)
gui->logic();
// Draw the gui
gui->draw();
SDL_GL_SwapBuffers();
}

void DGUI::SetMenu()
{
if(Play)
	{
	Play=false;
	gui->setTop(play_menu_container);
	}
}

void DGUI::SetPlayMenu()
{
if(Play)
	{
	Play=false;
	gui->setTop(top);
	}
}

void DGUI::CheckEvent()
{
if (b_StartGame->isClick())
	{
	FileWorld="world/arena.xml";
	Play=true;
	if(!FirstGame)
		NewGame=true;
	FirstGame=false;
	gui->setTop(play_container);
	}
if (b_StartMission->isClick())
	{
	FileWorld="world/test_mission1.xml";
	Play=true;
	NewGame=true;
	FirstGame=false;
	gui->setTop(play_container);
	}
if (b_ExitGame->isClick())
	Done=true;
if (b_Credits->isClick())
	gui->setTop(credits_container);
if (b_CMainMenu->isClick())
	gui->setTop(top);
if (b_PMainMenu->isClick())
	gui->setTop(top);
if (b_Option->isClick())
	gui->setTop(option_container);
if (b_Resume->isClick())
	{
	Play=true;
	gui->setTop(play_container);
	}
if (b_AppliedOptions->isClick())
	AppliedOptions();
if (b_popup_next->isClick())
	RunPythonOnce(s_popup_next);
if (b_popup_prev->isClick())
	RunPythonOnce(s_popup_prev);
if (b_popup_ok->isClick())
	RunPythonOnce(s_popup_ok);
}

void DGUI::SetCordLabel(std::string in_text)
{
cord_label->setCaption(in_text);
cord_label->adjustSize();
}

void DGUI::SetFpsLabel(std::string in_text)
{
fps_label->setCaption(in_text);
fps_label->adjustSize();
}

void DGUI::SetParamLabel(std::string in_text)
{
param_label->setCaption(in_text);
param_label->adjustSize();
}

void DGUI::AppliedOptions()
{
int b=0;
std::string temp;
TiXmlDocument doc;
if(doc.LoadFile(option.path_to_conffile.c_str()) == false)
	{
	std::cout<<option.path_to_conffile<<":"<< doc.ErrorDesc()<<std::endl;
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
				element->SetAttribute("x",
					option_textfield_resolution_x->getText().c_str());
				element->SetAttribute("y",
					option_textfield_resolution_y->getText().c_str());
				}
			if ((temp=element->Value())=="fullscreen")
				{
				if (option_checkbox_fullscreen->isSelected())
					element->SetAttribute("yes","1");
				else
					element->SetAttribute("yes","0");
				}
			if ((temp=element->Value())=="sound")
				{
				if (option_checkbox_music->isSelected())
					element->SetAttribute("yes","1");
				else
					element->SetAttribute("yes","0");
				}
			if ((temp=element->Value())=="input")
				{
				if (option_checkbox_mouse->isSelected())
					element->SetAttribute("mouse","1");
				else
					element->SetAttribute("mouse","0");
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
if(doc.SaveFile() == false)
	{
	std::cout<<doc.ErrorDesc()<<std::endl;
	exit(0);
	}
}

void DGUI::PauseGame(bool in)
{
if(in&&Play)
	{
	Play=false;
	*Game=false;
	}
if(!in&&!Play)
	{
	Play=true;
	*Game=true;
	}
}

void DGUI::SetPopupVisible(bool in)
{
popup_window->setVisible(in);
Mouse=!in;
}

void DGUI::SetPopupSize(int x, int y)
{
popup_window->setDimension(gcn::Rectangle(0, 0, x, y));
popup_container->setDimension(gcn::Rectangle(0, 0, x, y));
b_popup_prev->setPosition(15, y-45);
b_popup_next->setPosition(60, y-45);
b_popup_ok->setPosition(x-45, y-45);
face_icon->setPosition(x-70, 5);
}

void DGUI::SetPopupPosition(int x, int y)
{
popup_window->setPosition(x, y);
}

void DGUI::SetPopupText(std::string text)
{
popup_textbox->setText(text);
}

void DGUI::SetPopupCaretRow(int row)
{
popup_textbox->setCaretRow(row);
}

void DGUI::SetPopupEnableButtons(bool prev, bool next, bool ok)
{
b_popup_ok->setEnabled(ok);
b_popup_ok->setVisible(ok);
b_popup_prev->setEnabled(prev);
b_popup_prev->setVisible(prev);
b_popup_next->setEnabled(next);
b_popup_next->setVisible(next);
}

void DGUI::SetPopupScriptNext(std::string file)
{
s_popup_next = PKGDATADIR + file;
}

void DGUI::SetPopupScriptPrev(std::string file)
{
s_popup_prev = PKGDATADIR + file;
}

void DGUI::SetPopupScriptOk(std::string file)
{
s_popup_ok = PKGDATADIR + file;
}

void DGUI::SetPopupFaceImage(std::string file)
{
glGetError();
face_icon->setImage(gcn::Image::load(PKGDATADIR+file));
}

void DGUI::RunPythonOnce(std::string name)
{
if (name.size()!=0)
	{
	FILE *file;
	file = fopen(name.c_str(), "r");
	if (file==NULL)
		{
		std::cout<<"Error: file is null"<<std::endl;
		std::cout<<"name:"<<name<<std::endl;
		exit(0);
		}
	PyRun_AnyFile(file, name.c_str());
	if (file!=NULL)
		fclose(file);
	}
else
	std::cout<<"DGUI::RunPythonOnce: file string is null"<<std::endl;
}

namespace PyDGUI
{

static DGUI *u_gui;

PyObject *PySetPlayMenu(PyObject *self, PyObject *args)
	{
	u_gui->SetPlayMenu();
	return Py_None;
	}

PyObject *PyPauseGame(PyObject *self, PyObject *args)
	{
	bool pause;
	if (!PyArg_ParseTuple (args, "b", &pause))
		{
		PyErr_Print ();
		PyErr_Clear ();
		return Py_None;
		}
	u_gui->PauseGame(pause);
	return Py_None;
	}

PyObject *PySetPopupVisible(PyObject *self, PyObject *args)
	{
	bool visible;
	if (!PyArg_ParseTuple (args, "b", &visible))
		{
		PyErr_Print ();
		PyErr_Clear ();
		return Py_None;
		}
	u_gui->SetPopupVisible(visible);
	return Py_None;
	}

PyObject *PySetPopupCaretRow(PyObject *self, PyObject *args)
	{
	int row;
	if (!PyArg_ParseTuple (args, "i", &row))
		{
		PyErr_Print ();
		PyErr_Clear ();
		return Py_None;
		}
	u_gui->SetPopupCaretRow(row);
	return Py_None;
	}

PyObject *PySetPopupSize(PyObject *self, PyObject *args)
	{
	int size_x, size_y;
	if (!PyArg_ParseTuple (args, "ii", &size_x, &size_y))
		{
		PyErr_Print ();
		PyErr_Clear ();
		return Py_None;
		}
	u_gui->SetPopupSize(size_x, size_y);
	return Py_None;
	}

PyObject *PySetPopupPosition(PyObject *self, PyObject *args)
	{
	int cord_x, cord_y;
	if (!PyArg_ParseTuple (args, "ii", &cord_x, &cord_y))
		{
		PyErr_Print ();
		PyErr_Clear ();
		return Py_None;
		}
	u_gui->SetPopupPosition(cord_x, cord_y);
	return Py_None;
	}

PyObject *PySetPopupEnableButtons(PyObject *self, PyObject *args)
	{
	bool prev, next, ok;
	if (!PyArg_ParseTuple (args, "bbb", &prev, &next, &ok))
		{
		PyErr_Print ();
		PyErr_Clear ();
		return Py_None;
		}
	u_gui->SetPopupEnableButtons(prev, next, ok);
	return Py_None;
	}

PyObject *PySetPopupText(PyObject *self, PyObject *args)
	{
	char *text = NULL;
	if (!PyArg_ParseTuple (args, "s", &text))
		{
		PyErr_Print ();
		PyErr_Clear ();
		return Py_None;
		}
	u_gui->SetPopupText(text);
	return Py_None;
	}

PyObject *PySetPopupScriptNext(PyObject *self, PyObject *args)
	{
	char *filepath = NULL;
	if (!PyArg_ParseTuple (args, "s", &filepath))
		{
		PyErr_Print ();
		PyErr_Clear ();
		return Py_None;
		}
	u_gui->SetPopupScriptNext(filepath);
	return Py_None;
	}

PyObject *PySetPopupFaceImage(PyObject *self, PyObject *args)
	{
	char *filepath = NULL;
	if (!PyArg_ParseTuple (args, "s", &filepath))
		{
		PyErr_Print ();
		PyErr_Clear ();
		return Py_None;
		}
	u_gui->SetPopupFaceImage(filepath);
	return Py_None;
	}

PyObject *PySetPopupScriptPrev(PyObject *self, PyObject *args)
	{
	char *filepath = NULL;
	if (!PyArg_ParseTuple (args, "s", &filepath))
		{
		PyErr_Print ();
		PyErr_Clear ();
		return Py_None;
		}
	u_gui->SetPopupScriptPrev(filepath);
	return Py_None;
	}

PyObject *PySetPopupScriptOk(PyObject *self, PyObject *args)
	{
	char *filepath = NULL;
	if (!PyArg_ParseTuple (args, "s", &filepath))
		{
		PyErr_Print ();
		PyErr_Clear ();
		return Py_None;
		}
	u_gui->SetPopupScriptOk(filepath);
	return Py_None;
	}

PyObject *PyGetBPlay(PyObject *self, PyObject *args)
	{
	return Py_BuildValue("s", "hello");
	}

void InitPythonDGUI(DGUI *gui)
	{
	u_gui = gui;
	static PyMethodDef func[] = {
			{ "SetPlayMenu", PySetPlayMenu, METH_NOARGS },
			{ "GetBPlay", PyGetBPlay, METH_NOARGS },
			{ "SetPopupCaretRow", PySetPopupCaretRow, METH_VARARGS },
			{ "SetPopupVisible", PySetPopupVisible, METH_VARARGS },
			{ "SetPopupSize", PySetPopupSize, METH_VARARGS },
			{ "SetPopupPosition", PySetPopupPosition, METH_VARARGS },
			{ "SetPopupText", PySetPopupText, METH_VARARGS },
			{ "SetPopupEnableButtons", PySetPopupEnableButtons, METH_VARARGS },
			{ "SetPopupScriptNext", PySetPopupScriptNext, METH_VARARGS },
			{ "SetPopupScriptPrev", PySetPopupScriptPrev, METH_VARARGS },
			{ "SetPopupScriptOk", PySetPopupScriptOk, METH_VARARGS },
			{ "SetPopupFaceImage", PySetPopupFaceImage, METH_VARARGS },
			{ "PauseGame", PyPauseGame, METH_VARARGS },
			{ NULL, NULL, 0 }
			};
	Py_InitModule ("DGUI", func);
	}
}

