#include "text_checkbox.h"

namespace gcn
{
TextCheckBox::TextCheckBox(bool marked):
	CheckBox()
	{
	mSelected = marked;
	}
void TextCheckBox::drawBox(Graphics* graphics)
	{
	int h = getHeight() - 1;
	int alpha = getBaseColor().a;
	Color faceColor = getBaseColor();
	faceColor.a = alpha;
	Color highlightColor = faceColor + 0x303030;
	highlightColor.a = alpha;
	Color shadowColor = faceColor - 0x303030;
	shadowColor.a = alpha;

	graphics->setColor(shadowColor);
	graphics->drawLine(0, 0, h, 0);
	graphics->drawLine(0, 1, 0, h);

	graphics->setColor(highlightColor);
	graphics->drawLine(h, 1, h, h);
	graphics->drawLine(1, h, h - 1, h);

	graphics->setColor(getBackgroundColor());
	graphics->fillRectangle(Rectangle(1, 1, h - 1, h - 1));

	graphics->setColor(getForegroundColor());

	if (mSelected)
		{
		graphics->drawText("X", h-40, 1);
		}
	}
}
