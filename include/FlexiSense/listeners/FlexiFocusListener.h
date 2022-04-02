
/*! FlexiSense
 *  FlexiFocusListener.h
 *  Author: Alessandro Rasulo (mailto: alex9978@gmail.com)
 *  Notes:
 */

#ifndef FLEXIFOCUSLISTENER_H
#define FLEXIFOCUSLISTENER_H

#include <FlexiSense/FlexiExports.h>
#include <FlexiSense/events/FlexiFocusEvent.h>

class FLX_EXPORT FlexiFocusListener
{
public:
    FlexiFocusListener() {}
    virtual ~FlexiFocusListener() {}

    virtual void onFocus		(FlexiFocusEvent *event) = 0;
    virtual void onLostFocus	(FlexiFocusEvent *event) = 0;
	virtual void onMouseIn		(FlexiFocusEvent *event) = 0;
	virtual void onMouseOut		(FlexiFocusEvent *event) = 0;
};

#endif
