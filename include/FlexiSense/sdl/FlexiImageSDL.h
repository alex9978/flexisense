
/*! FlexiSense
 *  FlexiImageSDL.h
 *  Author: Alessandro Rasulo (mailto: alex9978@gmail.com)
 *  Notes: SDL implementation for texture resource
 */

#ifndef FLEXIIMAGESDL_H
#define FLEXIIMAGESDL_H

#include <FlexiSense/FlexiExports.h>
#include <FlexiSense/common/FlexiDefines.h>
#include <FlexiSense/common/FlexiImage.h>
#include <FlexiSense/common/FlexiLog.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_opengl.h>

class FLX_EXPORT FlexiImageSDL : public FlexiImage
{
friend class FlexiGfxRendererSDL;

public:
    FlexiImageSDL           ();
	virtual ~FlexiImageSDL	();
    
    bool load               (char *filename);
    bool createSurface      (int width, int height);
    void rebind             ();

    unsigned int getTexture ();

private:
    SDL_Surface        *image;
    unsigned int        glTexture;
    
    // sdl surface
    SDL_Surface *createSDLSurface(int w, int h);
    void freeSurfaces();

    // opengl
    int glPow2(int n);
    bool glLoadTexture();
    void glUnloadTexture();
    const char *glGetErrorString(GLenum code);
};

#endif // FLEXIIMAGE_H
