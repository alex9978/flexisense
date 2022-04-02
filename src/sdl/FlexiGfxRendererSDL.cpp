
#include <SDL/SDL_video.h>


#include <FlexiSense/sdl/FlexiGfxRendererSDL.h>
#include <FlexiSense/sdl/FlexiImageSDL.h>

FlexiGfxRendererSDL::FlexiGfxRendererSDL()
{
    onWindow = false;
    baseColor.set(0xffffffff);
}

FlexiGfxRendererSDL::~FlexiGfxRendererSDL()
{
    if(initialized)
        shutdown();
}

bool FlexiGfxRendererSDL::initialize()
{
    char buf[256];

    // set env vars
    putenv((char *)"SDL_VIDEO_CENTERED=1");
    #ifdef LINUX
    putenv((char *)"SDL_VIDEO_X11_DGAMOUSE=0");
    #endif
    //putenv("SDL_DEBUG=1");

    // initialize sdl
    if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_NOPARACHUTE) < 0)
    {
        FLX_LOG(1, "FlexiGfxRendererSDL.initialize() - Unable to init SDL: %s", SDL_GetError());
        return false;
    }

    // get video informations
    const SDL_VideoInfo *vi = SDL_GetVideoInfo();
    desktopSize.set((float)vi->current_w, (float)vi->current_h);
    
    // log some informations
    FLX_LOG(1, "FlexiGfxRendererSDL.initialize() - Video driver: %s", SDL_VideoDriverName(buf, 50));
    FLX_LOG(1, "FlexiGfxRendererSDL.initialize() - Desktop dimensions: %ix%i", (int)desktopSize.width, (int)desktopSize.height);
    FLX_LOG(1, "FlexiGfxRendererSDL.initialize() - Video memory: %i MB", vi->video_mem/1024);
    FLX_LOG(1, "FlexiGfxRendererSDL.initialize() - Hardware surfaces: %s", (vi->hw_available)?"yes":"no");
    FLX_LOG(1, "FlexiGfxRendererSDL.initialize() - Window manager: %s", (vi->wm_available)?"yes":"no");
    FLX_LOG(1, "FlexiGfxRendererSDL.initialize() - Accelerated hardware blits: %s", (vi->blit_hw)?"yes":"no");
    FLX_LOG(1, "FlexiGfxRendererSDL.initialize() - Accelerated software blits: %s", (vi->blit_sw)?"yes":"no");
    FLX_LOG(1, "FlexiGfxRendererSDL.initialize() - Accelerated color fill: %s", (vi->blit_fill)?"yes":"no");
    
    return true;
}

bool FlexiGfxRendererSDL::initializeOnWindow(long windowId)
{
    char buf[256];
        
    onWindow = true;                                // is on another window
    sprintf(buf, "SDL_WINDOWID=%ld", windowId);     // set env var
    putenv(buf);    
    return initialize();                            // run standard init
}

bool FlexiGfxRendererSDL::shutdown()
{
    if(screen)
        SDL_FreeSurface(screen);
    
    // shutdown resource manager
/*    printf("[ELFSDL2D.shutdown()] Delete resource manager");
    SDL2DResourceManager::instance()->shutdown();
*/

    // show system cursor
    SDL_ShowCursor(SDL_ENABLE);

    // quit sdl
    SDL_Quit();
}

