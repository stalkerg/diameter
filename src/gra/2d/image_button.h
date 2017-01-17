#ifndef UI2D_GUI_IMAGEBUTTON
#define UI2D_GUI_IMAGEBUTTON

#include <guichan.hpp>
#include <guichan/sdl.hpp>
#include <guichan/opengl.hpp>

#include "../../uni.h"

namespace gcn
{
class DImageButton:  public gcn::Button
	{
	Image *mImage1,*mImage2;
	bool click;
	public:
	DImageButton(Image *image1,Image *image2);
	~DImageButton();
	void draw(Graphics* graphics);
	void drawFrame(Graphics* graphics);
	bool isClick();
	};
}
#endif
