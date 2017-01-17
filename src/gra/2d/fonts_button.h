#ifndef UI2D_GUI_FONTSBUTTON
#define UI2D_GUI_FONTSBUTTON

#include <guichan.hpp>
#include <guichan/sdl.hpp>
#include <guichan/opengl.hpp>

#include "../../uni.h"

namespace gcn
{
class FontsButton:  public gcn::Button
	{
	ImageFont *font1, *font2;
	bool click;
	public:
	FontsButton(std::string text, ImageFont* in_font1, ImageFont *in_font2);
	void draw(Graphics* graphics);
	void drawFrame(Graphics* graphics);
	bool isClick();
	};
}
#endif
