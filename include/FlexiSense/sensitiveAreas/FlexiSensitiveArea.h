
/*! FlexiSense
 *  FlexiSensitiveArea.h
 *  Author: Alessandro Rasulo (mailto: alex9978@gmail.com)
 *  Notes: Base object
 */

#ifndef FLEXISENSITIVEAREA_H
#define FLEXISENSITIVEAREA_H

#include <FlexiSense/FlexiExports.h>

class FLX_EXPORT FlexiSensitiveArea
{
public:
    FlexiSensitiveArea() {}
    virtual ~FlexiSensitiveArea() {}

	virtual void moveBounds				(float delta_x, float delta_y) = 0;
	virtual bool isMouseOver            (float mouse_x, float mouse_y) = 0;
};

#endif // FLEXISENSITIVEAREA_H
