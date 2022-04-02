
/*! @class FlexiColor
 *  @brief Class for storing a color value
 *  @author Alessandro Rasulo (mailto: alex9978@gmail.com)
 */

#ifndef FLEXICOLOR_H
#define FLEXICOLOR_H

#include <FlexiSense/FlexiExports.h>
#include <memory.h>

#define FLX_BLACK	    0x000000ff
#define FLX_DARKGRAY    0x555555ff
#define FLX_LIGHTGRAY   0xaaaaaaff
#define FLX_WHITE	    0xffffffff

class FLX_EXPORT FlexiColor
{
public:
	FlexiColor              ();
    FlexiColor              (FlexiColor *c);
	FlexiColor              (long color_rgba);
	FlexiColor              (float r, float g, float b, float a);
	FlexiColor              (float *color_array);
	virtual ~FlexiColor();

	// Setting functions
	void set			    (long color_rgba);
	void set			    (float r, float g, float b, float a);
	void set			    (float *color_array);

	// Getting functions    
	long getLong		    ();
	float *getFloat	        ();
    
    // Operators
    const FlexiColor& operator= (const FlexiColor& right);

private:
	long	                 long_color;
	float	                 float_color[4];

	void convertLongToFloat();
	void convertFloatToLong();
};

#endif // FLEXICOLOR_H
