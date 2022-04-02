
#include <FlexiSense/common/FlexiGridBag.h>
#include <FlexiSense/FlexiManager.h>

/*! Constructor 
 */
FlexiGridBag::FlexiGridBag()
{
    setType(FLX_GRIDBAG_1X1);
}

/*! Constructor 
 *  @param grid_type Type of gridbag
 */
FlexiGridBag::FlexiGridBag(int grid_type)
{
	setType(grid_type);
}

/*! Destructor
 */
FlexiGridBag::~FlexiGridBag()
{
}

/*! Sets the type of the gridbag 
 *  @param grid_type Type of gridbag
 */
void FlexiGridBag::setType(int grid_type)
{
	float row, col;
	type = grid_type;

	switch(type)
	{
	case FLX_GRIDBAG_1X1:	row = 1; col = 1;	break;
	case FLX_GRIDBAG_3X1:	row = 1; col = 3;	break;
	case FLX_GRIDBAG_1X3:	row = 3; col = 1;	break;
	case FLX_GRIDBAG_3X3:	row = 3; col = 3;	break;
	}

	for(int j=0; j<row; j++)
		for(int i=0; i<col; i++)
		{
			array[i][j].u1 = (float)i / col;
			array[i][j].v1 = (float)j / row;
			array[i][j].u2 = (float)(i+1) / col;
			array[i][j].v2 = (float)(j+1) / row;
		}
}

/*! Paints the gridbag 
 *  @param x position
 *  @param y position
 *  @param w size
 *  @param h size
 *  @param image the image to paint
 */
void FlexiGridBag::paint(float x, float y, float w, float h, FlexiImage *image)
{
    float w1, w2, h1, h2;
	FlexiGfxRenderer *renderer = FlexiManager::instance()->getRenderer();

    generateCoordinates(x, y, w, h, image);

	switch(type)
	{
	case FLX_GRIDBAG_1X1:
		renderer->drawImage(array[0][0].x, array[0][0].y, array[0][0].w, array[0][0].h, 0, 0, 1, 1, image, 0);
		break;

	case FLX_GRIDBAG_3X1:
		renderer->drawImage(array[0][0].x, array[0][0].y, array[0][0].w, array[0][0].h, array[0][0].u1, array[0][0].v1, array[0][0].u2, array[0][0].v2, image, 0);
		renderer->drawImage(array[1][0].x, array[1][0].y, array[1][0].w, array[1][0].h, array[1][0].u1, array[1][0].v1, array[1][0].u2, array[1][0].v2, image, 0);
		renderer->drawImage(array[2][0].x, array[2][0].y, array[2][0].w, array[2][0].h, array[2][0].u1, array[2][0].v1, array[2][0].u2, array[2][0].v2, image, 0);
		break;

	case FLX_GRIDBAG_1X3:
		renderer->drawImage(array[0][0].x, array[0][0].y, array[0][0].w, array[0][0].h, array[0][0].u1, array[0][0].v1, array[0][0].u2, array[0][0].v2, image, 0);
		renderer->drawImage(array[0][1].x, array[0][1].y, array[0][1].w, array[0][1].h, array[0][1].u1, array[0][1].v1, array[0][1].u2, array[0][1].v2, image, 0);
		renderer->drawImage(array[0][2].x, array[0][2].y, array[0][2].w, array[0][2].h, array[0][2].u1, array[0][2].v1, array[0][2].u2, array[0][2].v2, image, 0);
		break;

	case FLX_GRIDBAG_3X3:
		renderer->drawImage(array[0][0].x, array[0][0].y, array[0][0].w, array[0][0].h, array[0][0].u1, array[0][0].v1, array[0][0].u2, array[0][0].v2, image, 0);
		renderer->drawImage(array[1][0].x, array[1][0].y, array[1][0].w, array[1][0].h, array[1][0].u1, array[1][0].v1, array[1][0].u2, array[1][0].v2, image, 0);
		renderer->drawImage(array[2][0].x, array[2][0].y, array[2][0].w, array[2][0].h, array[2][0].u1, array[2][0].v1, array[2][0].u2, array[2][0].v2, image, 0);
		renderer->drawImage(array[0][1].x, array[0][1].y, array[0][1].w, array[0][1].h, array[0][1].u1, array[0][1].v1, array[0][1].u2, array[0][1].v2, image, 0);
		renderer->drawImage(array[1][1].x, array[1][1].y, array[1][1].w, array[1][1].h, array[1][1].u1, array[1][1].v1, array[1][1].u2, array[1][1].v2, image, 0);
		renderer->drawImage(array[2][1].x, array[2][1].y, array[2][1].w, array[2][1].h, array[2][1].u1, array[2][1].v1, array[2][1].u2, array[2][1].v2, image, 0);
		renderer->drawImage(array[0][2].x, array[0][2].y, array[0][2].w, array[0][2].h, array[0][2].u1, array[0][2].v1, array[0][2].u2, array[0][2].v2, image, 0);
		renderer->drawImage(array[1][2].x, array[1][2].y, array[1][2].w, array[1][2].h, array[1][2].u1, array[1][2].v1, array[1][2].u2, array[1][2].v2, image, 0);
		renderer->drawImage(array[2][2].x, array[2][2].y, array[2][2].w, array[2][2].h, array[2][2].u1, array[2][2].v1, array[2][2].u2, array[2][2].v2, image, 0);
		break;
	}
}

