
/*! FlexiSense
 *  FlexiActionEvent.h
 *  Author: Alessandro Rasulo (mailto: alex9978@gmail.com)
 *  Notes:
 */

#ifndef FLEXIACTIONEVENT_H
#define FLEXIACTIONEVENT_H

#include <FlexiSense/events/FlexiEvent.h>

#define FLX_EVENT_ACTION_ACTIVATE		11	// This component is now active
#define FLX_EVENT_ACTION_DEACTIVATE		12	// This component is no longer active
#define FLX_EVENT_ACTION_SHOW			13	// This component is visible again
#define FLX_EVENT_ACTION_HIDE			14	// This component is no longer visible
#define FLX_EVENT_ACTION_VALUECHANGE	15	// Component's value changed
#define FLX_EVENT_ACTION_DONE			16	// Component editing done

class FLX_EXPORT FlexiActionEvent : public FlexiEvent
{
public:
	FlexiActionEvent(int type, long event_id = 0);
	virtual ~FlexiActionEvent();
};

#endif

