
/*! FlexiSense
 *  FlexiRectangularSensitiveArea.h
 *  Author: Alessandro Rasulo (mailto: alex9978@gmail.com)
 *  Notes:
 */

#ifndef FLEXIRECTANGULARSENSITIVEAREA_H
#define FLEXIRECTANGULARSENSITIVEAREA_H

#include <FlexiSense/sensitiveAreas/FlexiSensitiveArea.h>

class FlexiRectangularSensitiveArea : public FlexiSensitiveArea
{
public:
	FlexiRectangularSensitiveArea(float x1, float y1, float x2, float y2);
	virtual ~FlexiRectangularSensitiveArea();

	void setBounds(float x1, float y1, float x2 = -1, float y2 = -1);
	void moveBounds(float delta_x, float delta_y);

	bool isMouseOver(float mouse_x, float mouse_y);

private:
	float X1;
	float Y1;
	float X2;
	float Y2;
};

#endif // FLEXIRECTANGULARSENSITIVEAREA_H
