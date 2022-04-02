
/** @class FlexiResourceManager
 *  @brief Global resource manager
 *  @author Alessandro Rasulo (mailto: alex9978@gmail.com)
 */

#ifndef _FLEXIRESOURCEMANAGER_H
#define	_FLEXIRESOURCEMANAGER_H

#include <FlexiSense/FlexiExports.h>
#include <FlexiSense/common/FlexiCatalog.h>
#include <FlexiSense/common/FlexiFont.h>
#include <FlexiSense/common/FlexiImage.h>
#include <FlexiSense/common/FlexiSVG.h>
#include <FlexiSense/common/FlexiTheme.h>
#include <string>

typedef struct flexi_resource
{
    enum FLX_RESOURCETYPE
    {
        FLX_RES_CATALOG = 1,
        FLX_RES_FONT,
        FLX_RES_IMAGE,
        FLX_RES_SVG,
        FLX_RES_THEME
    };

    int          type;
    void        *resource;
    int          autocounter;
} FlexiResource;

class FLX_EXPORT FlexiResourceManager
{
public:
    FlexiResourceManager            ();
	virtual ~FlexiResourceManager   ();

    FlexiCatalog    *getCatalog     (char *filename);
    FlexiFont       *getFont        (char *filename);
    FlexiImage      *getImage       (char *filename);
    FlexiSVG        *getSVG         (char *filename);
    FlexiTheme      *getTheme       (char *filename);
    bool             releaseResource(void *res);

private:
    void            *findResource   (char *filename);
    void             createResource (char *filename, void *resource, int type);

    std::map<char*,FlexiResource*> resources;
};

#endif


