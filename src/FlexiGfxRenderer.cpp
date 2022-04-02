
/*! FlexiSense
 *  FlexiGfxRenderer.cpp
 *  Author: Alessandro Rasulo (mailto: alex9978@gmail.com)
 *  Notes: Abstract graphics renderer
 */

#include <FlexiSense/FlexiGfxRenderer.h>

FlexiGfxRenderer::FlexiGfxRenderer()
{
    initialized = false;
}

FlexiGfxRenderer::~FlexiGfxRenderer()
{
}

const FlexiSize &FlexiGfxRenderer::getScreenSize()
{
    return screenSize;
}

int FlexiGfxRenderer::getScreenPitch()
{
    return screenPitch;
}

void FlexiGfxRenderer::beginPath(FlexiWindow *w)
{
    cairo_t *cr = w->getContext();
    if(cr)
        cairo_new_path(cr);
}

void FlexiGfxRenderer::beginSubPath(FlexiWindow *w)
{
    cairo_t *cr = w->getContext();
    if(cr)
        cairo_new_sub_path(cr);
}

void FlexiGfxRenderer::endPath(FlexiWindow *w)
{
    cairo_t *cr = w->getContext();
    if(cr)
        cairo_close_path(cr);
}

void FlexiGfxRenderer::drawLine(FlexiWindow *w, float x1, float y1, float x2, float y2, FlexiColor *color, float width)
{
    cairo_t *cr = w->getContext();
    if(cr)
    {
        float *fcolor = color->getFloat();
        cairo_set_source_rgba(cr, fcolor[0], fcolor[1], fcolor[2], fcolor[3]);
        cairo_set_line_width(cr, width);
        cairo_move_to(cr, x1, y1);
        cairo_line_to(cr, x2, y2);
    }
}

void FlexiGfxRenderer::drawBox(FlexiWindow *w, float x1, float y1, float x2, float y2, FlexiColor *color, bool filled)
{}

void FlexiGfxRenderer::drawArc(FlexiWindow *w, float x, float y, float radius, float angle1, float angle2, FlexiColor *color, float width)
{}

void FlexiGfxRenderer::drawNegativeArc(FlexiWindow *w, float x, float y, float radius, float angle1, float angle2, FlexiColor *color, float width)
{}

void FlexiGfxRenderer::drawCurve(FlexiWindow *w, float x1, float y1, float x2, float y2, float x3, float y3, FlexiColor *color, float width)
{}

void FlexiGfxRenderer::drawImage(float x, float y, FlexiImage *image, FlexiColor *color)
{    
    FlexiSize size = image->getSize();
	drawImage(x, y, size.width, size.height, 0, 0, 1, 1, image, color);
}

void FlexiGfxRenderer::drawImage(float x, float y, float w, float h, FlexiImage *image, FlexiColor *color)
{
	drawImage(x, y, w, h, 0.0f, 0.0f, 1.0f, 1.0f, image, color);
}

void FlexiGfxRenderer::scaleCoordinates(float &x, float &y)
{
	// round to minimum
	x = ceilf(x * screenHRatio);
	y = ceilf(y * screenVRatio);
}

void FlexiGfxRenderer::scaleCoordinatesPair(float &x1, float &y1, float &x2, float &y2)
{
	// round to minimum
	x1 = ceilf(x1 * screenHRatio);
	y1 = ceilf(y1 * screenVRatio);
	x2 = ceilf(x2 * screenHRatio);
	y2 = ceilf(y2 * screenVRatio);
}