void FlexiGridBag::generateCoordinates(float x, float y, float w, float h, FlexiImage *image)
{
    int w1, w2, h1, h2, x2, x3, y2, y3;

    switch(type)
	{
	case FLX_GRIDBAG_1X1:
        array[0][0].x = x; array[0][0].y = y; array[0][0].w = w; array[0][0].h = h;
		break;

	case FLX_GRIDBAG_3X1:
        w1 = image->getSize().width / 3;        
        array[0][0].x = x;      array[0][0].y = y; array[0][0].w = w1;   array[0][0].h = h;
        array[1][0].x = x+w1;   array[1][0].y = y; array[1][0].w = w-w1; array[1][0].h = h;
        array[2][0].x = x+w-w1; array[2][0].y = y; array[2][0].w = w1;   array[2][0].h = h;
		break;

	case FLX_GRIDBAG_1X3:
        h1 = image->getSize().height / 3;
        array[0][0].x = x; array[0][0].y = y;      array[0][0].w = w; array[0][0].h = h1;
        array[0][1].x = x; array[0][1].y = y+h1;   array[0][1].w = w; array[0][1].h = h-h1;
        array[0][2].x = x; array[0][2].y = y+h-h1; array[0][2].w = w; array[0][2].h = h1;
		break;

	case FLX_GRIDBAG_3X3:
		w1 = image->getSize().width / 3;
        w2 = w-w1;
		h1 = image->getSize().height / 3;
        h2 = h-h1;
        x2 = x+w1;
        x3 = x+w-w1;
        y2 = y+h1;
        y3 = y+h-h1;
        array[0][0].x = x;  array[0][0].y = y;  array[0][0].w = w1; array[0][0].h = h1;
        array[1][0].x = x2; array[1][0].y = y;  array[1][0].w = w2; array[1][0].h = h1;
        array[2][0].x = x3; array[2][0].y = y;  array[2][0].w = w1; array[2][0].h = h1;
        array[0][1].x = x;  array[0][1].y = y2; array[0][1].w = w1; array[0][1].h = h2;
        array[1][1].x = x2; array[1][1].y = y2; array[1][1].w = w2; array[1][1].h = h2;
        array[2][1].x = x3; array[2][1].y = y2; array[2][1].w = w1; array[2][1].h = h2;
        array[0][2].x = x;  array[0][2].y = y3; array[0][2].w = w1; array[0][2].h = h1;
        array[1][2].x = x2; array[1][2].y = y3; array[1][2].w = w2; array[1][2].h = h1;
        array[2][2].x = x3; array[2][2].y = y3; array[2][2].w = w1; array[2][2].h = h1;
		break;
	}
}

