
/*! FlexiSense
 *  FlexiMouseListener.h
 *  Author: Alessandro Rasulo (mailto: alex9978@gmail.com)
 *  Notes:
 */

#ifndef FLEXIMOUSELISTENER_H
#define FLEXIMOUSELISTENER_H

#include <FlexiSense/FlexiExports.h>
#include <FlexiSense/events/FlexiMouseEvent.h>

class FLX_EXPORT FlexiMouseListener
{
public:
	FlexiMouseListener() {}
	virtual ~FlexiMouseListener() {}

	virtual void onClick		(FlexiMouseEvent *event) = 0;
	virtual void onDrag			(FlexiMouseEvent *event) = 0;
	virtual void onRelease		(FlexiMouseEvent *event) = 0;
	virtual void onMove			(FlexiMouseEvent *event) = 0;
	virtual void onWheelMove	(FlexiMouseEvent *event) = 0;
};

#endif
