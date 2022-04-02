
/*! FlexiSense
 *  FlexiGfxRenderer.h
 *  Author: Alessandro Rasulo (mailto: alex9978@gmail.com)
 *  Notes: Abstract graphics renderer
 */

#ifndef FLEXIGFXRENDERER_H
#define FLEXIGFXRENDERER_H

#include <FlexiSense/FlexiExports.h>
#include <FlexiSense/common/FlexiColor.h>
#include <FlexiSense/common/FlexiImage.h>
#include <FlexiSense/common/FlexiPosition.h>
#include <FlexiSense/widgets/FlexiWindow.h>

#include <cairo/cairo.h>
#include <librsvg-2/librsvg/rsvg.h>
#include <librsvg-2/librsvg/rsvg-cairo.h>

#include <math.h>

class FLX_EXPORT FlexiGfxRenderer
{
public:
	FlexiGfxRenderer				();
	virtual ~FlexiGfxRenderer		();

    /*! Initialization */
    virtual bool initialize         () = 0;
    virtual bool initializeOnWindow (long windowId) = 0;
    virtual bool shutdown           () = 0;
    virtual bool setMode            (int width, int height, int bps, bool fullscreen, int fsaa) = 0;

	/*! Get info */
    virtual bool isFullscreen       () = 0;
    const FlexiSize &getScreenSize  ();
    int getScreenPitch              ();
	float getScreenHorizontalRatio	() { return screenHRatio; }
	float getScreenVerticalRatio	() { return screenVRatio; }
    int getMaxTextureSize           () { return maxTextureSize; }   

    /*! Image factory */
    virtual FlexiImage *createImage () = 0;
    virtual FlexiImage *loadImage   (char *filename) = 0;    
    
	/*! Begin & End drawing ops */
	virtual void begin				() = 0;
	virtual void end				() = 0;

    /*! Draw path */
    virtual void beginPath          (FlexiWindow *w);
    virtual void beginSubPath       (FlexiWindow *w);
    virtual void endPath            (FlexiWindow *w);
	virtual void drawLine			(FlexiWindow *w, float x1, float y1, float x2, float y2, FlexiColor *color, float width=2.0f) = 0;
	virtual void drawBox			(FlexiWindow *w, float x1, float y1, float x2, float y2, FlexiColor *color, bool filled=false) = 0;
    virtual void drawArc            (FlexiWindow *w, float x, float y, float radius, float angle1, float angle2, FlexiColor *color, float width=2.0f) = 0;
    virtual void drawNegativeArc    (FlexiWindow *w, float x, float y, float radius, float angle1, float angle2, FlexiColor *color, float width=2.0f) = 0;
	virtual void drawCurve			(FlexiWindow *w, float x1, float y1, float x2, float y2, float x3, float y3, FlexiColor *color, float width=2.0f) = 0;

	/*! Draw image */
	void		 drawImage			(float x, float y, FlexiImage *image, FlexiColor *color = 0);
	void		 drawImage			(float x, float y, float w, float h, FlexiImage *image, FlexiColor *color = 0);
	virtual void drawImage			(float x, float y, float w, float h, float u1, float v1, float u2, float v2, FlexiImage *image, FlexiColor *color = 0) = 0;

protected:
    bool         initialized;
    FlexiSize    desktopSize;
    int          maxTextureSize;

    FlexiSize    screenSize;
    int          screenPitch;

	float        screenHRatio,
                 screenVRatio;

	inline void	 scaleCoordinates	(float &x, float &y);
	inline void	 scaleCoordinatesPair(float &x1, float &y1, float &x2, float &y2);
};

#endif // FLEXIGFXRENDERER_H
