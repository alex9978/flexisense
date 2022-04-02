
/*! FlexiSense
 *  FlexiCircularSensitiveArea.h
 *  Author: Alessandro Rasulo (mailto: alex9978@gmail.com)
 *  Notes:
 */

#ifndef FLEXICIRCULARSENSITIVEAREA_H
#define FLEXICIRCULARSENSITIVEAREA_H

#include <FlexiSense/FlexiExports.h>
#include <FlexiSense/sensitiveAreas/FlexiSensitiveArea.h>

class FLX_EXPORT FlexiCircularSensitiveArea : public FlexiSensitiveArea
{
public:
	FlexiCircularSensitiveArea(float x, float y, float radius);
	virtual ~FlexiCircularSensitiveArea();

	void setBounds(float x, float y, float radius = -1);
	void moveBounds(float delta_x, float delta_y);

	bool isMouseOver(float mouse_x, float mouse_y);

private:
	float X;
	float Y;
	float Radius;
};

#endif // FLEXICIRCULARSENSITIVEAREA_H