bool FlexiGfxRendererSDL::setMode(int width, int height, int bps, bool fullscreen, int fsaa)
{
    int rgb_size[3], value;
    unsigned int flags = 0;

    if(!onWindow)
    {
        // flags
        flags |= SDL_OPENGL;
        if(fullscreen) flags |= SDL_FULLSCREEN;
        if(bps==8) flags |= SDL_HWPALETTE;

        // initialize the display
        switch(bps)
        {
            case 0:     rgb_size[0] = 0; rgb_size[1] = 0; rgb_size[2] = 0; break;
            case 8:		rgb_size[0] = 3; rgb_size[1] = 3; rgb_size[2] = 2; break;
            case 15:
            case 16:	rgb_size[0] = 5; rgb_size[1] = 5; rgb_size[2] = 5; break;
            default:    rgb_size[0] = 8; rgb_size[1] = 8; rgb_size[2] = 8; break;
        }

        SDL_GL_SetAttribute(SDL_GL_RED_SIZE, rgb_size[0]);
        SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, rgb_size[1]);
        SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, rgb_size[2]);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        //SDL_GL_SetAttribute(SDL_GL_SWAP_CONTROL, 1);
        //SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

        if(fsaa > 0)
        {
            SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
            SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, fsaa);
        }
    }
    else
    {
        bps = 0;
    }

    if((screen = SDL_SetVideoMode(width, height, bps, flags)) == NULL)
    {
        FLX_LOG(1, "FlexiGfxRendererSDL.setMode() - Couldn't set graphics mode: %s", SDL_GetError());
        return false;
    }

    if(!onWindow)
    {
        SDL_WM_SetCaption("FlexiSense Application", 0);

        std::string glVendor     = (const char *)glGetString(GL_VENDOR),
                    glRenderer   = (const char *)glGetString(GL_RENDERER),
                    glVersion    = (const char *)glGetString(GL_VERSION),
                    glExtensions = (const char *)glGetString(GL_EXTENSIONS);

        FLX_LOG(1, "FlexiGfxRendererSDL.setMode() - GLVendor     : %s", glVendor.c_str());
        FLX_LOG(1, "FlexiGfxRendererSDL.setMode() - GLRenderer   : %s", glRenderer.c_str());
        FLX_LOG(1, "FlexiGfxRendererSDL.setMode() - GLVersion    : %s", glVersion.c_str());
        FLX_LOG(1, "FlexiGfxRendererSDL.SetMode() - GLExtensions : %s", glExtensions.c_str());

        //

        SDL_GL_GetAttribute(SDL_GL_RED_SIZE, &value);
        FLX_LOG(1, "FlexiGfxRendererSDL.setMode() - SDL_GL_RED_SIZE: requested %d, got %d", rgb_size[0], value);
        SDL_GL_GetAttribute(SDL_GL_GREEN_SIZE, &value);
        FLX_LOG(1, "FlexiGfxRendererSDL.setMode() - SDL_GL_GREEN_SIZE: requested %d, got %d", rgb_size[1], value);
        SDL_GL_GetAttribute(SDL_GL_BLUE_SIZE, &value);
        FLX_LOG(1, "FlexiGfxRendererSDL.setMode() - SDL_GL_BLUE_SIZE: requested %d, got %d", rgb_size[2], value);
        SDL_GL_GetAttribute(SDL_GL_DEPTH_SIZE, &value);
        FLX_LOG(1, "FlexiGfxRendererSDL.setMode() - SDL_GL_DEPTH_SIZE: requested %d, got %d", bps, value);
        SDL_GL_GetAttribute(SDL_GL_DOUBLEBUFFER, &value);
        FLX_LOG(1, "FlexiGfxRendererSDL.setMode() - SDL_GL_DOUBLEBUFFER: requested 1, got %d", value);
        if(fsaa)
        {
            SDL_GL_GetAttribute( SDL_GL_MULTISAMPLEBUFFERS, &value);
            FLX_LOG(1, "FlexiGfxRendererSDL.setMode() - SDL_GL_MULTISAMPLEBUFFERS: requested 1, got %d", value);
            SDL_GL_GetAttribute( SDL_GL_MULTISAMPLESAMPLES, &value);
            FLX_LOG(1, "FlexiGfxRendererSDL.setMode() - SDL_GL_MULTISAMPLESAMPLES: requested %d, got %d", fsaa, value);
        }
        //SDL_GL_GetAttribute( SDL_GL_ACCELERATED_VISUAL, &value );
        //printf("[ELFSDL2D.gfxSetMode()] SDL_GL_ACCELERATED_VISUAL: requested 1, got %d", value);
        //SDL_GL_GetAttribute( SDL_GL_SWAP_CONTROL, &value );
        //printf("[ELFSDL2D.gfxSetMode()] SDL_GL_SWAP_CONTROL: requested 1, got %d", value);
        glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxTextureSize);
        FLX_LOG(1, "FlexiGfxRendererSDL.setMode() - GL_MAX_TEXTURE_SIZE: %i", maxTextureSize);

        // log opengl error
      //  if(glCheckError("FlexiGfxRendererSDL.setMode()\n"))
      //      return false;
    }

    // set screen size and pitch
    screenSize.set(width, height);
    screenPitch = screen->pitch;

    /*// setup cairo
    cairoSurface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
    cairoDC = cairo_create(cairoSurface);

    cairo_set_source_rgb(cairoDC, 0, 0, 0);
    cairo_rectangle(cairoDC, 0.25f, 0.25f, 0.5f, 0.5f);
    cairo_fill(cairoDC);
    cairo_stroke(cairoDC);*/

    // hide system cursor
    SDL_ShowCursor(SDL_DISABLE);    
    SDL_EnableUNICODE(1);
    SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);

    return true;
}