/*
 *	switch(type)
	{
	case FLX_GRIDBAG_1X1:
		renderer->drawImage(x, y, w, h, 0, 0, 1, 1, image, 0);
		break;

	case FLX_GRIDBAG_3X1:
        w1 = image->getSize().width / 3.0f;
        w2 = w - w1*2;

        array[0][0].x = x;      array[0][0].y = y;
        array[1][0].x = x;      array[1][0].y = y;
        array[2][0].x = x;      array[2][0].y = y;

		renderer->drawImage(x,		    y,			w1+1,   h, array[0][0].u1, array[0][0].v1, array[0][0].u2, array[0][0].v2, image, 0);
		renderer->drawImage(x+w1,       y,			w2+1, h, array[1][0].u1, array[1][0].v1, array[1][0].u2, array[1][0].v2, image, 0);
		renderer->drawImage(x+w1+w2,    y,			w1+1,   h, array[2][0].u1, array[2][0].v1, array[2][0].u2, array[2][0].v2, image, 0);
		break;

	case FLX_GRIDBAG_1X3:
        h1 = image->getSize().height / 3.0f;
        h2 = h - h1*2;
		// one column
		renderer->drawImage(x,			y,			w, h1+1,   array[0][0].u1, array[0][0].v1, array[0][0].u2, array[0][0].v2, image, 0);
		renderer->drawImage(x,			y+h1,       w, h2+1, array[0][1].u1, array[0][1].v1, array[0][1].u2, array[0][1].v2, image, 0);
		renderer->drawImage(x,			y+h1+h2,    w, h1+1,   array[0][2].u1, array[0][2].v1, array[0][2].u2, array[0][2].v2, image, 0);
		break;

	case FLX_GRIDBAG_3X3:
		w1 = image->getSize().width / 3.0f;
        w2 = w - w1*2;
		h1 = image->getSize().height / 3.0f;
        h2 = h - h1*2;
		// first row
		renderer->drawImage(x,			y,			w1, h1, array[0][0].u1, array[0][0].v1, array[0][0].u2, array[0][0].v2, image, 0);
		renderer->drawImage(x+w1,       y,			w2+1, h1, array[1][0].u1, array[1][0].v1, array[1][0].u2, array[1][0].v2, image, 0);
		renderer->drawImage(x+w1+w2,    y,			w1+1, h1+1, array[2][0].u1, array[2][0].v1, array[2][0].u2, array[2][0].v2, image, 0);
		// second row
		renderer->drawImage(x,			y+h1,       w1, h2+1, array[0][1].u1, array[0][1].v1, array[0][1].u2, array[0][1].v2, image, 0);
		renderer->drawImage(x+w1,       y+h1,       w2+1, h2+1, array[1][1].u1, array[1][1].v1, array[1][1].u2, array[1][1].v2, image, 0);
		renderer->drawImage(x+w1+w2,    y+h1,       w1+1, h2+1, array[2][1].u1, array[2][1].v1, array[2][1].u2, array[2][1].v2, image, 0);
		// third row
		renderer->drawImage(x,			y+h1+h2,  w1, h1,	array[0][2].u1, array[0][2].v1, array[0][2].u2, array[0][2].v2, image, 0);
		renderer->drawImage(x+w1,       y+h1+h2,  w2+1, h1,	array[1][2].u1, array[1][2].v1, array[1][2].u2, array[1][2].v2, image, 0);
		renderer->drawImage(x+w1+w2,    y+h1+h2,  w1+1, h1, array[2][2].u1, array[2][2].v1, array[2][2].u2, array[2][2].v2, image, 0);
		break;
	}
 **/
