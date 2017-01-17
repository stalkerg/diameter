#include "fonts_button.h"

namespace gcn
{
FontsButton::FontsButton(std::string text,ImageFont* in_font1, ImageFont *in_font2):
	Button(text)
	{
	font1 = in_font1;
	font2 = in_font2;
	setFont(font2);
	adjustSize();
	click=true;
	mKeyPressed = false;
	mMousePressed = false;
	}
void FontsButton::draw(Graphics* graphics)
	{
	int textX;
	int textY = getHeight() / 2 - getFont()->getHeight() / 2;

	switch (getAlignment())
		{
		case Graphics::LEFT:
			textX = 4;
			break;
		case Graphics::CENTER:
			textX = getWidth() / 2;
			break;
		case Graphics::RIGHT:
			textX = getWidth() - 4;
			break;
		default:
			throw GCN_EXCEPTION("Unknown alignment.");
		}

	if (mHasMouse)
		graphics->setFont(font1);
	else
		graphics->setFont(font2);
	
	graphics->drawText(getCaption(), textX, textY, getAlignment());
	}
void FontsButton::drawFrame(Graphics* graphics)
	{
	}
bool FontsButton::isClick()
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
