
/*! FlexiSense
 *  FlexiCircularSensitiveArea.cpp
 *  Author: Alessandro Rasulo (mailto: alex9978@gmail.com)
 *  Notes:
 */

#include <FlexiSense/sensitiveAreas/FlexiCircularSensitiveArea.h>

FlexiCircularSensitiveArea::FlexiCircularSensitiveArea(float x, float y, float radius)
{
	// assign coords
	X = x;
	Y = y;
	Radius = radius;
}

FlexiCircularSensitiveArea::~FlexiCircularSensitiveArea()
{
}

void FlexiCircularSensitiveArea::setBounds(float x, float y, float radius)
{
	// assign coords
	X = x;
	Y = y;

	if(radius != -1) Radius = radius;
}

void FlexiCircularSensitiveArea::moveBounds(float delta_x, float delta_y)
{
	setBounds(X + delta_x, Y + delta_y);
}

inline bool FlexiCircularSensitiveArea::isMouseOver(float mouse_x, float mouse_y)
{
	return (((mouse_x - X) * (mouse_x - X)  + (mouse_y - Y) * (mouse_y - Y) ) < (Radius * Radius));
}
