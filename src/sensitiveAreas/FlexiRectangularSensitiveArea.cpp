
/*! FlexiSense
 *  FlexiRectangularSensitiveArea.cpp
 *  Author: Alessandro Rasulo (mailto: alex9978@gmail.com)
 *  Notes:
 */

#include <FlexiSense/sensitiveAreas/FlexiRectangularSensitiveArea.h>

FlexiRectangularSensitiveArea::FlexiRectangularSensitiveArea(float x1, float y1, float x2, float y2)
{
	float swap = 0;

	// check coords inversion
	if(x1 > x2)
 	{
 		swap = x2;
		x2 = x1;
		x1 = swap;
	}

	if(y1 > y2)
 	{
 		swap = y2;
		y2 = y1;
		y1 = swap;
	}

	// assign coords
	X1 = x1;
	Y1 = y1;
	X2 = x2;
	Y2 = y2;
}

FlexiRectangularSensitiveArea::~FlexiRectangularSensitiveArea()
{
}

void FlexiRectangularSensitiveArea::setBounds(float x1, float y1, float x2, float y2)
{
	float width = 0;
	float height = 0;
	float swap = 0;

	if(x2 == -1 && y2 == -1)
	{
		width = X2 - X1;
		height = Y2 - Y1;

		X1 = x1;
		Y1 = y1;
		X2 = x1 + width;
		Y2 = y1 + height;
	}
	else
	{
		// check coords inversion
		if(x1 > x2)
	 	{
	 		swap = x2;
			x2 = x1;
			x1 = swap;
		}

		if(y1 > y2)
	 	{
	 		swap = y2;
			y2 = y1;
			y1 = swap;
		}

		// assign coords
		X1 = x1;
		Y1 = y1;
		X2 = x2;
		Y2 = y2;
	}
}

void FlexiRectangularSensitiveArea::moveBounds(float delta_x, float delta_y)
{
	setBounds(X1 + delta_x, Y1 + delta_y);
}

inline bool FlexiRectangularSensitiveArea::isMouseOver(float mouse_x, float mouse_y)
{
	return (mouse_x >= X1 && mouse_x <= X2 && mouse_y >= Y1 && mouse_y <= Y2);
}
