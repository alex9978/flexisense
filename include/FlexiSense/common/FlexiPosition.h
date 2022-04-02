
/*! FlexiSense2
 *  FlexiPosition.h
 *  Author: Alessandro Rasulo (mailto: alex9978@gmail.com)
 *  Notes: 2d vector used for define positions
 */

#ifndef FLEXIPOSITION_H
#define FLEXIPOSITION_H

#include <FlexiSense/FlexiExports.h>

class FLX_EXPORT FlexiPosition
{
public:
	FlexiPosition			(float _x, float _y) : x(_x), y(_y) {}
	FlexiPosition			() : x(0), y(0) {}
	virtual ~FlexiPosition	() {}

	inline void set			(float _x, float _y) { x = _x; y = _y; }
        
    /*! Operators */
    
    FlexiPosition operator+ (const FlexiPosition& right) const
    {
        return FlexiPosition(x+right.x, y+right.y);
    }
    
    FlexiPosition operator- (const FlexiPosition& right) const
    {
        return FlexiPosition(x-right.x, y-right.y);
    }
    
	float				     x;
 	float					 y;
};

#endif // FLEXIPOSITION_H
