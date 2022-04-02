
#include <FlexiSense/common/FlexiColor.h>

/*! Constructor
 */
FlexiColor::FlexiColor()
{
	set(FLX_BLACK);
}

/*! Constructor
 *  @param c Sets the color from another color
 */
FlexiColor::FlexiColor(FlexiColor *c)
{
	set(c->getLong());
}

/*! Constructor
 *  @param color Sets the color from an hexadecimal value
 */
FlexiColor::FlexiColor(long color)
{
	set(color);
}

/*! Constructor
 *  @param r Red component of the color
 *  @param g Green component of the color
 *  @param b Blue component of the color
 *  @param a Alpha component of the color
 */
FlexiColor::FlexiColor(float r, float g, float b, float a)
{
	set(r, g, b, a);
}

/*! Constructor
 *  @param color_array Sets the color from an array of 4 float values
 */
FlexiColor::FlexiColor(float *color_array)
{
	set(color_array);
}

/*  Destructor
 */
FlexiColor::~FlexiColor()
{
}

/*! Sets the color from an hexadecimal value
 *  @param color (eg. 0xaaaaaaff)
 */
void FlexiColor::set(long color)
{
	long_color = color;
	convertLongToFloat();
}

/*! Sets the color from 4 float values
 *  @param r Red component of the color
 *  @param g Green component of the color
 *  @param b Blue component of the color
 *  @param a Alpha component of the color
 */
void FlexiColor::set(float r, float g, float b, float a)
{
	float_color[0] = r;
	float_color[1] = g;
	float_color[2] = b;
	float_color[3] = a;
	convertFloatToLong();
}

/*! Sets the color from an array of 4 float values
 *  @param color_array Float array pointer
 */
void FlexiColor::set(float *color_array)
{
	memcpy(float_color, color_array, 4 * sizeof(float));
	convertFloatToLong();
}

/*! Gets the color as a long value
 *  @return a long value
 */
long FlexiColor::getLong()
{
    return long_color;
}

/*! Gets the color as an array of float
 *  @return a float array pointer
 */
float *FlexiColor::getFloat()
{
    return float_color;
}

/*! Operator =
 */
const FlexiColor& FlexiColor::operator= (const FlexiColor& right)
{
    long_color = right.long_color;
    convertLongToFloat();
    return right;
}

void FlexiColor::convertLongToFloat()
{
	float_color[0] = ((long_color >> 24) & 0x000000FF) / 255.0f;	// R
	float_color[1] = ((long_color >> 16) & 0x000000FF) / 255.0f;	// G
	float_color[2] = ((long_color >>  8) & 0x000000FF) / 255.0f;	// B
	float_color[3] =  (long_color		 & 0x000000FF) / 255.0f;	// A
}

void FlexiColor::convertFloatToLong()
{
	long_color = 0;
	long_color += ((long)(float_color[0] * 255.0f) << 24);		    // R
	long_color += ((long)(float_color[1] * 255.0f) << 16);		    // G
	long_color += ((long)(float_color[2] * 255.0f) <<  8);		    // B
	long_color += ((long)(float_color[3] * 255.0f));				// A
}
