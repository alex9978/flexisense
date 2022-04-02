
/*! FlexiSense
 *  FlexiKeyEvent.cpp
 *  Author: Alessandro Rasulo (mailto: alex9978@gmail.com)
 *  Notes:
 */

#include <FlexiSense/events/FlexiKeyEvent.h>

FlexiKeyEvent::FlexiKeyEvent(int type, int keycode, char keyascii, int modifiers, long event_id) : FlexiEvent(type, event_id)
{
	keyCode = keycode;
	keyAscii = keyascii;
	keyModifiers = modifiers;
}

FlexiKeyEvent::~FlexiKeyEvent()
{
}

