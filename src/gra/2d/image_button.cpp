#include "image_button.h"

namespace gcn
{
DImageButton::DImageButton(gcn::Image *image1, gcn::Image *image2):
	Button()
	{
	mImage1=image1;
	mImage2=image2;
	setHeight(image1->getHeight());
	setWidth(image1->getWidth());
	click=true;
	mKeyPressed = false;
	mMousePressed = false;
	}
DImageButton::~DImageButton()
	{
	delete mImage1;
	delete mImage2;
	}
void DImageButton::draw(Graphics* graphics)
	{
	if (mHasMouse)
		graphics->drawImage(mImage2, 0, 0);
	else
		graphics->drawImage(mImage1, 0, 0);
	}
void DImageButton::drawFrame(Graphics* graphics)
	{
	}
bool DImageButton::isClick()
	{
	if(isPressed()&&click)
		{
		click=false;
		return true;
		}
	if(!isPressed())
		{
		click=true;
		mKeyPressed = false;
		mMousePressed = false;
		}
	return false;
	}
}

