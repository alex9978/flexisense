
/*! FlexiSense
 *  FlexiEvent.cpp
 *  Author: Alessandro Rasulo (mailto: alex9978@gmail.com)
 *  Notes:
 */

#include <FlexiSense/events/FlexiEvent.h>

FlexiEvent::FlexiEvent(int type, long event_id)
{
	source 		= 0;
	eventType 	= type;
	id 			= event_id;
	consumed	= false;
}

FlexiEvent::~FlexiEvent()
{
}

void FlexiEvent::setSource(FlexiObject *object)
{
    source = object;
}
