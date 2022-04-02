
/*! FlexiSense
 *  FlexiKeyListener.h
 *  Author: Alessandro Rasulo (mailto: alex9978@gmail.com)
 *  Notes:
 */

#ifndef FLEXIKEYLISTENER_H
#define FLEXIKEYLISTENER_H

#include <FlexiSense/FlexiExports.h>
#include <FlexiSense/events/FlexiKeyEvent.h>

class FLX_EXPORT FlexiKeyListener
{
public:
	FlexiKeyListener() {}
	virtual ~FlexiKeyListener() {}

	virtual void onKeyDown		(FlexiKeyEvent *event) = 0;
	virtual void onKeyUp		(FlexiKeyEvent *event) = 0;
	virtual void onKeyPress		(FlexiKeyEvent *event) = 0;
};

#endif

