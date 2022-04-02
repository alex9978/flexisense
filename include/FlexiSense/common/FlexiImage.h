
/*! FlexiSense
 *  FlexiImage.h
 *  Author: Alessandro Rasulo (mailto: alex9978@gmail.com)
 *  Notes: Image resource
 */

#ifndef FLEXIIMAGE_H
#define FLEXIIMAGE_H

#include <FlexiSense/FlexiExports.h>
#include <FlexiSense/common/FlexiSize.h>
#include <cairo/cairo.h>
#include <string>

class FLX_EXPORT FlexiImage
{
public:
    FlexiImage                  () {}    
	virtual ~FlexiImage         () {}
    
    virtual bool load           (char *filename) { return false; }
    virtual bool createSurface  (int width, int height) { return false; }
    virtual void rebind         () = 0;

    virtual unsigned int getTexture() { return 0; }
    cairo_surface_t *getSurface () { return cairoSurface; }
    const FlexiSize &getSize    () { return size; }
    float *getTexCoords         () { return texcoord; }

protected:
    std::string			        file;
    FlexiSize                   size;
    float                       texcoord[4];

    cairo_surface_t            *cairoSurface;
};

#endif // FLEXIIMAGE_H
