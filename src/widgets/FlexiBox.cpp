
#include <FlexiSense/widgets/FlexiBox.h>
#include <FlexiSense/FlexiManager.h>

FlexiBox::FlexiBox(const FlexiPosition &p, const FlexiSize &s, FlexiWidget *prnt) : FlexiWidget(p, s, prnt)
{
    // set class name
    className               = "box";    
}

FlexiBox::~FlexiBox()
{
}

void FlexiBox::resize(const FlexiPosition &p, const FlexiSize &s)
{
	// resize button
    position = p;
    size = s;
}

void FlexiBox::paint()
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
        FLX_GB1X1.paint(x, y, w, h, FLX_THEME.frame);
	}        
}
