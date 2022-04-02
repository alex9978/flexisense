
/*! FlexiSense
 *  FlexiMouseEvent.h
 *  Author: Alessandro Rasulo (mailto: alex9978@gmail.com)
 *  Notes:
 */

#ifndef FLEXIMOUSEEVENT_H
#define FLEXIMOUSEEVENT_H

#include <FlexiSense/events/FlexiEvent.h>
#include <FlexiSense/common/FlexiPosition.h>

#define FLX_EVENT_MOUSE_CLICK			51	/*! A mouse button has gone down with the mouse pointing at this component */
#define FLX_EVENT_MOUSE_DRAG			52	/*! The mouse has moved with a button held down */
#define FLX_EVENT_MOUSE_RELEASE			53	/*! A mouse button has been released */
#define FLX_EVENT_MOUSE_MOVE			54	/*! The mouse has moved without any mouse buttons held down */
#define FLX_EVENT_MOUSE_WHEEL			55	/*! The user has moved the mouse wheel */

#define FLX_MOUSE_LEFTBUTTON			1	/*! Mouse buttons */
#define FLX_MOUSE_MIDDLEBUTTON			2
#define FLX_MOUSE_RIGHTBUTTON			4

class FLX_EXPORT FlexiMouseEvent : public FlexiEvent
{
public:
	FlexiMouseEvent(int type, float mouseX, float mouseY, int mouseButtons, int mouseWheel, int long event_id = 0);
	virtual ~FlexiMouseEvent();

	float getMouseX 				    () { return mouseCoordinates.x; }
	float getMouseY 				    () { return mouseCoordinates.y; }
	int   getMouseButtonsState		    () { return mouseButtonsState; }
	bool  isMouseLeftButtonClicked	    () { return ((mouseButtonsState & FLX_MOUSE_LEFTBUTTON) > 0); }
	bool  isMouseMiddleButtonClicked	() { return ((mouseButtonsState & FLX_MOUSE_MIDDLEBUTTON) > 0); }
	bool  isMouseRightButtonClicked	    () { return ((mouseButtonsState & FLX_MOUSE_RIGHTBUTTON) > 0); }
	int   getMouseWheelState			() { return mouseWheelState; }
	bool  isMouseWheelDirectionUp	    () { return (mouseWheelState < 0) ? true : false; }
	bool  isMouseWheelDirectionDown	    () { return (mouseWheelState > 0) ? true : false; }

private:
	FlexiPosition       mouseCoordinates;
	int					mouseButtonsState;
	int 				mouseWheelState;
};

#endif

