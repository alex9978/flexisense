
/*! FlexiSense
 *  FlexiButton.cpp
 *  Author: Alessandro Rasulo (mailto: alex9978@gmail.com)
 *  Notes: Simple button
 */

#include <FlexiSense/widgets/FlexiButton.h>
#include <FlexiSense/listeners/DefaultButtonListeners.h>
#include <FlexiSense/sensitiveAreas/FlexiRectangularSensitiveArea.h>
#include <FlexiSense/FlexiManager.h>


FlexiButton::FlexiButton(const FlexiPosition &p, const FlexiSize &s, const std::string caption, FlexiWidget *prnt) : FlexiWidget(p, s, prnt)
{	
	className       	= "button";

    label               = new FlexiLabel(FlexiPosition(0,0), FlexiSize(s.width,s.height), caption.c_str(), FLX_ALIGN_IN, 0, 13, 0, this);
	pressedImage		= 0;
	hilightedImage		= 0;
	pressed				= false;
	
	// add default listeners
	addMouseListener( new ButtonMouseListener() );
	addFocusListener( new ButtonFocusListener() );
	addKeyListener( new ButtonKeyListener() );
}

FlexiButton::~FlexiButton()
{
    if(label) delete label;
}

void FlexiButton::resize(const FlexiPosition &pos, const FlexiSize &size)
{
	// resize button    
    position = pos;    
    this->size = size;
	
	// resize zone
	((FlexiRectangularSensitiveArea *) area)->setBounds(pos.x, pos.y, pos.x+size.width, pos.y+size.height);

	if(label) label->setSize(FlexiSize(size.width,size.height));
}

void FlexiButton::paint()
{
	// get renderer
	FlexiGfxRenderer *renderer = FlexiManager::instance()->getRenderer(); 
	
	// coordinates
	float x = getAbsPosition().x;
	float y = getAbsPosition().y;
	float w = getSize().width;
	float h = getSize().height;
	
	// paint
	if(backImage)
	{
		FlexiImage *topaint = 0;

	 	if(!pressed)
			if(hilighted || focused)
				topaint = hilightedImage;
			else
				topaint = backImage;
		else
			topaint = pressedImage;

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
	 	if(!pressed)
			if(hilighted || focused)
				FLX_GB3X3.paint(x, y, w, h, &FLX_THEME.button_focus);
			else
				FLX_GB3X3.paint(x, y, w, h, FLX_THEME.btn_normal);
		else
			FLX_GB3X3.paint(x, y, w, h, &FLX_THEME.button_pressed);
	}

	// paint label
	if(label) label->paint();
}

void FlexiButton::setPressedImage(FlexiImage *image)
{
	if(pressedImage) delete pressedImage;
	pressedImage = image;
}

void FlexiButton::setHilightedImage(FlexiImage *image)
{
	if(hilightedImage) delete hilightedImage;
	hilightedImage = image;
}

void FlexiButton::setPressedState(bool state)
{
	pressed = state;

	// call action listener
	callActionListener( new FlexiActionEvent(FLX_EVENT_ACTION_VALUECHANGE) );
}
