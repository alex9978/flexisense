
/*! FlexiSense
 *  FlexiMouseEvent.cpp
 *  Author: Alessandro Rasulo (mailto: alex9978@gmail.com)
 *  Notes:
 */

#include <FlexiSense/events/FlexiMouseEvent.h>

FlexiMouseEvent::FlexiMouseEvent(int type, float mouseX, float mouseY, int mouseButtons, int mouseWheel, int long event_id) : FlexiEvent(type, event_id)
{
	mouseCoordinates.set(mouseX, mouseY);
	mouseButtonsState = mouseButtons;
	mouseWheelState   = mouseWheel;
}

FlexiMouseEvent::~FlexiMouseEvent()
{
}
