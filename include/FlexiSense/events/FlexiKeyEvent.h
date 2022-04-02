
/*! FlexiSense
 *  FlexiKeyEvent.h
 *  Author: Alessandro Rasulo (mailto: alex9978@gmail.com)
 *  Notes:
 */

#ifndef FLEXIKEYEVENT_H
#define FLEXIKEYEVENT_H

#include <FlexiSense/events/FlexiEvent.h>

#define FLX_EVENT_KEY_DOWN		41	// A key was pressed
#define FLX_EVENT_KEY_UP		42	// A key was released
#define FLX_EVENT_PRESS			43	// A key was pressed, generates a ascii code.

class FLX_EXPORT FlexiKeyEvent : public FlexiEvent
{
public:
	FlexiKeyEvent(int type, int keycode, char keyascii, int modifiers, long event_id = 0);
	virtual ~FlexiKeyEvent();

	int	 getKeyCode()	{ return keyCode; }
	char getKeyAscii()	{ return keyAscii; }
	int  getModifiers()	{ return keyModifiers; }

	bool isShiftPressed();
	bool isCtrlPressed();
	bool isAltPressed();

private:
	int	 keyCode;
	char keyAscii;
	int  keyModifiers;
};

#endif

