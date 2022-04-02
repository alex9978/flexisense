
#include <FlexiSense/FlexiResourceManager.h>
#include <FlexiSense/FlexiManager.h>
#include <FlexiSense/FlexiGfxRenderer.h>

FlexiResourceManager::FlexiResourceManager()
{
}

FlexiResourceManager::~FlexiResourceManager()
{
    FlexiResource *r = 0;
    std::map<char*,FlexiResource*>::iterator it;
    for(it = resources.begin(); it!= resources.end(); it++)
    {
        r = (FlexiResource *)it->second;
        if(r->resource)
            switch(r->type)
            {
            case FlexiResource::FLX_RES_CATALOG:
                delete (FlexiCatalog *)r->resource;
                break;
            case FlexiResource::FLX_RES_FONT:
                delete (FlexiFont *)r->resource;
                break;
            case FlexiResource::FLX_RES_IMAGE:
                delete (FlexiImage *)r->resource;
                break;
            case FlexiResource::FLX_RES_SVG:
                delete (FlexiSVG *)r->resource;
                break;
            case FlexiResource::FLX_RES_THEME:
                delete (FlexiTheme *)r->resource;
                break;
            }
    }
    resources.clear();
}

FlexiCatalog *FlexiResourceManager::getCatalog(char *filename)
{
    // find in resources
    FlexiCatalog *c = (FlexiCatalog *)findResource(filename);
    if(c) return c;

    // load new catalog
    c = new FlexiCatalog();
    c->load(filename);

    // create new resource
    createResource(filename, c, FlexiResource::FLX_RES_CATALOG);

    // return
    return c;
}

FlexiFont *FlexiResourceManager::getFont(char *filename)
{
    // find in resources
    FlexiFont *f = (FlexiFont *)findResource(filename);
    if(f) return f;
    
    // load new font
    f = new FlexiFont(filename);

    // create new resource
    createResource(filename, f, FlexiResource::FLX_RES_FONT);

    // return
    return f;
}

FlexiImage *FlexiResourceManager::getImage(char *filename)
{
    // find in resources
    FlexiImage *i = (FlexiImage *)findResource(filename);
    if(i) return i;

    // load new image
    FlexiGfxRenderer *gr = FlexiManager::instance()->getRenderer();
    i = gr->loadImage(filename);

    // create new resource
    createResource(filename, i, FlexiResource::FLX_RES_IMAGE);

    // return
    return i;
}

FlexiSVG *FlexiResourceManager::getSVG(char *filename)
{
    // find in resources
    FlexiSVG *s = (FlexiSVG *)findResource(filename);
    if(s) return s;

    // load new svg file
    s = new FlexiSVG();
    s->load(filename);

    // create new resource
    createResource(filename, s, FlexiResource::FLX_RES_SVG);

    // return
    return s;
}

FlexiTheme *FlexiResourceManager::getTheme(char *filename)
{
    // find in resources
    FlexiTheme *t = (FlexiTheme *)findResource(filename);
    if(t) return t;

    // load new font
    t = new FlexiTheme();
    t->load(filename);

    // create new resource
    createResource(filename, t, FlexiResource::FLX_RES_THEME);

    // return
    return t;
}

bool FlexiResourceManager::releaseResource(void *res)
{
    FlexiResource *r = 0;
    std::map<char*,FlexiResource*>::iterator it;
    for(it = resources.begin(); it!= resources.end(); it++)
    {
        r = (FlexiResource *)it->second;
        if(r->resource == res)
        {            
            r->autocounter--;
            if(r->autocounter == 0)
            {
                if(r->resource)
                    switch(r->type)
                    {                    
                    case FlexiResource::FLX_RES_CATALOG:
                        delete (FlexiCatalog *)r->resource;
                        break;
                    case FlexiResource::FLX_RES_FONT:
                        delete (FlexiFont *)r->resource;
                        break;
                    case FlexiResource::FLX_RES_IMAGE:
                        delete (FlexiImage *)r->resource;
                        break;
                    case FlexiResource::FLX_RES_SVG:
                        delete (FlexiSVG *)r->resource;
                        break;
                    case FlexiResource::FLX_RES_THEME:
                        delete (FlexiTheme *)r->resource;
                        break;
                    }

                resources.erase(it);                
                return true;
            }
        }
    }
    return false;
}

void *FlexiResourceManager::findResource(char *filename)
{
    if(resources[filename])
    {
        resources[filename]->autocounter++;
        return resources[filename]->resource;
    }
    return 0;
}

void FlexiResourceManager::createResource (char *filename, void *resource, int type)
{
    FlexiResource *res = new FlexiResource;
    res->type = type;
    res->autocounter = 1;
    res->resource = resource;
    resources[filename] = res;
    FLX_LOG(1, "Resource '%s' created", filename);
}
