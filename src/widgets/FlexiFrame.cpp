
/*! FlexiSense
 *  FlexiFrame.cpp
 *  Author: Alessandro Rasulo (mailto: alex9978@gmail.com)
 *  Notes: Base frame
 */

#include <FlexiSense/widgets/FlexiFrame.h>
#include <FlexiSense/FlexiManager.h>

FlexiFrame::FlexiFrame(const FlexiPosition &p, const FlexiSize &s, FlexiWidget *prnt) : FlexiWidget(p, s, prnt)
{
    // set class name
    className               = "frame";
    
    // is container?
    container               = true;
}

FlexiFrame::~FlexiFrame()
{
}

void FlexiFrame::resize(const FlexiPosition &p, const FlexiSize &s)
{
	// resize button
    position = p;
    size = s;
}

void FlexiFrame::paint()
{
    // renderer
    FlexiGfxRenderer *gr = FlexiManager::instance()->getRenderer();
        
	// coordinates
	float x = getAbsPosition().x,
          y = getAbsPosition().y,
          w = getSize().width,
          h = getSize().height;    
    
	// paint
	if(backImage)
	{
		FlexiImage *topaint = backImage;

		if(topaint)
			switch(gridBagType)
			{            
            case FlexiGridBag::FLX_GRIDBAG_1X1:	FLX_GB1X1.paint(x, y, w, h, topaint);	break;
			case FlexiGridBag::FLX_GRIDBAG_1X3:	FLX_GB1X3.paint(x, y, w, h, topaint);	break;
			case FlexiGridBag::FLX_GRIDBAG_3X1:	FLX_GB3X1.paint(x, y, w, h, topaint);	break;
			case FlexiGridBag::FLX_GRIDBAG_3X3:	FLX_GB3X3.paint(x, y, w, h, topaint);	break;
			}
	}
	else
	{               
        //FLX_GB3X3.paint(x, y, w, h, FLX_THEME.frame);
        gr->drawBox(x,y,x+w,y+h,&backColor, true);
	}    
    
    // widget common paint ops
    FlexiWidget::paint();
}
