
/*! FlexiSense2
 *  FlexiSize.h
 *  Author: Alessandro Rasulo (mailto: alex9978@gmail.com)
 *  Notes: 2d vector used for define sizes
 */

#ifndef FLEXISIZE_H
#define FLEXISIZE_H

#include <FlexiSense/FlexiExports.h>

class FLX_EXPORT FlexiSize
{
public:
	FlexiSize			    (float w, float h) : width(w), height(h) {}
	FlexiSize			    () : width(0), height(0) {}
	virtual ~FlexiSize	    () {}

	inline void set			(float w, float h) { width = w; height = h; }

    FlexiSize operator+ (const FlexiSize& right) const
    {
        return FlexiSize(width+right.width, height+right.height);
    }
    
    FlexiSize operator- (const FlexiSize& right) const
    {
        return FlexiSize(width-right.width, height-right.height);
    }
    
	float					 width;
	float					 height;
};

#endif // FLEXISIZE_H