bool FlexiGfxRendererSDL::isFullscreen()
{
    return ((screen->flags & SDL_FULLSCREEN) == SDL_FULLSCREEN);
}

FlexiImage *FlexiGfxRendererSDL::createImage()
{
    return (FlexiImage *)new FlexiImageSDL();
}

FlexiImage *FlexiGfxRendererSDL::loadImage(char *filename)
{
    FlexiImageSDL *i = new FlexiImageSDL();
    i->load(filename);
    return (FlexiImage *)i;
}

void FlexiGfxRendererSDL::begin()
{
    glEnterMode2D();
    glClear(GL_COLOR_BUFFER_BIT);
    FlexiColor c(0xaa4444ff);
//    drawBoxFilled(0, 0, screen->w, screen->h, &c);
}

void FlexiGfxRendererSDL::end()
{
    SDL_GL_UpdateRects(0, 0);
    SDL_GL_SwapBuffers();
    glLeaveMode2D();
}


void FlexiGfxRendererSDL::drawImage(float x, float y, float w, float h, float u1, float v1, float u2, float v2, FlexiImage *image, FlexiColor *color)
{
    float *c = (color!=0)?color->getFloat():baseColor.getFloat(),
          *texcoord = image->getTexCoords(),
           u = texcoord[2] - texcoord[0],
           v = texcoord[3] - texcoord[1];
    //
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1024, 1024, 0, GL_RGBA, GL_UNSIGNED_BYTE, * );

    //
    glLoadIdentity();
 	glTranslatef(x, y, 0);	
    glBindTexture(GL_TEXTURE_2D, image->getTexture());
	glBegin(GL_TRIANGLE_STRIP);        
        glColor4f(c[0], c[1], c[2], c[3]);      
        glTexCoord2f(texcoord[0]+u1*u, texcoord[1]+v1*v); glVertex2i(0, 0);
        glTexCoord2f(texcoord[0]+u2*u, texcoord[1]+v1*v); glVertex2i(w, 0);
        glTexCoord2f(texcoord[0]+u1*u, texcoord[1]+v2*v); glVertex2i(0, h);
        glTexCoord2f(texcoord[0]+u2*u, texcoord[1]+v2*v); glVertex2i(w, h);        
	glEnd();
}

void FlexiGfxRendererSDL::glEnterMode2D()
{
    glClearDepth(0);
	glPushAttrib(GL_ENABLE_BIT);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);

	// This allows alpha blending of 2D textures with the scene
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glShadeModel(GL_SMOOTH);

	glViewport(0, 0, screen->w, screen->h);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, (GLdouble)screen->w, (GLdouble)screen->h, 0.0, -1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    // log opengl error
    //glCheckError("ELFSDL2D.glEnterMode2D()");
}

void FlexiGfxRendererSDL::glLeaveMode2D()
{
    glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glPopAttrib();
}
