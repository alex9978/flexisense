
/*! FlexiSense
 *  FlexiFocusEvent.h
 *  Author: Alessandro Rasulo (mailto: alex9978@gmail.com)
 *  Notes:
 */

#ifndef FLEXIFOCUSEVENT_H
#define FLEXIFOCUSEVENT_H

#include <FlexiSense/events/FlexiEvent.h>

#define FLX_EVENT_GOTFOCUS		31
#define FLX_EVENT_LOSTFOCUS		32
#define FLX_EVENT_MOUSEIN		33
#define FLX_EVENT_MOUSEOUT		34

class FLX_EXPORT FlexiFocusEvent : public FlexiEvent
{
public:
	FlexiFocusEvent(int type, long event_id = 0);
	virtual ~FlexiFocusEvent();
};

#endif

