
#include <FlexiSense/sdl/FlexiImageSDL.h>
#include <FlexiSense/FlexiGfxRenderer.h>

FlexiImageSDL::FlexiImageSDL() : image(0), glTexture(0)
{
    cairoSurface = 0;
    image = 0;
}

FlexiImageSDL::~FlexiImageSDL()
{
    freeSurfaces();
    glUnloadTexture();
}

bool FlexiImageSDL::load(char *filename)
{
    // free current sdl surface
    freeSDLSurface();

    // load image
    image = IMG_Load(filename);
    if(image == 0)
    {
        FLX_LOG(1, "FlexiImageSDL::load() - %s", IMG_GetError());
        image = createSDLSurface(32, 32);
        return false;
    }

    if(!glLoadTexture())
        return false;
        
    size.width = (float) image->w;
    size.height = (float) image->h;

    FLX_LOG(2, "FlexiImageSDL::load() - %s loaded", filename);
    return true;
}

bool FlexiImageSDL::createSurface(int width, int height)
{
    if(cairoSurface)
        return false;

    FlexiGfxRenderer *gr = FlexiManager::instance()->getRenderer();

    std::vector<unsigned char> data(w*h*4);

	image = SDL_CreateRGBSurfaceFrom(&data[0], width, height, 32, width*4, 0x00FF0000,0x0000FF00,0x000000FF,0xFF000000);
	cairoSurface = cairo_image_surface_create_for_data(&data[0], CAIRO_FORMAT_ARGB32, width, height, gr->getScreenPitch());

    return (image && cairoSurface);
}

/*	std::vector<unsigned char> data(width*height*4);

	image = SDL_CreateRGBSurfaceFrom(&data[0],
                                     surface->width,
                                     surface->height,
                                     32,
                                     surface->width*4,
                                     0x00FF0000,0x0000FF00,0x000000FF,0xFF000000);

	cairo_surface_t *surface = surface = cairo_image_surface_create_for_data(&data[0],
		CAIRO_FORMAT_ARGB32,width,height,screen->pitch);

	cairo_t *cr = cairo_create(surface);
	cairo_set_antialias (cr,CAIRO_ANTIALIAS_GRAY);


				cairo_set_source_rgba(cr, 0, 0, 0, 1);
				cairo_paint(cr);
				cairo_set_source_rgba(cr, 1, 0, 0, 1);
				cairo_arc (cr, width/2, height/2, 76.8, 0, 2 * 3.1416926);
				cairo_fill (cr);

			SDL_BlitSurface(sdl_surface, NULL, screen, NULL);
			SDL_Flip(screen);
			SDL_Delay(0);
	}
	cairo_destroy(cr);
	cairo_surface_destroy(surface);
	SDL_FreeSurface(sdl_surface);

	return 0;
    return (image != NULL);
*/

void FlexiImageSDL::rebind()
{
    glUnloadTexture();
    glLoadTexture();
}

unsigned int FlexiImageSDL::getTexture()
{
    return glTexture;
}

SDL_Surface *FlexiImageSDL::createSDLSurface(int w, int h)
{
    SDL_Surface *surface;
    Uint32 rmask, gmask, bmask, amask;

    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
    #else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
    #endif

    surface = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32, rmask, gmask, bmask, amask);
    if(surface == NULL)
        FLX_LOG(1, "FlexiImageSDL::createEmptySurface() - CRITICAL ERROR: %s", SDL_GetError());

    return surface;
}

void FlexiImageSDL::freeSurfaces()
{
    if(cairoSurface)
        cairo_surface_destroy(cairoSurface);

    if(image)
        SDL_FreeSurface(image);
}

int FlexiImageSDL::glPow2(int n)
{
	int value = 1;

	while(value < n)
		value <<= 1;

    return value;
}

bool FlexiImageSDL::glLoadTexture()
{	
	SDL_Surface *texture = 0;
	SDL_Rect area;
	Uint32 saved_flags;
	Uint8  saved_alpha;

	// use the surface width and height expanded to powers of 2
	int w = glPow2(image->w),
        h = glPow2(image->h),
        maxSize = FlexiManager::instance()->getRenderer()->getMaxTextureSize();
    
	if(w > maxSize)
	{      
        FLX_LOG(1, "FlexiImageSDL::glLoadTexture() - Image size not allowed: too big");
        return false;
    }
    else
    {
        texcoord[0] = 0.0f;			        // Min X
        texcoord[1] = 0.0f;			        // Min Y
        texcoord[2] = (float) image->w / w;	// Max X
        texcoord[3] = (float) image->h / h;	// Max Y

        if(!cairoSurface)
            texture = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32,
                                            // OpenGL RGBA masks
                                            #if SDL_BYTEORDER == SDL_LIL_ENDIAN
                                            0x000000FF,
                                            0x0000FF00,
                                            0x00FF0000,
                                            0xFF000000
                                            #else
                                            0xFF000000,
                                            0x00FF0000,
                                            0x0000FF00,
                                            0x000000FF
                                            #endif
                                            );
        else
            texture = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32, 0x00FF0000,0x0000FF00,0x000000FF,0xFF000000);

        if(!texture)
        {
            FLX_LOG(1, "FlexiImageSDL::glLoadTexture() - ERROR: Can't allocate surface");
            return false;
        }

        // save the alpha blending attributes
        saved_flags = image->flags&(SDL_SRCALPHA|SDL_RLEACCELOK);
        saved_alpha = image->format->alpha;
        if((saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA)
            SDL_SetAlpha(image, 0, 0);

        // copy the surface into the GL texture image
        area.x = 0;
        area.y = 0;
        area.w = image->w;
        area.h = image->h;
        SDL_BlitSurface(image, &area, texture, &area);

        // restore the alpha blending attributes
        if((saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA)
            SDL_SetAlpha(image, saved_flags, saved_alpha);
    }

	// create an OpenGL texture for the image
	glGenTextures(1, &glTexture);
	glBindTexture(GL_TEXTURE_2D, glTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	SDL_FreeSurface(texture);

    GLenum gl_error = glGetError();
    if(gl_error != GL_NO_ERROR)
    {
        FLX_LOG(1, "FlexiImageSDL::glLoadTexture() - OpenGL error: %s", glGetErrorString(gl_error));
        return false;
    }
    return true;
}

void FlexiImageSDL::glUnloadTexture()
{
    if(glTexture)
        glDeleteTextures(1, &glTexture);
}

const char *FlexiImageSDL::glGetErrorString(GLenum code)
{
    switch(code)
    {
    case GL_NO_ERROR:           return "GL_NO_ERROR";
    case GL_INVALID_ENUM:       return "GL_INVALID_ENUM";
    case GL_INVALID_VALUE:	    return "GL_INVALID_VALUE";
    case GL_INVALID_OPERATION:	return "GL_INVALID_OPERATION";
    case GL_STACK_OVERFLOW:     return "GL_STACK_OVERFLOW";
    case GL_STACK_UNDERFLOW:    return "GL_STACK_UNDERFLOW";
    case GL_OUT_OF_MEMORY:      return "GL_OUT_OF_MEMORY";
    default:                    return "Unknown OpenGL error";
    }
}
