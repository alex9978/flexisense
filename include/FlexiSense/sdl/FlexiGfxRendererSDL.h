
/*! FlexiSense
 *  FlexiGfxRendererSDL.h
 *  Author: Alessandro Rasulo (mailto: alex9978@gmail.com)
 *  Notes: SDL graphics renderer
 */

#ifndef FLEXIGFXRENDERERSDL_H
#define FLEXIGFXRENDERERSDL_H

#include <FlexiSense/FlexiGfxRenderer.h>
#include <FlexiSense/common/FlexiColor.h>
#include <FlexiSense/common/FlexiDefines.h>
#include <FlexiSense/common/FlexiLog.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_opengl.h>
#include <SDL/SDL_syswm.h>

class FLX_EXPORT FlexiGfxRendererSDL : public FlexiGfxRenderer
{
public:
	FlexiGfxRendererSDL				();
	virtual ~FlexiGfxRendererSDL	();
    
    /*! Initialization */
    bool initialize                 ();
    bool initializeOnWindow         (long windowId);
    bool shutdown                   ();
    bool setMode                    (int width, int height, int bps, bool fullscreen, int fsaa);

    /*! Get info */
    bool isFullscreen               ();

    /*! Image factory */
    FlexiImage *createImage         ();
    FlexiImage *loadImage           (char *filename);
    
	/*! Begin & End drawing ops */
	void begin                  	();
	void end                		();

	/*! Drawing ops */
    void drawImage          		(float x, float y, float w, float h, float u1, float v1, float u2, float v2, FlexiImage *image, FlexiColor *color = 0);

private:
    bool                onWindow;
    FlexiColor          baseColor;
    SDL_Surface        *screen;
    
    void glEnterMode2D();
    void glLeaveMode2D();    
};

#endif // FLEXIGFXRENDERERSDL_H
