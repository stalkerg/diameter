#ifndef UI2D_GUI_ICONEXT
#define UI2D_GUI_ICONEXT

#include <guichan.hpp>
#include <guichan/sdl.hpp>
#include <guichan/opengl.hpp>

namespace gcn
{
class IconExt:  public gcn::Icon
	{
	public:
	~IconExt(){};
	IconExt(Image *image):Icon(image){};
	void setImage(Image *image)
		{
		if (mImage!=NULL)
			delete mImage;
		mImage = image;
		setHeight(image->getHeight());
		setWidth(image->getWidth());
		}
	};
}

#endif
