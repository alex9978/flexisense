
#ifndef DEFAULTBUTTONLISTENERS_H
#define DEFAULTBUTTONLISTENERS_H

#include <FlexiSense/widgets/FlexiButton.h>
#include <FlexiSense/listeners/FlexiMouseListener.h>
#include <FlexiSense/listeners/FlexiFocusListener.h>
#include <FlexiSense/listeners/FlexiKeyListener.h>

class ButtonMouseListener : public FlexiMouseListener
{
public:
	void onClick		(FlexiMouseEvent *event);
	void onDrag			(FlexiMouseEvent *event) {}
	void onRelease		(FlexiMouseEvent *event);
	void onMove			(FlexiMouseEvent *event) {}
	void onWheelMove	(FlexiMouseEvent *event) {}
};

class ButtonFocusListener : public FlexiFocusListener
{
public:    
    void onFocus		(FlexiFocusEvent *event) {}
    void onLostFocus	(FlexiFocusEvent *event);
	void onMouseIn		(FlexiFocusEvent *event) {}
	void onMouseOut		(FlexiFocusEvent *event) {}
};

class ButtonKeyListener : public FlexiKeyListener
{
public:
	void onKeyDown		(FlexiKeyEvent *event);
	void onKeyUp		(FlexiKeyEvent *event);
 	void onKeyPress		(FlexiKeyEvent *event) {}
};

#endif
