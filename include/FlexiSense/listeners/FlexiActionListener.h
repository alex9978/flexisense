
/*! FlexiSense
 *  FlexiActionListener.h
 *  Author: Alessandro Rasulo (mailto: alex9978@gmail.com)
 *  Notes:
 */

#ifndef FLEXIACTIONLISTENER_H
#define FLEXIACTIONLISTENER_H

#include <FlexiSense/FlexiExports.h>
#include <FlexiSense/events/FlexiActionEvent.h>

class FLX_EXPORT FlexiActionListener
{
public:
	FlexiActionListener() {}
	virtual ~FlexiActionListener() {}

	virtual void onActivate		(FlexiActionEvent *event) = 0;
	virtual void onDeActivate	(FlexiActionEvent *event) = 0;
	virtual void onShow			(FlexiActionEvent *event) = 0;
	virtual void onHide			(FlexiActionEvent *event) = 0;
	virtual void onValueChange	(FlexiActionEvent *event) = 0;
	virtual void onDone			(FlexiActionEvent *event) = 0;
};

#endif
