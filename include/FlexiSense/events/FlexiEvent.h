
/*! FlexiSense
 *  FlexiEvent.h
 *  Author: Alessandro Rasulo (mailto: alex9978@gmail.com)
 *  Notes:
 */

#ifndef FLEXIEVENT_H
#define FLEXIEVENT_H

#include <FlexiSense/FlexiExports.h>
#include <FlexiSense/FlexiObject.h>

class FLX_EXPORT FlexiEvent
{
public:
	FlexiEvent(int type, long event_id = 0);
	virtual ~FlexiEvent();

	void			setSource	(FlexiObject *object);

	FlexiObject    *getSource	() { return source; }		// get event's source
	int				getType		() { return eventType; }	// get event's type
	long			getID		() { return id; }			// get event's id

	bool			isConsumed	() { return consumed; }
	void			consume		() { consumed = true; }

private:
	FlexiObject    *source;
	int				eventType;
	long			id;

	bool			consumed;
};

#endif

