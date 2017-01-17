#ifndef UI2D_GUI_TEXTCHECKBOX
#define UI2D_GUI_TEXTCHECKBOX

#include <guichan.hpp>
#include <guichan/sdl.hpp>
#include <guichan/opengl.hpp>


namespace gcn
{
class TextCheckBox:  public gcn::CheckBox
	{
	public:
	TextCheckBox(bool marked=false);
	void drawBox(Graphics* graphics);
	};
}
#endif
