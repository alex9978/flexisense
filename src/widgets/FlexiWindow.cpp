
/*! FlexiSense
 *  FlexiWindow.cpp
 *  Author: Alessandro Rasulo (mailto: alex9978@gmail.com)
 *  Notes: Base window
 */

#include "FlexiSense/FlexiWidget.h"


#include "FlexiSense/FlexiWidget.h"


#include <FlexiSense/widgets/FlexiWindow.h>
#include <FlexiSense/sensitiveAreas/FlexiRectangularSensitiveArea.h>
#include <FlexiSense/FlexiManager.h>

FlexiWindow::FlexiWindow(const FlexiPosition &p, const FlexiSize &s, FlexiWidget *prnt) : FlexiWidget(p, s, prnt)
{
    // set class name
    className               = "window";
    
    // is container?
    container               = true;
    
    // set sensitive area (only titlebar)
    area                    = new FlexiRectangularSensitiveArea(p.x, p.y, p.x+s.width, p.y+FLX_THEME.wnd_titlebar_height);

    // create image surface
    imgSurface              = new FlexiImage();
    imgSurface->createSurface(s.width, s.height);

    // create context
	cairoContext = cairo_create(imgSurface->getSurface());
	cairo_set_antialias (cairoContext, CAIRO_ANTIALIAS_GRAY);

    // create frame
 /*   float w = getSize().width,
          h = getSize().height,
          th = FLX_THEME.wnd_titlebar_height,
          sw = FLX_THEME.wnd_side_width,
          bh = FLX_THEME.wnd_bottom_height;
    
    frame = new FlexiFrame(FlexiPosition(sw,th), FlexiSize(w-sw-sw,h-th-bh), this);
    if(frame)
        addChild(frame);

    // title font + label
    fontTitle = new FlexiFont((std::string)"verdana_bold.ttf");    
    lblTitle = new FlexiLabel(FlexiPosition(sw, 2), FlexiSize(w-sw-sw,15), "FlexiSense Window", FLX_ALIGN_INNER+FLX_ALIGN_CENTER, fontTitle, 11, 0, this);
    if(lblTitle)
    {
        lblTitle->foreColor = FLX_THEME.wnd_titlebar_textcolor;
        lblTitle->setShadow(true);
        addChild(lblTitle);
    }*/
}

FlexiWindow::~FlexiWindow()        
{
    if(fontTitle)
        delete fontTitle;

    if(cairoContext)
        cairo_destroy(cairoContext);
}

void FlexiWindow::resize(const FlexiPosition &p, const FlexiSize &s)
{
	// resize button    
    position = p;    
    size = s;

    float w = s.width,
          h = s.height,
          th = FLX_THEME.wnd_titlebar_height,
          sw = FLX_THEME.wnd_side_width,
          bh = FLX_THEME.wnd_bottom_height;

	// resize zone
    if(area)
        ((FlexiRectangularSensitiveArea *) area)->setBounds(p.x, p.y, p.x+s.width, p.y+FLX_THEME.wnd_titlebar_height);

    // resize frame
    if(frame)
        frame->setSize(FlexiSize(w-sw-sw,h-th-bh));
    
    // resize label
    if(lblTitle)
        lblTitle->setSize(FlexiSize(w-sw-sw,15));
}

void FlexiWindow::paint()
{
    // renderer
    FlexiGfxRenderer *gr = FlexiManager::instance()->getRenderer();
    
	// coordinates
	float x = getAbsPosition().x,
          y = getAbsPosition().y,
          w = getSize().width,
          h = getSize().height,
          th = FLX_THEME.wnd_titlebar_height,
          sw = FLX_THEME.wnd_side_width,
          bh = FLX_THEME.wnd_bottom_height;
	
	// paint
	/*if(backImage)
	{
		FlexiImage *topaint = 0;

//		if(hilighted || focused)
//			topaint = hilightedImage;
//		else
			topaint = backImage;

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
    	if(hilighted || focused)        
			FLX_GB3X1.paint(x, y, w, th, FLX_THEME.wnd_titlebar);            
		else
			FLX_GB3X1.paint(x, y, w, th, FLX_THEME.wnd_titlebar_inactive);

        FLX_GB1X3.paint(x, y+th, sw, h-th-bh, FLX_THEME.wnd_side);
        FLX_GB1X3.paint(x+w-sw, y+th, sw, h-th-bh, FLX_THEME.wnd_side);
        FLX_GB3X1.paint(x, y+h-bh, w, bh, FLX_THEME.wnd_bottom);
	}*/

    gr->drawLine(this, 10, 10, 40, 40, FlexiColor(0xff0000ff));
    
    // widget common paint ops
    FlexiWidget::paint();
}

cairo_t *FlexiWindow::getContext()
{
    return cairoContext;
}

int FlexiWindow::glPow2(int n)
{
	int value = 1;

	while(value < n)
		value <<= 1;

    return value;
}