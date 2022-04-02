
/*! @class FlexiGridBag
 *  @brief GridBag for drawing images
 *  @author Alessandro Rasulo (mailto: alex9978@gmail.com) 
 */

#ifndef FLEXIGRIDBAG_H
#define FLEXIGRIDBAG_H

#include <FlexiSense/FlexiExports.h>
#include <FlexiSense/FlexiGfxRenderer.h>
#include <FlexiSense/common/FlexiColor.h>
#include <FlexiSense/common/FlexiImage.h>

typedef struct flexi_grid_unit
{
    float   x, y, w, h;
	float   u1, v1, u2, v2;
} FlexiGridUnit;

class FLX_EXPORT FlexiGridBag
{
public:            
    enum FLX_GRIDBAG
    {
        /*! 1x1 gridbag */
        FLX_GRIDBAG_1X1     = 1,
        /*! 3x1 horizontal gridbag */
        FLX_GRIDBAG_3X1     = 2,
        /*! 1x3 vertical gridbag */
        FLX_GRIDBAG_1X3     = 3,
        /*! 3x3 gridbag */
        FLX_GRIDBAG_3X3     = 4
    };
    
	FlexiGridBag();
	FlexiGridBag(int grid_type);
	virtual ~FlexiGridBag();

	void setType(int grid_type);
	void paint(float x, float y, float w, float h, FlexiImage *image);

private:
	int				type;
	FlexiGridUnit	array[3][3];

    void generateCoordinates(float x, float y, float w, float h, FlexiImage *image);
};

#endif
