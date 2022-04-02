
/*! FlexiSense
 *  FlexiEventParam.h
 *  Author: Alessandro Rasulo (mailto: alex9978@gmail.com)
 *  Notes: Structure for manage generic event data
 */

#ifndef FLEXIEVENTPARAM_H
#define FLEXIEVENTPARAM_H

#include <FlexiSense/FlexiExports.h>

typedef struct flexi_event_param
{
	int			 type;			// event type
	int			 keyCode;		// key related
	int			 keyAscii;
	int			 modifiers;
	float		 mouseX;		// mouse related
	float		 mouseY;
	int			 mouseButtons;
	int			 mouseWheel;

	// constructor
	flexi_event_param(int _type, int _keyCode, int _keyAscii, int _modifiers, float _mouseX, float _mouseY, int _mouseButtons, int _mouseWheel) :
	type(_type),
	keyCode(_keyCode),
	keyAscii(_keyAscii),
	modifiers(_modifiers),
	mouseX(_mouseX),
	mouseY(_mouseY),
	mouseButtons(_mouseButtons),
	mouseWheel(_mouseWheel) {}

} FlexiEventParam;

#endif
